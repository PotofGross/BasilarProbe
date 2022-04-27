#include "ApproachSample.h"
#include "MeasureMembrane.h"
#include "StiffnessFrequency.h"
#include "Piezoelectric.h"
#include <iostream>
#include <string>
#include "MatlabEngine.hpp"
using namespace matlab::engine;

int main()
{
	std::unique_ptr<MATLABEngine> matlabFuture = startMATLAB();
	Piezoelectric ACPiezo(120, 0.0);
	ApproachSample();
	double* mechprop = MeasureMembrane(matlabFuture,'r');
	StiffnessFrequency(mechprop);
	ACPiezo.SetVoltage(0);
	return 0;
}