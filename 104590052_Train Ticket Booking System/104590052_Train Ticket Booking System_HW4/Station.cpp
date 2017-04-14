#include <iostream>
#include <vector>
#include "TicketOffice.h"
#include "Station.h"
#include "TextUI.h"
#include "Ticket.h"

using namespace std;

string Station::GetName()
{
	return _name;
}

int Station::Getindex()
{
	return _index;
}

double Station::Getposition()
{
	return _position;
}

bool Station::isMainStation()
{
	return _isMainStation;
}
