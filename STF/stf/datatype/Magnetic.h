#ifndef stf_datatype_MagneticField_h
#define stf_datatype_MagneticField_h

#include "StaticVector.h"
namespace stf { 
namespace datatype {
//磁束密度(T)
class MagneticField : public StaticVector<3> {
public:
	MagneticField(){}
    MagneticField(const StaticVector<3> &rhs);
    MagneticField(const Vector &rhs);
    MagneticField(const MagneticField &rhs);
    MagneticField(double m0,double m1, double m2);
	~MagneticField(){}
private:
};

//磁気モーメント(Am2)
class MagneticMoment : public StaticVector<3> {
public:
	MagneticMoment(){}
    MagneticMoment(const StaticVector<3> &rhs);
    MagneticMoment(const Vector &rhs);
    MagneticMoment(const MagneticMoment &rhs);
    MagneticMoment(double m0,double m1, double m2);
	~MagneticMoment(){}
private:
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_MagneticField_h
