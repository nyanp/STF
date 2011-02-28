/**
 * @file   SatelliteModel.h
 * @brief  衛星質量特性を表現するクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_SatelliteModel_h
#define stf_datatype_SatelliteModel_h

#include "StaticMatrix.h"

namespace stf { 
namespace datatype {

//! 衛星質量特性を表現するクラス．
/*! */
class SatelliteModel {
public:
	SatelliteModel(){}
	SatelliteModel(double M, StaticMatrix<3, 3> I) : I_(I), M_(M) {}
	void setI(const StaticMatrix<3, 3>& I) { I_ = I; }
	void setM(double M) { M_ = M; }
	const StaticMatrix<3, 3>& getI() const { return I_; }
	double getM() const { return M_; }
private:
	StaticMatrix<3, 3> I_;//!< 慣性テンソル(kgm2)
	double M_;//!< 質量(kg)
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_SatelliteModel_h
