#include "DateTime.h"
namespace stf { 
namespace datatype {

DateTime::DateTime(const DateTime &rhs){
    this->second_ = rhs.second_;
	this->minute_ = rhs.minute_;
	this->hour_ = rhs.hour_;
	this->date_ = rhs.date_;

}

// std::ostreamクラスの演算子に対するグローバルな演算子オーバーロード
std::ostream &operator << (std::ostream& out_file, const DateTime& time){
	out_file << time.dates() << "/" << time.hours() << ":" << time.minutes() << ":" << time.seconds();
	return out_file;
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */