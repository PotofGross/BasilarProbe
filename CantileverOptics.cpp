#include <iostream>
#include <cmath>
#include "CantileverOptics.h"
using namespace std;

CantileverOptics::CantileverOptics()
{
	double Emission = 10.0;
}
double CantileverOptics::GetResponse(int i)
{
	return Response[i];
}
