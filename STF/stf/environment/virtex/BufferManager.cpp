#include "BufferManager.hpp"
using nj::util::RingBuffer;
using nj::util::DROP_OLDEST;
using nj::util::DROP_NEWEST;

namespace nj
{

BufferManager::BufferManager()
 : cout_rb_(DROP_OLDEST), cin_rb_(DROP_OLDEST), cin_tb_(cin_rb_)
{
}

}
