#ifndef MEASUREMEMBRANE_H
#define MEASUREMEMBRANE_H
#include "CantileverOptics.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
using namespace matlab::engine;

const double BONESTIFF = 100.00;
double* MeasureMembrane(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture, char&);
char WhereAmI();
void Interval(char&);
void ApproachSample();
double DeflectStiff(CantileverOptics deflectDist);
bool IsBone(double);
std::unique_ptr<MATLABEngine> Matlab2Cpp(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture);

#endif