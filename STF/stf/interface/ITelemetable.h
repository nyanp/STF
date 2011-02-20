/**
 * @file   ITelemetable.h
 * @brief  テレメトリを生成可能なオブジェクトに対するインターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_interface_ITelemetable_h
#define stf_interface_ITelemetable_h

namespace stf {
namespace interface {

class ITelemetable {
public:
    virtual const double* toStream() const = 0;
	virtual int getStreamLength() const = 0;
    virtual ~ITelemetable() { }
};

} /* End of namespace stf::interface */
} /* End of namespace stf */

#endif // stf_interface_ITelemetable_h
