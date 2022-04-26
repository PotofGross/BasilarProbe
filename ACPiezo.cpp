#include "Piezoelectric.h"
#include "ACPiezo.h"
using namespace std;

ACPiezo::ACPiezo(int volt, double pos)
{
	voltage = volt;
	position = pos;
}