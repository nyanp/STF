/**
 * @file   Time.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Time.h"
namespace stf { 
namespace datatype {
Time::Time()
{
    this->seconds_ = 0;
    this->milliseconds_ = 0;
}

Time::Time(const Time &rhs){
    this->seconds_ = rhs.seconds_;
    this->milliseconds_ = rhs.milliseconds_;
}

Time::Time(int second, double millisecond)
: seconds_(second),milliseconds_(millisecond)
{
	if(milliseconds_ >= 1000){
		int u = (int)(this->milliseconds_ / 1000);
		this->seconds_ += u;
		this->milliseconds_ -= u * 1000;  
	}
}

Time::~Time()
{
}
// std::ostreamクラスの演算子に対するグローバルな演算子オーバーロード
std::ostream &operator << (std::ostream& out_file, const Time& time){
    out_file << time.seconds_ << ":" << time.milliseconds_;
	return out_file;
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */