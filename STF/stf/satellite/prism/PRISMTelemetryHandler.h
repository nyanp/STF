/**
 * @file   PRISMTelemetryHandler.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_tmhandler_PRISMTelemetryHandler_h
#define stf_core_devicedriver_tmhandler_PRISMTelemetryHandler_h

#include <fstream>
#include <string>
#include "../../core/devicedriver/tmhandler/ITelemetryStoragable.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace tmhandler {

template<class T>
class PRISMTelemetryHandler : virtual public ITelemetryStoragable{
public:
    PRISMTelemetryHandler(const std::string &filename, bool console_out);
    PRISMTelemetryHandler();
    virtual ~PRISMTelemetryHandler();
    void logging(int value, int address);
    virtual void logging(double value, int address);
    virtual void logging(datatype::String value, int address);
    virtual ITelemetryStoragable &operator <<(int value);
    virtual ITelemetryStoragable &operator <<(double value);
    ITelemetryStoragable &operator <<(const char* value);
    virtual ITelemetryStoragable &endl();
 private:
    typename T::OutputStream *ofs_;
    bool console_out_;
};

template<class T>
PRISMTelemetryHandler<T>::PRISMTelemetryHandler(const std::string &filename, bool console_out)
: console_out_(console_out)
{
	if(filename.length() != 0)
		this->ofs_ = new typename T::OutputStream(filename);
	else
		this->ofs_ = 0;
}

template<class T>
PRISMTelemetryHandler<T>::PRISMTelemetryHandler()
: console_out_(true), ofs_(0)
{
	//引数なしの場合は標準出力にのみ表示，ログはとらない
}

template<class T>
PRISMTelemetryHandler<T>::~PRISMTelemetryHandler()
{
	if(this->ofs_ != 0) delete this->ofs_;
}

template<class T>
void PRISMTelemetryHandler<T>::logging(int value, int address)
{
   *this << value;//ロガーは書き込み先アドレスの指定を無視する   
}

template<class T>
void PRISMTelemetryHandler<T>::logging(double value, int address)
{
   *this << value;    
}

template<class T>
void PRISMTelemetryHandler<T>::logging(datatype::String value, int address)
{
	*this << value.to_char();
}

template<class T>
ITelemetryStoragable &PRISMTelemetryHandler<T>::operator <<(int value)
{
	if(this->console_out_) util::cout << value << ", ";
	if(this->ofs_ != 0)    *ofs_ << value << ", ";
	return *this;
}

template<class T>
ITelemetryStoragable &PRISMTelemetryHandler<T>::operator <<(double value)
{
	if(this->console_out_) util::cout << value << ", ";
	if(this->ofs_ != 0)    *ofs_ << value << ", ";
	return *this;
}

template<class T>
ITelemetryStoragable &PRISMTelemetryHandler<T>::operator <<(const char* value)
{
	if(this->console_out_) util::cout << value << ", ";
	if(this->ofs_ != 0)    *ofs_ << value << ", ";
	return *this;
}

template<class T>
ITelemetryStoragable &PRISMTelemetryHandler<T>::endl()
{
	if(this->console_out_) util::cout << util::endl;
	if(this->ofs_ != 0)    *ofs_ << util::endl;
	return *this;
}

} /* End of namespace stf::core::devicedriver::tmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_tmhandler_PRISMTelemetryHandler_h
