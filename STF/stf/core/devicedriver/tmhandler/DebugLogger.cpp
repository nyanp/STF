/**
 * @file   DebugLogger.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "DebugLogger.h"
#include "ITelemetryStoragable.h"
#include "../../../datatype/String.h"
#include "../../../util/Ostream.h"


namespace stf {
namespace core {
namespace devicedriver {
namespace tmhandler {

DebugLogger::DebugLogger(const std::string &filename, bool console_out)
: console_out_(console_out)
{
	if(filename.length() != 0)
		this->ofs_ = new std::ofstream(filename);
	else
		this->ofs_ = 0;
}

DebugLogger::DebugLogger()
: console_out_(true), ofs_(0)
{
	//引数なしの場合は標準出力にのみ表示，ログはとらない
}

DebugLogger::~DebugLogger()
{
	if(this->ofs_ != 0) delete this->ofs_;
}

void DebugLogger::logging(int value, int address)
{
   *this << value;//ロガーは書き込み先アドレスの指定を無視する   
}

void DebugLogger::logging(double value, int address)
{
   *this << value;    
}

void DebugLogger::logging(datatype::String value, int address)
{
	*this << value.to_char();
}

ITelemetryStoragable &DebugLogger::operator <<(int value)
{
	if(this->console_out_) util::cout << value << ",";
	if(this->ofs_ != 0)    *ofs_ << value << ",";
	return *this;
}

ITelemetryStoragable &DebugLogger::operator <<(double value)
{
	if(this->console_out_) util::cout << value << ",";
	if(this->ofs_ != 0)    *ofs_ << value << ",";
	return *this;
}

ITelemetryStoragable &DebugLogger::operator <<(const char* value)
{
	if(this->console_out_) util::cout << value << ",";
	if(this->ofs_ != 0)    *ofs_ << value << ",";
	return *this;
}

ITelemetryStoragable &DebugLogger::endl()
{
	if(this->console_out_) util::cout << util::endl;
	if(this->ofs_ != 0)    *ofs_ << std::endl;
	return *this;
}

} /* End of namespace stf::core::devicedriver::tmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
