/**
 * @file   Time.h
 * @brief  経過時間を表すクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_Time_h
#define datatype_Time_h
#include"../util/stfassert.h"

namespace stf { 
namespace datatype {

//! 経過時間を表すクラス．
/*! 正の時間（seconds >= 0）のみ対応しているため，コンストラクタに負値を与えたときの挙動は不定 */
class Time {
public:
	Time() : seconds_(0), milliseconds_(0) {}
	Time(const Time &rhs) : seconds_(rhs.seconds_), milliseconds_(rhs.milliseconds_) {}
    Time(int second, double millisecond) : seconds_(second), milliseconds_(millisecond) {
		stf_assert(second >= 0);
		while(milliseconds_ >= 1000){
			seconds_ ++;
			milliseconds_ -= 1000;  
		}
	}
	~Time(){}

    inline void add_seconds(int seconds);
    inline void add_milliseconds(double milliSeconds);
	inline int seconds() const { return this->seconds_; }
	inline double milliseconds() const { return this->milliseconds_; }
    inline double total_milliseconds() const ;
    inline double total_seconds() const;
    inline void clear();
    inline Time &operator=(const Time &rhs);
    inline Time &operator+=(const Time &rhs);
    inline Time &operator-=(const Time &rhs);
    inline Time &operator/=(int rhs);
    inline Time &operator*=(int rhs);
private:
    friend inline bool operator ==(const Time&, const Time&);
    friend inline bool operator !=(const Time&, const Time&);
    friend inline bool operator > (const Time&, const Time&);
    friend inline bool operator < (const Time&, const Time&);
    friend inline bool operator >=(const Time&, const Time&);
    friend inline bool operator <=(const Time&, const Time&);
	friend inline const Time operator +(const Time&, const Time&);
	friend inline const Time operator -(const Time&, const Time&);
	friend inline const Time operator *(int, const Time&);
	friend inline const Time operator *(const Time&, int);
	friend inline const Time operator /(const Time&, int);
    int seconds_;
    double milliseconds_;
};

////////////////////////////////
//  Inline Methods for Time //
////////////////////////////////


inline void Time::add_seconds(int seconds)
{
    this->seconds_ += seconds;
    stf_assert(this->seconds_ >= 0);
}

inline void Time::add_milliseconds(double milliSeconds)
{
    this->milliseconds_ += milliSeconds;
    int u = (int)(this->milliseconds_ / 1000);
    this->seconds_ += u;
    this->milliseconds_ -= u * 1000;  
    stf_assert(this->seconds_ >= 0);
}

inline double Time::total_milliseconds() const 
{
    return 1000 * this->seconds_ + this->milliseconds_;
}

inline void Time::clear()
{
    this->seconds_ = 0;
    this->milliseconds_ = 0.0;
}

inline double Time::total_seconds() const 
{
    return this->seconds_ + 0.001 * this->milliseconds_;
}

inline Time &Time::operator+=(const Time &rhs){
    this->milliseconds_ += rhs.milliseconds_;
    if(this->milliseconds_ > 1000.0){//桁上がり
        this->seconds_ ++;
        this->milliseconds_ -= 1000;
    }else if(this->milliseconds_ < 0.0){
        this->seconds_ --;
        this->milliseconds_ += 1000;
    }
    this->seconds_ += rhs.seconds_;
    stf_assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator-=(const Time &rhs){
    this->milliseconds_ -= rhs.milliseconds_;
    if(this->milliseconds_ > 1000.0){//桁上がり
        this->seconds_ ++;
        this->milliseconds_ -= 1000;
    }else if(this->milliseconds_ < 0.0){
        this->seconds_ --;
        this->milliseconds_ += 1000;
    }
    this->seconds_ -= rhs.seconds_;
    stf_assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator/=(int rhs){
    int r = this->seconds_ % rhs;
    this->seconds_ /= rhs;
    this->milliseconds_ += r * 1000;
    this->milliseconds_ /= rhs;
    stf_assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator*=(int rhs){
    this->seconds_ *= rhs;
    this->milliseconds_ *= rhs;
    int u = (int)(this->milliseconds_ / 1000);
    this->seconds_ += u;
    this->milliseconds_ -= u * 1000;
    stf_assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator=(const Time &rhs){
    this->seconds_ = rhs.seconds_;
    this->milliseconds_ = rhs.milliseconds_;
    return *this;
}

inline const Time operator + (const Time& time1, const Time& time2){
	Time temp = time1;
	temp += time2;
	return temp;
}

inline const Time operator - (const Time& time1, const Time& time2){
	Time temp = time1;
	temp -= time2;
	return temp;
}

inline const Time operator * (const Time& time, int factor){
	Time temp = time;
	return temp *= factor;
}

inline const Time operator * (int factor, const Time& time){
	return time * factor;
}

inline const Time operator / (const Time& time, int factor){
	Time temp = time;
	return temp /= factor;
}

inline bool operator==(const Time &time1, const Time &time2){
    if(time1.milliseconds_ == time2.milliseconds_ && time1.seconds_ == time2.seconds_) return true;
    return false;
}

inline bool operator!=(const Time &time1, const Time &time2){
    return !(time1 == time2);
}

inline bool operator>(const Time &time1, const Time &time2){
    if(time1.seconds_ > time2.seconds_){
        return true;
    }else if((time1.seconds_ == time2.seconds_) && (time1.milliseconds_ > time2.milliseconds_)){
        return true;
    }
    return false;
}

inline bool operator>=(const Time &time1, const Time &time2){
    if(time1.seconds_ > time2.seconds_){
        return true;
    }else if((time1.seconds_ == time2.seconds_) && (time1.milliseconds_ >= time2.milliseconds_)){
        return true;
    }
    return false;
}

inline bool operator<(const Time &time1, const Time &time2){
    return !(time1 > time2);
}

inline bool operator<=(const Time &time1, const Time &time2){
    return !(time1 >= time2);
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
#endif // datatype_Time_h
