#ifndef MEASUREMEMBRANE_H
#define MEASUREMEMBRANE_H
#include "CantileverOptics.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
using namespace matlab::engine;

const double BONESTIFF = 100.00;
double* MeasureMembrane(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture, char&);
void Interval(char&);
void ApproachSample(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture);
double DeflectStiff(CantileverOptics deflectDist);
bool IsBone(double);
std::unique_ptr<MATLABEngine> Matlab2Cpp(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture);

#endif