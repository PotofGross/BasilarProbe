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
	FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture = startMATLABAsync();
	std::unique_ptr<MATLABEngine> matlabPtr = matlabFuture.get();
	ACPiezo ACPStack(120, 0.0);
	ApproachSample();
	double* mechprop = MeasureMembrane(matlabPtr, 'r');
	StiffnessFrequency(mechprop);
	ACPStack.SetVoltage(0);
	return 0;
}