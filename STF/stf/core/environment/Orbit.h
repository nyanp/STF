/**
 * @file   Orbit.h
 * @brief  軌道計算を行う，sgp4のラッパークラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_environment_Orbit_h
#define stf_core_environment_Orbit_h

#include "../../datatype/OrbitInfo.h"
#include "../../datatype/OrbitCalc.h"
#include "../../datatype/DateTime.h"
#include "../../datatype/Magnetic.h"
#include "../../Config.h"


namespace stf {
namespace core {
namespace environment {

//! 軌道計算を行う，sgp4のラッパークラス．
/*! */
class Orbit {
public:
	Orbit()
		: orbit_(7100000, 0.0, 0.0, util::math::PI / 2, 0.0, 0.0), starttime_(YEAR, MONTH, DATE){}
	Orbit(double a, double e, double i, double Omega, double omega, int year, int month, int day, int hour = 0, int minutes = 0, int second = 0)
		: orbit_(a, e, 0, i, Omega, omega), starttime_(year, month, day, hour, minutes, second){}
	~Orbit(){}
	void set_orbitElement(double a, double e, double i, double Omega, double omega);
	void set_orbitElement(const datatype::OrbitInfo& orbit);
	void addTime(const datatype::Time& dt);
	void addSecond(int seconds);
	void resetDateTime(const datatype::DateTime& time);
	const datatype::DateTime get_time() const { return this->starttime_ + localtime_; }
	const datatype::PositionInfo getSatellitePosition() const ;
	const datatype::OrbitInfo& getSatelliteOrbit() const ;
	const datatype::StaticVector<2> getSunVector2D() const ;
	const datatype::StaticVector<3> getSunVector3D() const ;
	const datatype::StaticVector<2> getEarthVector2D() const ;
	const datatype::StaticVector<3> getEarthVector3D() const ;
	const datatype::MagneticField getMagneticField() const ;
private:
	void updateOrbit_();
	datatype::OrbitInfo orbit_;
	const datatype::DateTime starttime_;
	datatype::Time localtime_;
};

} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_environment_Orbit_h
