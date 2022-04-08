#include <iostream>
#include <cmath>
#include "Piezoelectric.h"
using namespace std;

Piezoelectric::Piezoelectric()
{
	voltage = 120;
	position = 0.0;
}

Piezoelectric::Piezoelectric(int volt, double pos)
{
	voltage = volt;
	position = pos;
}	
void Piezoelectric::SetPosition(double pos)
{
	position = pos;
}
void Piezoelectric::SetVoltage(int volt)
{
	voltage = volt;
}