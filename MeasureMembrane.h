#ifndef MEASUREMEMBRANE_H
#define MEASUREMEMBRANE_H
#include "CantileverOptics.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
using namespace matlab::engine;
using namespace matlab::data;

const double BONESTIFF = 100.00;
double* MeasureMembrane(std::unique_ptr<MATLABEngine> matlabFuture, char&);
void Interval(char&);
void ApproachSample(std::unique_ptr<MATLABEngine> matlabFuture);
double DeflectStiff(CantileverOptics deflectDist, int);
bool IsBone(double);
FutureResult<matlab::data::TypedArray> Matlab2Cpp(std::unique_ptr<MATLABEngine> matlabFuture, StructArray&);

#endif

