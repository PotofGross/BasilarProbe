#include "ApproachSample.h"
#include "MeasureMembrane.h"
#include "StiffnessFrequency.h"
#include "ACPiezo.h"
#include <iostream>
#include <string>
#include "MatlabEngine.hpp"
using namespace matlab::engine;

int main()
{
	FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture = startMatlabAsync();
	ACPiezo ACPStack(120, 0.0);
	ApproachSample();
	double* mechprop = MeasureMembrane(matlabFuture, 'r');
	StiffnessFrequency(mechprop);
	ACPStack.SetVoltage(0);
	return 0;
}