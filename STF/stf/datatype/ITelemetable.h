#ifndef stf_datatype_ITelemetable_h
#define stf_datatype_ITelemetable_h

namespace stf {
namespace datatype {

class ITelemetable {
public:
    virtual const double* toStream() const = 0;
	virtual int getStreamLength() const = 0;
    virtual ~ITelemetable() { }
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_ITelemetable_h
