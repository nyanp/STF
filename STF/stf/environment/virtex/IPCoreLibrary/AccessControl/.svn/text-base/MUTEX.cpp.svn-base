/*!
  \file   MUTEX.cpp
  \author TAKISAWA Jun'ichi
  \date   Sun Apr 11 21:53:37 2010
  
  \brief  MUTEX.hppの実装
*/
#include "MUTEX.hpp"

#include <xparameters.h>

namespace nj
{
namespace lib
{

volatile unsigned int & MUTEX::MUTEX_ = 
	*reinterpret_cast<volatile unsigned int*>(XPAR_PLB_MUTEX_SPLB0_BASEADDR);

unsigned int MUTEX::lock_counter_ = 0;

}
}
