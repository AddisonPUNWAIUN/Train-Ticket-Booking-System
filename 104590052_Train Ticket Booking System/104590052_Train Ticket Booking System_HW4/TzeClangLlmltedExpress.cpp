#include<iostream>
#include "Train.h"
#include "TzeClangLlmltedExpress.h"
using namespace std;

bool TzeClangLlmltedExpress::GetIsReserved()
{
	return _isReserved;
}

int TzeClangLlmltedExpress::ComputePrice(double distance)
{
	double Price = 0;
	if (distance <= 70) {
		Price = distance * _PRICE_RATE;
		if (Price - int(Price) >= 0.5)
			Price = int(Price) + 1;
		else
			Price = int(Price);
	}
	else {
		Price = ((70 * 0.9) + distance - 70)*_PRICE_RATE;
		if (Price - int (Price) >= 0.5)
			Price = int(Price) + 1;
		else
			Price = int(Price);
	}

	if (!_isReserved) {
		Price *= 0.9;
		if (Price - int(Price) >= 0.5)
			Price = int(Price) + 1;
		else
			Price = int(Price);
	}

	return Price;
}
