#ifndef PIEZOELECTRIC_H
#define PIEZOELECTRIC_H

class Piezoelectric
{
	private:
		int voltage;
		double position;
	public:
		Piezoelectric();
		Piezoelectric(int volt, double pos);
		~Piezoelectric();
		void SetPosition(double);
		void SetVoltage(int);
};


#endif