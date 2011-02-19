#ifndef stf_datatype_String_h
#define stf_datatype_String_h

//簡単な機能のみを実行するstd::stringの簡略版．
namespace stf {
namespace datatype {

class String {
private:
	char *value_;
	int length_;
	friend bool operator == (const String&, const String&);
	friend String operator + (const String&,const String&);
public:
	String():length_(0) { value_ = new char[1]; *value_ = '\0';}
	String(const String &rhs);//copy constructor
	String(const char *cp);
	String(const char c);
	~String(){delete[] value_;}
	String &operator=(const String &);
	String &operator+=(const String &);
	inline int length() const{ return this->length_; };
	inline const char* toChar() const{ return this->value_;}
};
} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_String_h
