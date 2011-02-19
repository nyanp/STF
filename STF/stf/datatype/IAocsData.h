/**
 * @file   IAocsData.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_IAocsData_h
#define stf_datatype_IAocsData_h

#include "ITelemetable.h"

namespace stf { 
namespace datatype {

class Time;

class IAocsData : public ITelemetable{
public:
	virtual void normalize() = 0;
	virtual void reset() = 0;
	//virtual const int* serialize() const { return 0;}//double型の配列にオブジェクトをシリアライズする．デフォルトの実装は0
    virtual ~IAocsData() { }
protected:

};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_IAocsData_h
