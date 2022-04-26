#include <iostream>
#include <cmath>
#include "MeasureMembrane.h"
#include "CantileverOptics.h"
#include "Piezoelectric.h"
using namespace matlab::engine;
using namespace matlab::data;

double* MeasureMembrane(std::unique_ptr<MATLABEngine> matlabFuture, char& direction)
{
	ArrayFactory dataStruct;
	double stiffness = 0.0;
	if (IsBone(stiffness) != true)
	{
		dataStruct Matlab2Cpp(matlabFuture,dataStruct);
		Interval(direction);
		ApproachSample(matlabFuture);
	}
	if (IsBone(stiffness) == true)
	{
		if (direction = 'r')
			direction = 'l';
		if (direction = 'l')
			direction = 'r';
	}
	return stiffness;
}

void Interval(char& direction) //microcontroller radial movement
{
	// back off sample then interval
	switch (direction)
	{
		case 'l':

		case 'r':

	}
}

void ApproachSample(std::unique_ptr<MATLABEngine> matlabFuture) //DC piezo approach
{
	Piezoelectric DCPiezo(10, 0.0);

}

double DeflectStiff(CantileverOptics deflectDist, int samplenum) //interprets deflection, need formula
{
	//cantilever dimensions
	double length =0.879, width =0.11, thickness = 0.0181; //inches
	double ElasticModulus = 10; //psi
	//calc
	double stiffness = ((3 * ElasticModulus * width * pow(thickness, 3)) / (4 * pow(length, 3))) * deflectDist.GetResponse(samplenum);
	return stiffness;
}

bool IsBone(double stiffness)
{
	if (stiffness > BONESTIFF)
		return true;
	else
		return false;
}

FutureResult<matlab::data::TypedArray> Matlab2Cpp(std::unique_ptr<MATLABEngine> matlabFuture, StructArray& dataStruct)
{
	matlab::engine::connectMATLAB(); //connect to active session
	StructArray(const StructArray& dataStruct);
	std::vector<double> bc{ 10, 13 };
	std::vector<matlab::data::Array> args({
	  factory.CreateScalar<double>(7),
	  factory.CreateArray({ 1, 2 }, bc.cbegin(), bc.cend())
		});

	matlab::data::TypedArray<double> results = matlabPtr->feval(u"simple_fun1", args); // Run simple_fun1

	std::cout << "Sum: " << results[0][0] << std::endl;
	std::cout << "Prod: " << results[0][1] << std:endl;
	std::cout << "Three: " << results[1][0] << std::endl;
}