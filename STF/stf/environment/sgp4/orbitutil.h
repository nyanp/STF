#ifndef __orbit_H__
#define __orbit_H__


#include "sgp4unit.h"

namespace sgp4{

double SiderealTime(double jd);
int TransGeoToGAxis(double lon, double lat, double alt, double* pos);
int TransGAxis(double* pos,double gmst,double* gpos);
void TransECIToGeo(double gmst, double *pos, double *lon, double* lat, double* alt);
void CalculateSolarPosition(double jd, double *solar_vector);
int SatEclipsed(double *pos, double *sol, double *depth);
bool SatEclipsed(double *pos, double *sol);

//int InitOrbit(double* jdepoch);
int InitOrbit(double* jdepoch, char* tle1, char* tle2);
int OrbitMain(double stoptime,double* mag);

//int test();		//Ç‡Ç∆Ç‡Ç∆ÇÃÉÅÉCÉìä÷êî
}
#endif //__orbit_H__