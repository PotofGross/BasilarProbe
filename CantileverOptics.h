#ifndef CANTILEVEROPTICS_H
#define CANTILEVEROPTICS_H

class CantileverOptics
{
	public:
		CantileverOptics();
		~CantileverOptics();
		double GetResponse(int);
	protected:
		double Emission, Response[210000];
};


#endif