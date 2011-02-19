/**
 * @file   orbitutil.cpp
 * @brief  
 *
 * @author Taiga Nomi
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


#pragma warning ( disable : 4996 )		//fopenエラー回避

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#ifdef _WIN32
#include <io.h>
#endif

#include <conio.h>

#include "sgp4ext.h"
#include "sgp4unit.h"
#include "sgp4io.h"
//とりあえず
#include "../models/igrf.h"
#include "matrixvector.h"

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

//extern const int DEBUG;	//画面表示

//extern double global_poseci[3];
//extern double global_solpos[3];
//extern double global_veleci[3];

//グリニッジ平均恒星時を計算(sgp4io.hに書いてあるgstimeの補助)
double SiderealTime(double jd) {
	double K    = jd - 2415020.0;	//１９００年１月０日正午からの経過日数
	double Tu   = K/36525.0;
	double gmst = 6+(38.0/60.0)+(45.836/3600.0) + 8640184.542*Tu/3600 + 0.0929*pow(Tu,2)/3600;	//ここでは時間単位
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

	n = XKMPER / pow(1-F*(2-F)*slat*slat,0.5 );

	pos[0] = (n+alt) * clat * clon;
	pos[1] = (n+alt) * clat * slon;
	pos[2] = (n+alt-F*(2-F)*n) * slat;

	return 0;
}

//地心赤道直交座標(ECI)をG系直交座標系へ
int TransGAxis(double* pos,double gmst,double* gpos)
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

	theta=AcTan(pos[1],pos[0]); /* radians */
	*lon=FMod2p(theta-gmst); /* radians */	//東経が正？
	r=sqrt(pos[0]*pos[0]+pos[1]*pos[1]);
	e2=F*(2-F);
	*lat=AcTan(pos[2],r); /* radians */

	do
	{
		phi=*lat;
		c=1/sqrt(1-e2*sin(phi)*sin(phi));
		*lat=AcTan(pos[2]+XKMPER*c*e2*sin(phi),r);

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
	double l,m,c,theta,epsi,t,r,nu,e;

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
	/*
	cout << "Rho ";
	for(int i=0;i<3;i++) {
		cout << Rho[i];
		cout << " ";
	}
	cout << endl;
	*/
	sd_sun=asin(RSUN/mag(Rho));
	for (int i=0;i<3;i++) {
		earth[i] = -1.0 * pos[i];
	}
	delta=angle(sol,earth);

	depth=sd_earth - sd_sun - delta;

	if (sd_earth<sd_sun)
		return false;
	else
		if (depth>=0)
			return true;
		else
			return false;
}


int InitOrbit(double* jdepoch, char* tle1, char* tle2)
{
	//測地系はWGS72を使用【暫定】
	whichconst = wgs72;
	char typerun='c', typeinput=0;
	double startmfe, stopmfe, deltamin;

	//TLE
//	char tle1[130],tle2[130];
	//strcpy(tle1,"1 88888U          80275.98708465  .00073094  13844-3  66816-4 0    87");
	//strcpy(tle2,"2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518  1058");

	/*****PRISM*****/
//	strcpy(tle1,"1 33493U 09002B   09267.97681059  .00000231  00000-0  37030-4 0  7858");
//	strcpy(tle2,"2 33493  98.0645  20.6659 0018835 279.8094  80.0980 14.80732317 36233");

	//FO-29
	//strcpy(tle1,"1 24278U 96046B 03232.95303700 -.00000056 00000-0 -24068-4 0 06270");
	//strcpy(tle2,"2 24278 098.5660 359.5477 0351513 101.3348 262.7487 13.52885302346104");

	twoline2rv( tle1, tle2, typerun, typeinput, whichconst, startmfe, stopmfe, deltamin, satrec );
	printf(" SAT No.%ld\n", satrec.satnum);
	*jdepoch = satrec.jdsatepoch;

	return 0;

}

//引数はクラス化までの繋ぎ
int OrbitMain(double stoptime, double* mag)
{	

	//?
	double p, a, ecc, incl, node, argp, nu, m, arglat, truelon, lonper;
	double ro[3];
	double vo[3];

	//SGP4計算
	sgp4 (whichconst, satrec,  stoptime, ro,  vo);


	//SGP4エラー表示
	if (satrec.error > 0)printf("# *** error: time:= %f *** code = %3d\n",satrec.t, satrec.error);

	//表示初期化
	cout.setf(ios::floatfield,ios::fixed);		//指数表示
	cout.setf(ios::showbase|ios::showpoint);
	cout.precision(4);

	//計算現在時刻
//	cout << "stoptime = " << stoptime;

	//ユリウス日計算
	double jd = satrec.jdsatepoch + stoptime/1440.0;
	int  year; int mon; int day; int hr; int min;
	double sec;
	invjday( jd, year,mon,day,hr,min, sec );
//	cout << " " << year << "/" << mon << "/" << day << " " << hr << ":" << min << ":" << sec << endl;
	//DecimalYearの計算(forIGRF)
	double decyear;
	JdToDecyear(jd,&decyear);
//	cout << "DecimalYear = " << decyear << "\n";


	//グリニッジ平均恒星時計算
	double side = gstime(jd);	//rad


	//double gpos[3];
	//double test[3];
	//TransGAxis(ro,side,gpos);	//G系に変換
	//TransECIToGeo(0,gpos,&test[0],&test[1],&test[2]);
	//cout << "test高度" << test[2] << " 緯度" << test[1]*RAD2DEG << " 経度" << test[0]*RAD2DEG << endl;

/*
	for(int i=0;i<3;i++) {
		cout << gpos[i];
		cout << " ";
	}
	cout << endl;
*/
	//緯度経度の表示
	double lon,lat,alt;

	TransECIToGeo(side, ro, &lon, &lat, &alt);
//	cout << "高度" << alt << " 緯度" << lat*RAD2DEG << " 経度" << lon*RAD2DEG << endl;

	//IGRF計算
	igrf::IgrfCalc(decyear,lat,lon,alt,side,mag);


	/*
	//test
	double fm[6];
	igrfm(fm);
	cout << "IGRF(Maxis) ";
	for(int i=0;i<6;i++) {
		cout << fm[i];
		cout << " ";
	}
	cout << "\n";
	*/

	//6要素の表示
	double tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2;
	getgravconst( whichconst, tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2 );
	rv2coe(ro, vo, mu, p, a, ecc, incl, node, argp, nu, m, arglat, truelon, lonper );
//	printf(" a %10.6f e %8.6f i %10.5f Ω %10.5f ω %10.5f n %10.5f m %10.5f\n",a, ecc, incl*RAD2DEG, node*RAD2DEG, argp*RAD2DEG, nu*RAD2DEG, m*RAD2DEG);
	
	//太陽位置の表示
	double sol_pos[3];
	CalculateSolarPosition(jd, sol_pos);
	bool shoku;
	shoku = (bool)SatEclipsed(ro, sol_pos);

	//CopyVec(sol_pos,global_solpos,3);	//実験用
//	cout << "SUN(x,y,z)";
//	for(int i=0;i<3;i++) {
//		cout << sol_pos[i];
//		cout << " ";
//	}
//	cout << "\n";
//	cout << "蝕？" << shoku;
//	cout << endl;


	return 0;
}

//以下関数の遺産

/*

int test()		//もともとのメイン関数
{
	char str[2];
	char infilename[15];
	double ro[3];
	double vo[3];
        char typerun, typeinput;
        gravconsttype  whichconst;
        int whichcon;
	FILE *infile, *outfile, *outfilee;

// ----------------------------  locals  -------------------------------
        double p, a, ecc, incl, node, argp, nu, m, arglat, truelon, lonper;
	double sec,  jd, rad, tsince, startmfe, stopmfe, deltamin;
        double tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2;
	int  year; int mon; int day; int hr; int min;
	char longstr1[130];
        typedef char str3[4];
        str3 monstr[13];
        char outname[64];
	char longstr2[130];
	elsetrec satrec;

        rad = 180.0 / PI;
// ------------------------  implementation   --------------------------
strcpy(monstr[1], "Jan");
strcpy(monstr[2], "Feb");
strcpy(monstr[3], "Mar");
strcpy(monstr[4], "Apr");
strcpy(monstr[5], "May");
strcpy(monstr[6], "Jun");
strcpy(monstr[7], "Jul");
strcpy(monstr[8], "Aug");
strcpy(monstr[9], "Sep");
strcpy(monstr[10], "Oct");
strcpy(monstr[11], "Nov");
strcpy(monstr[12], "Dec");

        //typerun = 'c' compare 1 year of full satcat data
        //typerun = 'v' verification run, requires modified elm file with
        //              start, stop, and delta times
        //typerun = 'm' maunual operation- either mfe, epoch, or dayof yr also
        printf("input type of run c, v, m \n\n");
        typerun = getche();

        //typeinput = 'm' input start stop mfe
        //typeinput = 'e' input start stop ymd hms
        //typeinput = 'd' input start stop yr dayofyr
        if ((typerun != 'v') && (typerun != 'c'))
          {
            printf("input mfe, epoch (YMDHMS), or dayofyr approach, m,e,d \n\n");
            typeinput = getche();
          }
          else
            typeinput = 'e';

        printf("input which constants 721 72 84 \n");
        scanf( "%i",&whichcon );
        if (whichcon == 721) whichconst = wgs72old;
        if (whichcon == 72) whichconst = wgs72;
        if (whichcon == 84) whichconst = wgs84;

        getgravconst( whichconst, tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2 );

        // ---------------- setup files for operation ------------------
        // input 2-line element set file
        printf("input elset filename: \n");
        scanf( "%s",infilename );
        infile = fopen(infilename, "r");
        if (infile == NULL)
	  {
	    printf("Failed to open file: %s\n", infilename);
	    return 1;
	  }

        if (typerun == 'c')
            outfile = fopen("tcppall.out", "w");
          else
            {
            if (typerun == 'v')
                outfile = fopen("tcppver.out", "w");
              else
                outfile = fopen("tcpp.out", "w");
            }

//        dbgfile = fopen("sgp4test.dbg", "w");
//        fprintf(dbgfile,"this is the debug output\n\n" );

        // ----------------- test simple propagation -------------------
        while (feof(infile) == 0)
          {
            do
              {
                fgets( longstr1,130,infile);
                strncpy(str, &longstr1[0], 1);
                str[1] = '\0';
              } while ((strcmp(str, "#")==0)&&(feof(infile) == 0));

            if (feof(infile) == 0)
              {
                fgets( longstr2,130,infile);
                // convert the char string to sgp4 elements
                // includes initialization of sgp4
                twoline2rv( longstr1, longstr2, typerun, typeinput, whichconst,
                            startmfe, stopmfe, deltamin, satrec );
                fprintf(outfile, "%ld xx\n", satrec.satnum);
                printf(" %ld\n", satrec.satnum);
                // call the propagator to get the initial state vector value
                sgp4 (whichconst, satrec,  0.0, ro,  vo);

// generate .e files for stk
jd = satrec.jdsatepoch;
strncpy(outname,&longstr1[2],5);
outname[5]= '.';
outname[6]= 'e';
outname[7]= '\0';
invjday( jd, year,mon,day,hr,min, sec );
outfilee = fopen(outname, "w");
fprintf(outfilee,"stk.v.4.3 \n"); // must use 4.3...
fprintf(outfilee,"\n");
fprintf(outfilee,"BEGIN Ephemeris \n");
fprintf(outfilee," \n");
fprintf(outfilee,"NumberOfEphemerisPoints		146 \n");
fprintf(outfilee,"ScenarioEpoch	  %3i %3s%5i%3i:%2i:%12.9f \n",day,monstr[mon],
                  year,hr,min,sec );
fprintf(outfilee,"InterpolationMethod		Lagrange \n");
fprintf(outfilee,"InterpolationOrder		5 \n");
fprintf(outfilee,"CentralBody				Earth \n");
fprintf(outfilee,"CoordinateSystem			teme \n");
fprintf(outfilee,"CoordinateSystemEpoch	%3i %3s%5i%3i:%2i:%12.9f \n",day,
                  monstr[mon],year,hr,min,sec );
fprintf(outfilee,"DistanceUnit			Kilometers \n");
fprintf(outfilee," \n");
fprintf(outfilee,"EphemerisTimePosVel \n");
fprintf(outfilee," \n");
fprintf(outfilee, " %16.8f %16.8f %16.8f %16.8f %12.9f %12.9f %12.9f\n",
                 satrec.t,ro[0],ro[1],ro[2],vo[0],vo[1],vo[2]);

                fprintf(outfile, " %16.8f %16.8f %16.8f %16.8f %12.9f %12.9f %12.9f\n",
                        satrec.t,ro[0],ro[1],ro[2],vo[0],vo[1],vo[2]);

                tsince = startmfe;
                // check so the first value isn't written twice
                if ( fabs(tsince) > 1.0e-8 )
                    tsince = tsince - deltamin;

                // ----------------- loop to perform the propagation ----------------
                while ((tsince < stopmfe) && (satrec.error == 0))
                  {
                   tsince = tsince + deltamin;

                   if(tsince > stopmfe)
                       tsince = stopmfe;

                   sgp4 (whichconst, satrec,  tsince, ro,  vo);

                   if (satrec.error > 0)
                       printf("# *** error: t:= %f *** code = %3d\n",
                               satrec.t, satrec.error);

                   if (satrec.error == 0)
                     {
                       if ((typerun != 'v') && (typerun != 'c'))
                         {
                            jd = satrec.jdsatepoch + tsince/1440.0;
                            invjday( jd, year,mon,day,hr,min, sec );

                            fprintf(outfile,
                                    " %16.8f %16.8f %16.8f %16.8f %12.9f %12.9f %12.9f %5i%3i%3i %2i:%2i:%9.6f\n",
                                    tsince, ro[0],ro[1],ro[2],vo[0],vo[1],vo[2],year,mon,day,hr,min,sec );
//                            fprintf(outfile, " %16.8f %16.8f %16.8f %16.8f %12.9f %12.9f %12.9f\n",
//                                           tsince,ro[0],ro[1],ro[2],vo[0],vo[1],vo[2]);
                         }
                       else
                         {
                            jd = satrec.jdsatepoch + tsince/1440.0;
                            invjday( jd, year,mon,day,hr,min, sec );

                            fprintf(outfilee, " %16.6f %16.8f %16.8f %16.8f %12.9f %12.9f %12.9f \n",
                                           tsince*60.0,ro[0],ro[1],ro[2],vo[0],vo[1],vo[2]);

                            fprintf(outfile, " %16.8f %16.8f %16.8f %16.8f %12.9f %12.9f %12.9f",
                                           tsince,ro[0],ro[1],ro[2],vo[0],vo[1],vo[2]);

                            rv2coe(ro, vo, mu, p, a, ecc, incl, node, argp, nu, m, arglat, truelon, lonper );
                            fprintf(outfile, " %14.6f %8.6f %10.5f %10.5f %10.5f %10.5f %10.5f %5i%3i%3i %2i:%2i:%9.6f\n",
                                     a, ecc, incl*rad, node*rad, argp*rad, nu*rad,
                                     m*rad,year,mon,day,hr,min,sec);
                         }
                     } // if satrec.error == 0

                  } // while propagating the orbit

fprintf(outfilee," END Ephemeris \n");
fclose (outfilee);

              } // if not eof

          } // while through the input file

  return 0;
}  // end test

*/

/*
void CalculateSolarPosition(double jd, double *solar_vector)
{
	double mjd, year, T, M, L, e, C, O, Lsa, nu, R, eps;

	mjd=jd-2415020.0;
	year=1900+mjd/365.25;
	T=(mjd+Delta_ET(year)/86400.0)/36525.0;

	M=Modulus(358.47583+Modulus(35999.04975*T,360.0)-(0.000150+0.0000033*T)*T*T,360.0)*DEG2RAD;
	L=(Modulus(279.69668+Modulus(36000.76892*T,360.0)+0.0003025*T*T,360.0))*DEG2RAD;
	e=0.01675104-(0.0000418+0.000000126*T)*T;
	C=((1.919460-(0.004789+0.000014*T)*T)*sin(M)+(0.020094-0.000100*T)*sin(2*M)+0.000293*sin(3*M))*DEG2RAD;
	O=(Modulus(259.18-1934.142*T,360.0))*DEG2RAD;
	Lsa=Modulus(L+C-(0.00569-0.00479*sin(O))*DEG2RAD,TWOPI);
	nu=Modulus(M+C,TWOPI);
	R=1.0000002*(1.0-e*e)/(1.0+e*cos(nu));
	eps=(23.452294-(0.0130125+(0.00000164-0.000000503*T)*T)*T+0.00256*cos(O))*DEG2RAD;
	R=AU*R;

	double l,m,c,theta,epsi,t;
	t = (jd-2415020)/36525;
	l = 279.69668 + 36000.76892 * t + 0.0003025 *t*t;
	m = 358.475833 + 35999.04975 * t - 0.00015 *t*t + 0.0000033 *t*t*t;
	c = ( (1.919460 - 0.004789 * t - 0.000014 *t*t) * sin((double)((int)m))
		+ (0.020094 - 0.0001 *t) * sin((double)((int)(2*m))) + 0.000293 * sin((double)((int)(3*m))) );
	theta = l + c - 0.00556 - 0.00479*sin((double)((int)(259.18-1934.142*t)));
	epsi = 23.452294 - 0.0130125*t - 0.00000164*t*t - 0.000000503*t*t*t + 0.00256*cos((double)((int)(259.18-1934.142*t)));

	solar_vector[0]=R*cos(Lsa);
	solar_vector[1]=R*sin(Lsa)*cos(eps);
	solar_vector[2]=R*sin(Lsa)*sin(eps);
	//solar_vector->w=R;

}
*/


/*
//直交座標を極座標(球座標)へ(楕円近似なし)[不要]
int TransPolarAxis(double* pos,double* pol)
{
	double mag;
	mag = sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
	pol[0] = mag;
	pol[1] = asin(pos[2] / mag);
	pol[2] = atan2(pos[1],pos[0]);

	return 0;
}
*/

}