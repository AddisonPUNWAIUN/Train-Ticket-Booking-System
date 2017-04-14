#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TicketOffice.h"
#include "Station.h"
#include "TextUI.h"
#include "Ticket.h"
using namespace std;


int Ticket::GetPrice()//�^�ǻݭn�I�ڪ����B
{
	return _PRICE;
}
string Ticket::GetTrainName()
{
	return _TRAIN_NAME;
}
string Ticket::GetDeparture()
{
	return _DEPARTURE;
}

string Ticket::GetDestination()
{
	return _DESTINATION;
}

string Ticket::GetTravelTimeText()
{
	string Hour, Min;
	double traveltime = _TRAVEL_TIME;

	if (traveltime < 60) {
		Min = to_string(int(traveltime));
		return Min + " ����";
	}
	if (traveltime >= 60) {
		Hour = to_string(int(traveltime / 60));
		Min = to_string(int(traveltime - int(traveltime / 60) * 60));
		return Hour + " �p�� " + Min + " ����";
	}
}

string Ticket::GetTicketType()
{
	return _TRAVEL_TYPE;
}

void Ticket::Print()
{
	cout << "�����ԲӸ�T:" << endl;

	cout << "����:";
	cout << _TRAIN_NAME << endl;

	cout << "�_�I��:";
	cout << _DEPARTURE << endl;//�L�X�_�I���W

	cout << "���I��:";
	cout << _DESTINATION << endl;//�L�X���I���W

	cout << "�����ɶ�: ";
	cout << GetTravelTimeText() << endl;

	cout << "����: ";
	cout << GetTicketType() << endl;

	cout << "����: NT$";
	cout << _PRICE << endl;
}
