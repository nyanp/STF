/**
 * @file   Quaternion.h
 * @brief  4元数を表現するクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_Quaternion_h
#define stf_datatype_Quaternion_h

#include "StaticVector.h"
namespace stf { 
namespace datatype {

//! 4元数を表現するクラス．q0がcosと定義されている点に注意．
/*! */
class Quaternion : public StaticVector<4> {
public:
    Quaternion();
    Quaternion(const StaticVector<4> &rhs);
    Quaternion(const Quaternion &rhs);
    Quaternion(double q0,double q1, double q2, double q3);
	~Quaternion(){}
	//! 共役を取得する．
    Quaternion conjugate() const;
	//! ノルムを1に調整する．
	virtual void normalize();
	//! n-ノルムを取得．
	virtual double norm(int n) const;
private:
	friend inline const Quaternion operator -(const Quaternion&,const Quaternion&);
};

inline const Quaternion operator - (const Quaternion& vec1, const Quaternion& vec2){
	Quaternion temp = vec1;
	if(vec1[0] * vec2[0] < 0){
		for(int i = 0; i < 4; i++)
			temp[i] = -temp[i] - vec2[i];
	}else{
		for(int i = 0; i < 4; i++)
			temp[i] = temp[i] - vec2[i];
	}
	return temp;
}

//Quaternionの積
inline Quaternion operator * (const Quaternion& q1, const Quaternion& q2){
	Quaternion q;
	q[0] = q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3];
	q[1] = q1[0] * q2[1] + q2[0] * q1[1] + q1[2] * q2[3] - q1[3] * q2[2];
	q[2] = q1[0] * q2[2] + q2[0] * q1[2] + q1[3] * q2[1] - q1[1] * q2[3];
	q[3] = q1[0] * q2[3] + q2[0] * q1[3] + q1[1] * q2[2] - q1[2] * q2[1];
	return q;
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_Quaternion_h
