#include "math.h"

namespace stf {
namespace util {
namespace math { 
	double sqrt(double s){
		double x = 0.5 * s;
		double last_x = 0.0;
		while( x != last_x ){
			last_x = x;
			x = ( x + s / x ) * 0.5;
		}
		return x;
	}
	double abs(double s){
		return s < 0 ? -s : s;
	}

	double Sin(double s){
		return sin(s);
	}

	double Cos(double s){
		return cos(s);
	}

	double Align(double s, double align){
		if(abs(s) < align){
			return 0;
		}
		return s;
	}
}
}
}