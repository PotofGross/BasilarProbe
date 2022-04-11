#ifndef DCPIEZO_H
#define DCPIEZO_H
#include "Piezoelectric.h"

class DCPiezo:public Piezoelectric
{
	private:
	public:
		DCPiezo(int volt, double pos);
		~DCPiezo();
};


#endif