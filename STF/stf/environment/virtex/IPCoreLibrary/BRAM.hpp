#ifndef BRAM_HPP_
#define BRAM_HPP_

//#include "../Util/assert.hpp"
#include"../../../util/stfassert.h"

namespace nj
{
namespace lib
{

class BRAM
{
public: 
	inline BRAM(unsigned int base_addr, unsigned int size);
	
	inline unsigned char operator[](unsigned int pos) const;
	inline unsigned char& operator[](unsigned int pos);
	
	template<typename T>
	void write(unsigned int addr, const T& data);
	
	template<typename T>
	void read(unsigned int addr, T& data) const;
	
	void seq_write(unsigned int addr, const unsigned char* data, unsigned int size);
	void seq_read(unsigned int addr, unsigned char* data, unsigned int size) const;
	
private:
	inline unsigned char* calc_addr_(unsigned int pos) const;

	//! BRAM領域の開始アドレス
	unsigned char* const base_;
	//! BRAN領域のサイズ
	const unsigned int size_;
};

BRAM::BRAM(unsigned int base_addr, unsigned int size)
 : base_(reinterpret_cast<unsigned char*>(base_addr)), size_(size)
{
}

unsigned char BRAM::operator [](unsigned int pos) const
{
	return *calc_addr_(pos);
}

unsigned char& BRAM::operator [](unsigned int pos)
{
	return *calc_addr_(pos);	
}

template<typename T>
void BRAM::write(unsigned int addr, const T& data)
{
	const unsigned char* temp = reinterpret_cast<const unsigned char*>(&data);
	seq_write(addr, temp, sizeof(T));
}

template<typename T>
void BRAM::read(unsigned int addr, T& data) const
{
	unsigned char* temp = reinterpret_cast<unsigned char*>(&data);
	seq_read(addr, temp, sizeof(T));
}

unsigned char* BRAM::calc_addr_(unsigned int pos) const
{
	assert(pos < size_); //読み出し位置はBRAMサイズを超えないはず!!
	return base_+pos;
}

} // nj::lib
} // nj

#endif /*BRAM_HPP_*/
