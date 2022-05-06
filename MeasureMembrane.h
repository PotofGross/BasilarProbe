#ifndef MEASUREMEMBRANE_H
#define MEASUREMEMBRANE_H
#include "CantileverOptics.h"
#include "Piezoelectric.h"
#include "SerialPort.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
using namespace matlab::engine;
using namespace matlab::data;

const double BONESTIFF = 100.00;
double* MeasureMembrane(std::unique_ptr<MATLABEngine> matlabFuture, char&);
void Interval(char&, Piezoelectric, Serial);
void ApproachSample(Piezoelectric);
double DeflectStiff(CantileverOptics deflectDist, int);
bool IsBone(double);
FutureResult<matlab::data::TypedArray> Matlab2Cpp(std::unique_ptr<MATLABEngine> matlabFuture, StructArray&, int idx);

#endif

