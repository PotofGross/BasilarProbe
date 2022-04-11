#ifndef ACPIEZO_H
#define ACPIEZO_H
#include "Piezoelectric.h"

class ACPiezo:public Piezoelectric
{
	private:
	public:
		ACPiezo(int volt, double pos);
		~ACPiezo();
};


#endif