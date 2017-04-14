#include <iostream>
#include "Train.h"
#include "LocalTraIn.h"
using namespace std;

bool LocalTraIn::GetIsReserved()
{
	return false;
}

int LocalTraIn::ComputePrice(double distance)
{
	int Price;
	if (distance <= 10) return 11;

	if (distance*_PRICE_RATE - double(int(distance*_PRICE_RATE)) >= 0.5)
		Price = int(distance*_PRICE_RATE) + 1;
	else
		Price = int(distance*_PRICE_RATE);

	return Price;
}
