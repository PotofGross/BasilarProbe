#include "ApproachSample.h"
#include "MeasureMembrane.h"
#include "StiffnessFrequency.h"
#include "ACPiezo.h"
using namespace matlab::engine;

int main()
{
	FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture = startMatlabAsync();
	ACPiezo ACPStack(120, 0.0);
	ApproachSample();
	char direction WhereAmI();
	double* mechprop MeasureMembrane(matlabFuture, direction);
	StiffnessFrequency(mechprop);
	ACPStack.Setvoltage(0);
	return 0;
}