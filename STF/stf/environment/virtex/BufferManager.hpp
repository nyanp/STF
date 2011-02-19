#ifndef BUFFER_MANAGER_HPP_
#define BUFFER_MANAGER_HPP_

#include "./Util/RingBuffer.hpp"
#include "./Util/TextBuffer.hpp"

namespace nj
{
	
class BufferManager
{
public:
	BufferManager();
	
	static const unsigned int COUT_BUF_DEPTH = 256;
	static const unsigned int CIN_BUF_DEPTH = 256;
	
	nj::util::RingBuffer<COUT_BUF_DEPTH>& cout_rb(){ return cout_rb_; }
	nj::util::TextBuffer<CIN_BUF_DEPTH>& cin_buf(){ return cin_tb_; }
private:
	nj::util::RingBuffer<COUT_BUF_DEPTH> cout_rb_;

	nj::util::RingBuffer<CIN_BUF_DEPTH> cin_rb_;
	nj::util::TextBuffer<CIN_BUF_DEPTH> cin_tb_;
};

}

#endif /*BUFFER_MANAGER_HPP_*/
