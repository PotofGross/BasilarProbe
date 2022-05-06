#include <iostream>
#include <cmath>
#include "MeasureMembrane.h"
using namespace matlab::engine;
using namespace matlab::data;

double* MeasureMembrane(std::unique_ptr<MATLABEngine> matlabFuture, char& direction)
{
	Serial* SP = new Serial("\\\\.\\COM5");
	ArrayFactory dataStruct;
	double stiffness[210000];
	Piezoelectric DCPiezo(0, 0.0);
	stiffness[0]=0.0;
	for (int i=0, i<=210000, i++)
		if (IsBone(stiffness[i]) != true)
		{
			dataStruct['volt'][i] Matlab2Cpp(matlabFuture,dataStruct,i);
			ApproachSample(DCPiezo);
			Interval(direction, DCPiezo, SP);
		}
		if (IsBone(stiffness[i]) == true)
		{
			if (direction = 'r')
				direction = 'l'
			if (direction = 'l')
				direction = 'r';
		}
	}
	return stiffness;
}

void Interval(char& direction, DCPiezo) //microcontroller radial movement
{
	DCPiezo.SetVoltage(-20.0); // back off sample then interval
	switch (direction)
	{
		case 'l':
			//micrometer left
		case 'r':
			//micrometer right
	}
	DCPiezo.SetVoltage(20.0)
}

void ApproachSample(DCPiezo) //DC piezo approach
{
	DCPiezo.SetVoltage(20.0);
}

double DeflectStiff(CantileverOptics deflectDist, int samplenum) //interprets deflection, need formula
{
	for (int i=0, i<samplenum, i++)
	{
		//cantilever dimensions
		double length =0.879, width =0.11, thickness = 0.0181; //inches
		double ElasticModulus = 10; //psi
		//calc
		double stiffness[samplenum] = ((3 * ElasticModulus * width * pow(thickness, 3)) / (4 * pow(length, 3))) * deflectDist.GetResponse(samplenum);
	}
	return stiffness;
}

bool IsBone(double stiffness)
{
	if (stiffness > BONESTIFF)
		return true;
	else
		return false;
}

FutureResult<matlab::data::TypedArray> Matlab2Cpp(matlabFuture, dataStruct, idx)
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