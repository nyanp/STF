/**
 * @file   orbitutil.h
 * @brief  NJHILSから持ってきた軌道計算関係モジュールを，sgp4名前空間でラップして使用．
 *
 * @author david vallado
 * @date   2011.02.16
 */
#ifndef __orbit_H__
#define __orbit_H__


#include "sgp4unit.h"

namespace sgp4{

double SiderealTime(double jd);
int TransGeoToGAxis(double lon, double lat, double alt, double* pos);
int TransGAxis(double* pos, double gmst, double* gpos);
void TransECIToGeo(double gmst, double *pos, double *lon, double* lat, double* alt);
void CalculateSolarPosition(double jd, double *solar_vector);
int SatEclipsed(double *pos, double *sol, double *depth);
bool SatEclipsed(double *pos, double *sol);

}
#endif //__orbit_H__