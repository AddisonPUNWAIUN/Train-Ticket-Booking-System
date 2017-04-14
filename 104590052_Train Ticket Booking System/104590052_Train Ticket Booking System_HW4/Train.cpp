#include <iostream>
#include <string>
#include "Train.h"

using namespace std;

string Train::GetTrainName()
{
	return _TRIAN_NAME;
}

double Train::ComputeTravelTime(double distance, int intermediateStops)
{
	double _distime = (distance / _SPEED) * 60;
	if (_distime - double(int(_distime)) >= 0.5) _distime = double(int(_distime)) + 1;
	else _distime = double(int(_distime));

	double Stoptime = double(intermediateStops * _STOPPING_TIME);
	return Stoptime + _distime;
}

int Train::ComputePrice(double distance)
{
	return 0;
}
