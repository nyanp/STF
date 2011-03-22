/**
 * @file   orbitutil.cpp
 * @brief  NJHILSから持ってきた軌道計算関係モジュールを，sgp4名前空間でラップして使用．
 *
 * @author david vallado
 * @date   2011.02.16
 */
/* ---------------------------------------------------------------------
*
*                              orbit.cpp
*						軌道計算プログラムメイン
*
*  this program tests the sgp4 propagator. an stk ephemeris file is generated
*  along with the test output. the code for this is left justified for easy
*  location.
*
*                          companion code for
*             fundamentals of astrodynamics and applications
*                                  2007
*                            by david vallado
*
*     (w) 719-573-2600, email dvallado@agi.com
*     *****************************************************************
*  current :
*             2 apr 07  david vallado
*                        fixes for linux suggested by brian micek
*                        misc fixes noted by the community - manual operation,
*                        formats, char lengths
*  changes :
*            14 aug 06  david vallado
*                        update mfe for verification time steps, constants
*            20 jul 05  david vallado
*                         fixes for paper, corrections from paul crawford
*             7 jul 04  david vallado
*                         fix record file and get working
*            14 may 01  david vallado
*                         2nd edition baseline
*                   80  norad
*                         original baseline
*       ----------------------------------------------------------------      */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "sgp4ext.h"
#include "sgp4unit.h"

//とりあえず
#include "../models/igrf.h"

#define PI			3.14159265358979323846
#define PIO2		1.57079632679489656		/* Pi/2 */
#define X3PIO2		4.71238898038468967		/* 3*Pi/2 */
#define TWOPI		6.28318530717958623		/* 2*Pi  */
//#define XKMPER		6.378137E3			/* WGS 84 Earth radius km */	//GRM-80(WGS84)楕円体
//#define F			3.35281066474748E-3	/* Flattening factor */				//扁平率WGS84
#define XKMPER		6.378135E3			/* WGS 72 Earth radius km */		//地球半径WGS72楕円体
#define F			(1.0/298.26)			/* Flattening factor */			//扁平率WGS72
#define RSUN		6.960E5					//太陽半径[km]
#define AU			1.49597870691E8			//天文単位
#define DEG2RAD		0.017453292519943295769	// PI/180
#define RAD2DEG		(180/PI)

using namespace std;

namespace sgp4 {
static gravconsttype whichconst;
static elsetrec satrec;

//グリニッジ平均恒星時を計算(sgp4io.hに書いてあるgstimeの補助)
double SiderealTime(double jd) {
	double K    = jd - 2415020.0;	//１９００年１月０日正午からの経過日数
	double Tu   = K/36525.0;
	double gmst = 6+(38.0/60.0)+(45.836/3600.0) + 8640184.542*Tu/3600 + 0.0929*pow(Tu, 2)/3600;	//ここでは時間単位
	while(gmst>24){gmst-=24;}
	gmst *= 15;	//ここでdeg単位に変換

	return gmst * DEG2RAD;
}

//G系経緯度高度からG系直交座標へ[test:TransGAxisと同じ結果]
//Reference:http://www.toyama-cmt.ac.jp/~mkawai/lecture/radionav/tfcoordinate/transform.html
int TransGeoToGAxis(double lon, double lat, double alt, double* pos)
{
	double n;
	double clat = cos(lat);
	double slat = sin(lat);
	double clon = cos(lon);
	double slon = sin(lon);

	n = XKMPER / pow(1-F*(2-F)*slat*slat, 0.5 );

	pos[0] = (n+alt) * clat * clon;
	pos[1] = (n+alt) * clat * slon;
	pos[2] = (n+alt-F*(2-F)*n) * slat;

	return 0;
}

//地心赤道直交座標(ECI)をG系直交座標系へ
int TransGAxis(double* pos, double gmst, double* gpos)
{
	double cgmst = cos(gmst);
	double sgmst = sin(gmst);

	gpos[0] = pos[0] * cgmst + pos[1] * sgmst;
	gpos[1] = -pos[0] * sgmst + pos[1] * cgmst;
	gpos[2] = pos[2];

	return 0;
}

//ECIから地心G系座標の経緯度パラメータに変換
//Reference:Predct
void TransECIToGeo(double gmst, double *pos, double *lon, double* lat, double* alt)
{
	/* Procedure Calculate_LatLonAlt will calculate the geodetic  */
	/* position of an object given its ECI position pos and time. */
	/* It is intended to be used to determine the ground track of */
	/* a satellite.  The calculations  assume the earth to be an  */
	/* oblate spheroid as defined in WGS '72.                     */

	/* Reference:  The 1992 Astronomical Almanac, page K12. */

	double r, e2, phi, c;
	double theta;

	theta=AcTan(pos[1], pos[0]); /* radians */
	*lon=FMod2p(theta-gmst); /* radians */	//東経が正？
	r=sqrt(pos[0]*pos[0]+pos[1]*pos[1]);
	e2=F*(2-F);
	*lat=AcTan(pos[2], r); /* radians */

	do
	{
		phi=*lat;
		c=1/sqrt(1-e2*sin(phi)*sin(phi));
		*lat=AcTan(pos[2]+XKMPER*c*e2*sin(phi), r);

	} while (fabs(*lat-phi)>=1E-10);

	*alt=r/cos(*lat)-XKMPER*c; /* kilometers */	//楕円体高さ

	if (*lat>PIO2)
		*lat-=TWOPI;
}



//太陽位置の計算(ECI座標)
//Reference:http://abacus.nmsu.edu/nmsu_ece_95_002_.pdf
//Reference:http://www.dustymars.net/Mephemeris.htm
//Reference:Predct
//※ETとUTの誤差を無視したが問題ないか？
//Output:solar_vector[3]	[km]で返す
void CalculateSolarPosition(double jd, double *solar_vector)
{
	double l, m, c, theta, epsi, t, r, nu, e;

	t = (jd-2415020)/36525;
	l = 279.69668 + 36000.76892 * t + 0.0003025 *t*t;
	m = 358.475833 + 35999.04975 * t - 0.00015 *t*t + 0.0000033 *t*t*t;
	c = ( (1.919460 - 0.004789 * t - 0.000014 *t*t) * sin(m*DEG2RAD)
		+ (0.020094 - 0.0001 *t) * sin(2*m*DEG2RAD) + 0.000293 * sin(3*m*DEG2RAD) );
	theta = l + c - 0.00556 - 0.00479*sin((259.18-1934.142*t)*DEG2RAD);
	epsi = 23.452294 - 0.0130125*t - 0.00000164*t*t - 0.000000503*t*t*t + 0.00256*cos((259.18-1934.142*t)*DEG2RAD);

	e = 0.01675104 - 0.0000418*t - 0.000000126*t*t;
	nu = m+c;
	r = 1.00000023 * (1-e*e) / (1+ e*cos(nu*DEG2RAD));
	r *= AU;

	solar_vector[0]=r*cos(theta*DEG2RAD);
	solar_vector[1]=r*sin(theta*DEG2RAD)*cos(epsi*DEG2RAD);
	solar_vector[2]=r*sin(theta*DEG2RAD)*sin(epsi*DEG2RAD);

}

//蝕判定
//蝕なら1を返却。そうでなければ0を返却
//主影のみ判定
//(argument depth) 
//Reference:Predct
bool SatEclipsed(double *pos, double *sol)
{
	/* Calculates stellite's eclipse status and depth */

	double sd_sun, sd_earth, delta, depth;
	double Rho[3], earth[3];

	/* Determine partial eclipse */
	sd_earth=asin(XKMPER/mag(pos));
	for (int i=0;i<3;i++) {
		Rho[i] = sol[i]-pos[i];
	}

	sd_sun=asin(RSUN/mag(Rho));
	for (int i=0;i<3;i++) {
		earth[i] = -1.0 * pos[i];
	}
	delta=angle(sol, earth);

	depth=sd_earth - sd_sun - delta;

	if (sd_earth<sd_sun)
		return false;
	else
		if (depth>=0)
			return true;
		else
			return false;
}



}