#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TicketOffice.h"
#include "Station.h"
#include "TextUI.h"
#include "Ticket.h"
using namespace std;


int Ticket::GetPrice()//回傳需要付款的金額
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
		return Min + " 分鐘";
	}
	if (traveltime >= 60) {
		Hour = to_string(int(traveltime / 60));
		Min = to_string(int(traveltime - int(traveltime / 60) * 60));
		return Hour + " 小時 " + Min + " 分鐘";
	}
}

string Ticket::GetTicketType()
{
	return _TRAVEL_TYPE;
}

void Ticket::Print()
{
	cout << "車票詳細資訊:" << endl;

	cout << "車種:";
	cout << _TRAIN_NAME << endl;

	cout << "起點站:";
	cout << _DEPARTURE << endl;//印出起點站名

	cout << "終點站:";
	cout << _DESTINATION << endl;//印出終點站名

	cout << "乘車時間: ";
	cout << GetTravelTimeText() << endl;

	cout << "票種: ";
	cout << GetTicketType() << endl;

	cout << "票價: NT$";
	cout << _PRICE << endl;
}
