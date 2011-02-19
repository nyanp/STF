#ifndef stf_datatype_SatelliteModel_h
#define stf_datatype_SatelliteModel_h

#include <assert.h>

#include "StaticMatrix.h"


namespace stf { 
namespace datatype {

///
class SatelliteModel {
public:
	SatelliteModel(){}
	SatelliteModel(double M, StaticMatrix<3,3> I) : I_(I),M_(M) {};
	void setI(const StaticMatrix<3,3>& I) { I_ = I; }
	void setM(double M) { M_ = M; }
	const StaticMatrix<3,3>& getI() const { return I_; }
	double getM() const { assert(M_ != 0); return M_; }
private:
	//const double 
	StaticMatrix<3,3> I_;//‰q¯Šµ«ƒeƒ“ƒ\ƒ‹(kgm)
	double M_;//¿—Ê(kg)
};


} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_SatelliteModel_h
