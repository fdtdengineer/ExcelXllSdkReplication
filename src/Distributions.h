#ifndef Distributions_h
#define Distributions_h


#include <windows.h> 
#include <math.h> 
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <ctype.h>
#include <windows.h>
#include "../xlcall.h"
#include "../framewrk.h"

extern const double PI;


__declspec(dllexport) double WINAPI ND(double x);
__declspec(dllexport) double WINAPI CND(double x);
__declspec(dllexport) double WINAPI CBND(double x, double y, double rho);


double __stdcall PoissonDistribution(double x, long k);
double NormalCDFInverse(double p);
double RationalApproximation(double t);



#endif