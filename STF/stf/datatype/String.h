/**
 * @file   String.h
 * @brief  std::stringの簡略版クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_String_h
#define stf_datatype_String_h

namespace stf {
namespace datatype {

//! std::stringの簡略版．
/*! */
class String {
public:
	String():length_(0) { value_ = new char[1]; *value_ = '\0';}
	String(const String &rhs);//copy constructor
	String(const char *cp);
	String(const char c);
	~String(){delete[] value_;}
	String &operator=(const String &);
	String &operator+=(const String &);
	inline int length() const{ return this->length_; };
	inline const char* to_char() const{ return this->value_;}
private:
	char *value_;
	int length_;
	friend bool operator == (const String&, const String&);
	friend String operator + (const String&,const String&);
};
} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_String_h
