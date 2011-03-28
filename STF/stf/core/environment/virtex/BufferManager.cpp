/**
 * @file   BufferManager.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
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
