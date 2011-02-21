/**
 * @file   SatelliteModel.h
 * @brief  陦帶弌雉ｪ驥冗音諤ｧ繧定｡ｨ迴ｾ縺吶ｋ繧ｯ繝ｩ繧ｹ・・
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_SatelliteModel_h
#define stf_datatype_SatelliteModel_h

#include "StaticMatrix.h"

namespace stf { 
namespace datatype {

//! 陦帶弌雉ｪ驥冗音諤ｧ繧定｡ｨ迴ｾ縺吶ｋ繧ｯ繝ｩ繧ｹ・・
/*! */
class SatelliteModel {
public:
	SatelliteModel(){}
	SatelliteModel(double M, StaticMatrix<3,3> I) : I_(I),M_(M) {}
	void setI(const StaticMatrix<3,3>& I) { I_ = I; }
	void setM(double M) { M_ = M; }
	const StaticMatrix<3,3>& getI() const { return I_; }
	double getM() const { return M_; }
private:
	StaticMatrix<3,3> I_;//陦帶弌諷｣諤ｧ繝・Φ繧ｽ繝ｫ(kgm)
	double M_;//雉ｪ驥・kg)
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_SatelliteModel_h
