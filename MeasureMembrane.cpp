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
	connectMATLAB(); //connect to active session

	StructArray my_matlab_struct = matlab->feval(u"bmCollectD1");
	ArrayDimensions dims = my_matlab_struct.getDimensions();
	size_t numFields = my_matlab_struct.getNumberOfFields();

	Range<matlab::data::ForwardIterator, matlab::data::MATLABFieldIdentifier const> fields = my_matlab_struct.getFieldNames();

	for (int i = 0; i < numFields; i++) {
		TypedArray<double> data = my_matlab_struct[0][fields.begin()[i]]; // [0] for the first element of the structure. Iterates over the fields.
		ArrayDimensions data_dims = data.getDimensions();
		for (int j = 0; j < data_dims[0]; j++) {
			for (int k = 0; k < data_dims[1]; k++) {
				std::cout << data[j][k] << " ";
			}
			std::cout << std::endl;
		}
	}
}
}