#include "BRAM.hpp"

namespace nj
{
namespace lib
{

void BRAM::seq_write(unsigned int addr, const unsigned char* data, unsigned int size)
{
	for(unsigned int i=0; i<size; ++i)
	{
		(*this)[addr+i] = data[i];
	}
}

void BRAM::seq_read(unsigned int addr, unsigned char* data, unsigned int size) const
{
	for(unsigned int i=0; i<size; ++i)
	{
		data[i] = (*this)[addr+i];
	}
}

} // nj::lib	
} // nj
