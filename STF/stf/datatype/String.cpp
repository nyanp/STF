/**
 * @file   String.cpp
 * @brief  std::stringの簡略版クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "String.h"

namespace stf {
namespace datatype {

namespace {
//C99 format string functions via http://libc.blog47.fc2.com/
int strlen(const char* s){
  register const char* ss;
  for (ss = s; *ss != '\0'; ss++);
  return ss - s;
}

//文字列コピー関数．s1,s2のアドレスが重複していた場合の動作は未定義．
char *strcpy(char * s1, const char * s2)
{
  for (register char *ss = s1; (*ss = *s2) != '\0'; ss++, s2++)
    ;
  return s1;
}

char *strncpy(char *  s1, const char *  s2, size_t n)
{
  register char *ss, *t;
  for (ss = s1, t = ss + n;
      ss != t && (*ss = *s2) != '\0';
      ss++, s2++)
    ;
  for (; ss != t; ss++)
    *ss = '\0';
  return s1;
}

int strcmp(const char *s1, const char *s2)
{
  register const unsigned char *ss1, *ss2;
  for (ss1 = (const unsigned char*)s1, ss2 = (const unsigned char*)s2;
       *ss1 == *ss2 && *ss1 != '\0';
       ss1++, ss2++)
    ;
  return *ss1 - *ss2;
}
}//end of anonymous namespace

String::String(const String &rhs) : length_(rhs.length_){
	if (length_) {
		value_ = new char[length_+1];
		strncpy(value_, rhs.value_, length_);
		*(value_ + length_) = '\0';
	} else {
		value_ = new char[1];
		*value_ = '\0';
	}
}

String::String(const char *cp){
    if (cp == 0)
		length_ = 0;
    else
        length_ = strlen(cp);

    if (length_ == 0)
		value_ = 0;
    else {
        value_ = new char [length_+1];
        strcpy(value_, cp);
    }
}

String::String(const char c) : length_(1){
	value_ = new char[2];
	value_[0] = c;
	value_[1] = '\0';
}

String &String::operator+=(const String &s){
	char* c = new char[this->length_ + s.length_ + 1];
	
	if(length_)
		strcpy(c,this->value_);

	delete [] value_;

	if(s.length_)
		strcpy(&c[length_], s.value_);

	this->value_ = new char[this->length_ + s.length_ + 1];
	strcpy(value_,c);

	this->length_ += s.length_;
	return *this;
}

String &String::operator=(const String &rhs){
   if (this == &rhs)
        return *this;   // string = string の場合

    delete [] value_;

	if (rhs.length_)  {
        value_ = new char[rhs.length_+1];
        length_ = rhs.length_;
		strcpy(value_, rhs.value_);
    }
    else {
        value_ = new char[1];
		*value_ = '\0';
        length_ = 0;
    }
    return *this;
}

bool operator == (const String &s1, const String &s2){
	if(strcmp(s1.value_,s2.value_) == 0) return true;
	return false;
}

String operator + (const String &s1,const String &s2){
    String temp = s1;
    return temp += s2;
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
