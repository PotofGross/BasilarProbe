#include <iostream>
#include <cmath>
#include "MeasureMembrane.h"
#include "CantileverOptics.h"
#include "DCPiezo.h"
using namespace matlab::engine;

double* MeasureMembrane(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture, char& direction)
{
	double stiffness = 0.0;
	if (IsBone(stiffness) != true)
	{
		Matlab2Cpp(matlabFuture);
		Interval(direction);
		ApproachSample();
	}
	if (IsBone(stiffness) = true)
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

void ApproachSample() //DC piezo approach
{

}

double DeflectStiff(CantileverOptics deflectDist) //interprets deflection, need formula
{
	//cantilever dimensions
	double length =0.879, width =0.11, thickness = 0.0181; //inches
	double ElasticModulus = _________;
	//calc
	double stiffness = ((3 * ElasticModulus * width * pow(thickness, 3)) / (4 * pow(length, 3))) * deflectDist;
	return stiffness;
}

bool IsBone(double stiffness)
{
	if (stiffness > BONESTIFF)
		return true;
	else
		return false;
}

std::unique_ptr<MATLABEngine> Matlab2Cpp(FutureResult<std::unique_ptr<MATLABEngine>> matlabFuture)
{
	matlab::engine::connectMATLAB; //connect to active session
	FutureResult<matlab::data::Array> fevalAsync(const matlab::engine::String & BMStiffD1,
		const std::vector<matlab::data::Array> &args,
		const std::shared_ptr<matlab::engine::StreamBuffer> &output = std::shared_ptr<matlab::engine::StreamBuffer>(),
		const std::shared_ptr<matlab::engine::StreamBuffer> &error = std::shared_ptr<matlab::engine::StreamBuffer>());
	std::unique_ptr<MATLABEngine> matlabPtr = matlabFuture.get();
	return matlabPtr;
}