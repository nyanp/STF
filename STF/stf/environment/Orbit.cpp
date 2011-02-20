/**
 * @file   Orbit.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Orbit.h"
#include "sgp4/sgp4ext.h"
#include "sgp4/sgp4unit.h"
#include "sgp4/orbitutil.h"
#include "models/igrf.h"

using namespace stf::datatype;

namespace stf {
namespace environment {

void Orbit::set_orbitElement(double a, double e, double i, double Omega, double omega)
{
	this->orbit_.a = a;
	this->orbit_.e = e;
	this->orbit_.i = i;
	this->orbit_.Omega = Omega;
	this->orbit_.omega = omega;
	this->orbit_.n = sqrt( util::math::MU / (a * a * a) );
	this->orbit_.M = this->orbit_.n * this->localtime_.total_seconds();
}

void Orbit::set_orbitElement(const datatype::OrbitInfo& orbit)
{
	this->orbit_ = orbit;
	updateOrbit_();
}

void Orbit::addSecond(int seconds)
{
	this->localtime_.add_seconds(seconds);
	updateOrbit_();
}

void Orbit::addTime(const Time& t)
{
	this->localtime_ += t;
	updateOrbit_();
}

void Orbit::updateOrbit_()
{
	this->orbit_.M = this->orbit_.n * this->localtime_.total_seconds();
}

const PositionInfo Orbit::getSatellitePosition() const {
	return TypeConverter::toPositionInfo(this->orbit_); 
}

const OrbitInfo& Orbit::getSatelliteOrbit() const { 
	return orbit_; 
} 

const StaticVector<2> Orbit::getSunVector2D() const { 
	return OrbitCalc::getSunDirection2D(this->starttime_ + this->localtime_); 
}

const StaticVector<3> Orbit::getSunVector3D() const { 
	return OrbitCalc::getSunDirection3D(this->starttime_ + this->localtime_); 
}

const StaticVector<2> Orbit::getEarthVector2D() const {
	return OrbitCalc::getEarthDirection2D(TypeConverter::toPositionInfo(this->orbit_));
}

const StaticVector<3> Orbit::getEarthVector3D() const {
	return OrbitCalc::getEarthDirection3D(TypeConverter::toPositionInfo(this->orbit_));
}

const MagneticField Orbit::getMagneticField() const {
	//外部のigrf.hを使って磁場計算．外部ファイルigrf10.coefが無いとプログラムが停止するので注意．
	return OrbitCalc::getMagneticFieldDirection(this->getSatellitePosition(),this->starttime_ + this->localtime_);
}

} /* End of namespace stf::environment */
} /* End of namespace stf */
