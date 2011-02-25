/**
 * @file   TypeConverter.cpp
 * @brief  単位や姿勢表現の相互変換を行うユーティリティ．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include <cmath>//TBD!

#include "DCM.h"
#include "EulerAngle.h"
#include "Quaternion.h"
#include "TypeConverter.h"
#include "../util/Ostream.h"

namespace stf {
namespace datatype {

Quaternion TypeConverter::toQuaternion(const DCM &dcm)
{
	DCM dcm_n = dcm;
	dcm_n.normalize();

	Quaternion q;
	q[0] = 0.5 * sqrt(1 + dcm_n[0][0] + dcm_n[1][1] + dcm_n[2][2]);
	if(q[0] > 0){
		q[1] = (dcm_n[1][2] - dcm_n[2][1]) / (4 * q[0]);
		q[2] = (dcm_n[2][0] - dcm_n[0][2]) / (4 * q[0]);
		q[3] = (dcm_n[0][1] - dcm_n[1][0]) / (4 * q[0]);
	}else{//q0 = 0のとき
		q[3] = sqrt(-(dcm_n[0][0] + dcm_n[1][1]) / 2);
		q[2] = sqrt(-(dcm_n[0][0] + dcm_n[2][2]) / 2);
		q[1] = sqrt(-(dcm_n[1][1] + dcm_n[2][2]) / 2);
	}
	return q;
}



DCM TypeConverter::toDCM(const Quaternion &q)
{
	Quaternion q_n = q;
	q_n.normalize();
	DCM d;//Z-Y-Xの順に回転する回転行列とする
	d[0][0] = q_n[0] * q_n[0] + q_n[1] * q_n[1] - q_n[2] * q_n[2] - q_n[3] * q_n[3];
	d[0][1] = 2 * (q_n[1] * q_n[2] + q_n[0] * q_n[3]);
	d[0][2] = 2 * (q_n[1] * q_n[3] - q_n[0] * q_n[2]);
	d[1][0] = 2 * (q_n[1] * q_n[2] - q_n[0] * q_n[3]);
	d[1][1] = q_n[0] * q_n[0] - q_n[1] * q_n[1] + q_n[2] * q_n[2] - q_n[3] * q_n[3];
	d[1][2] = 2 * (q_n[2] * q_n[3] + q_n[0] * q_n[1]);
	d[2][0] = 2 * (q_n[1] * q_n[3] + q_n[0] * q_n[2]);
	d[2][1] = 2 * (q_n[2] * q_n[3] - q_n[0] * q_n[1]);
	d[2][2] = q_n[0] * q_n[0] - q_n[1] * q_n[1] - q_n[2] * q_n[2] + q_n[3] * q_n[3];
	return d;
}

DCM TypeConverter::toDCM(const EulerAngle &euler_angle)
{
	double cos0 = cos(euler_angle[2]);
	double cos1 = cos(euler_angle[1]);
	double cos2 = cos(euler_angle[0]);
	double sin0 = sin(euler_angle[2]);
	double sin1 = sin(euler_angle[1]);
	double sin2 = sin(euler_angle[0]);

	DCM d;//Z-Y-Xの順に回転する回転行列とする
	d[0][0] = cos1 * cos2;                      d[0][1] = cos1 * sin2;                      d[0][2] = -sin1;
	d[1][0] = sin0 * sin1 * cos2 - cos0 * sin2; d[1][1] = sin0 * sin1 * sin2 + cos0 * cos2; d[1][2] = sin0 * cos1;
	d[2][0] = cos0 * sin1 * cos2 + sin0 * sin2; d[2][1] = cos0 * sin1 * sin2 - sin0 * cos2; d[2][2] = cos0 * cos1;

	return d;
}

EulerAngle TypeConverter::toEulerAngle(const DCM &dcm)
{
	DCM dcm_n = dcm;
	dcm_n.normalize();

	EulerAngle e;
	e[1] = asin(-dcm_n[0][2]);
	if(cos(e[1]) != 0){
		e[0] = atan2(dcm_n[0][1], dcm_n[0][0]);
		e[2] = atan2(dcm_n[1][2], dcm_n[2][2]);
	}else {
		e[2] = 0;
		e[0] = atan2(-dcm_n[1][0], dcm_n[2][0]);
	}
	return e;
}


DCM TypeConverter::toDCM(double z_deg, double y_deg, double x_deg)
{
    datatype::EulerAngle e;
    e[0] = z_deg * util::math::DEG2RAD;
    e[1] = y_deg * util::math::DEG2RAD;
    e[2] = x_deg * util::math::DEG2RAD;
    return TypeConverter::toDCM(e);
}

StaticVector<2> TypeConverter::toPolar(const StaticVector<3> &vec){
	StaticVector<2> v;
	double phi = atan2(vec[1],vec[0]);
	double theta;
	if(sin(phi) != 0){
		theta = atan2(vec[1] / sin(phi), vec[2]);
	}else{
		theta = atan2(vec[0], vec[2]);
	}
	v[0] = theta;
	v[1] = phi;
	return v;
}

StaticVector<3> TypeConverter::toRectangular(const StaticVector<2> &vec){
	StaticVector<3> v;
	v[0] = sin(vec[0]) * cos(vec[1]);
	v[1] = sin(vec[0]) * sin(vec[1]);
	v[2] = cos(vec[0]);
	return v;
}

OrbitInfo TypeConverter::toOrbitInfo(const PositionInfo &pos)
{
	OrbitInfo o;
	double v = pos.velocity.norm(2);
	double r = pos.position.norm(2);
	o.a =  util::math::MU / ( ( 2 * util::math::MU / r )- v * v );

	StaticVector<3> h  = pos.position % pos.velocity;//外積

	o.i = acos( h[2] / h.norm(2) );
	double sin = h[0] / sqrt(h[0] * h[0] + h[1] * h[1]);
	double cos = -h[1] / sqrt(h[0] * h[0] + h[1] * h[1]);

	o.Omega = atan2(sin , cos);
	o.e = sqrt( util::math::Align(1 - h.norm(2) * h.norm(2) / ( util::math::MU * o.a ) ) );

	if(o.e != 0){
	double cosE = (o.a - r) / ( o.a * o.e );
	double sinE = (pos.position * pos.velocity) / ( o.e * sqrt( util::math::MU * o.a ) );
	o.M = atan2(sinE, cosE) - o.e * sinE;
	}
	else{//離心率0のとき，近点離角は定義できない
		o.M = 0;
	}
	double sinO = pos.position[2] / ( r * util::math::Sin(o.i) );
	double cosO = (pos.position[0] * util::math::Cos(o.Omega) + pos.position[1] * util::math::Sin(o.Omega) ) / r;
	o.omega = atan2(sinO, cosO);
	o.n = 0;//位置情報だけでは決まらないが，0を入れている
	return o;
}

PositionInfo TypeConverter::toPositionInfo(const OrbitInfo &o)
{
	double E = o.M - o.e * sin(o.M);
	for(int i = 0; i < 5; i++){
		E = E - ( E - o.e * sin(E) - o.M) / ( 1 - o.e * cos(o.e) );
	}
	StaticMatrix<2,2> m1;
	StaticMatrix<3,2> m2;

	m1[0][0] = cos(o.omega); m1[0][1] = -sin(o.omega);
	m1[1][0] = sin(o.omega); m1[1][1] = cos(o.omega);

	m2[0][0] = cos(o.Omega); m2[0][1] = -sin(o.Omega) * cos(o.i);
	m2[1][0] = sin(o.Omega); m2[1][1] = cos(o.Omega) * cos(o.i);
	m2[2][0] = 0           ; m2[2][1] = sin(o.i);

	StaticVector<2> v;
	v[0] = o.a * (cos(E) - o.e);
	v[1] = o.a * sin(E) * sqrt(1 - o.e * o.e);
	StaticVector<2> v2;
	v2[0] = -sin(E);
	v2[1] = cos(E) * sqrt(1 - o.e * o.e);

	PositionInfo p;
	p.position = m2 * m1 * v;
	p.velocity = (sqrt(o.a * util::math::MU) / (o.a * (1 - o.e * cos(E)))) * m2 * m1 * v2;
	return p;
}



} /* End of namespace stf::datatype */
} /* End of namespace stf */
