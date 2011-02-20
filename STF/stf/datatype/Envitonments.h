/**
 * @file   Envitonments.h
 * @brief  回路上の物理量を表すクラス群．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_Environments_h
#define stf_datatype_Environments_h

#include <assert.h>
#include "Scalar.h"

namespace stf { 
namespace datatype {

//! 電流を表すクラス．
/*! */
class Current : public Scalar {
public:
	Current() {}
	Current(double value) : Scalar(value) {}
	Current(const Current& rhs) : Scalar(rhs.value_){}
	Current& operator = (const Current& rhs) { value_ = rhs.value_; return *this;}
	~Current(){}
private:
};

//! 電圧を表すクラス．
/*! */
class Voltage : public Scalar {
public:
	Voltage() {}
	Voltage(double value) : Scalar(value) {}
	Voltage(const Voltage& rhs) : Scalar(rhs.value_){}
	Voltage& operator = (const Voltage& rhs) { value_ = rhs.value_; return *this;}
	~Voltage(){}
private:
};

//! 温度を表すクラス．
/*! */
class Temperature : public Scalar {
public:
	Temperature() {}
	Temperature(double value) : Scalar(value) {}
	Temperature(const Temperature& rhs) : Scalar(rhs.value_){}
	Temperature& operator = (const Temperature& rhs) { value_ = rhs.value_; return *this;}
	~Temperature(){}
private:
};


} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_Environments_h
