#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Ticket.h"
#include "TicketOffice.h"
#include "Station.h"
#include "Train.h"
#include "TextUI.h"

using namespace std;

void TicketOffice::LoadStations() {
	int index;
	string StationsName, saveIsMainStation;
	bool IsMainStation;
	double Distance;

	fstream OpenStationsData;
	OpenStationsData.open("stations.TXT");

	while (OpenStationsData >> index) {//stations.TXT �Ĥ@�Ӥ���(1)�s�JStationsName
		OpenStationsData >> StationsName;     //stations.TXT �ĤG�Ӥ���(��)�s�JStationsName
		OpenStationsData >> Distance;         //stations.TXT �ĤT�Ӥ���(0)�s�JDistance
		OpenStationsData >> saveIsMainStation;//stations.TXT �ĥ|�Ӥ���(true)�s�JsaveIsMainStation
		IsMainStation = (saveIsMainStation == "true");//�P�_saveIsMainStation�r��O�_��true,�O,�s�JIsMainStation
		Station *load = new Station(index, StationsName, Distance, IsMainStation);//�إߤ@�Ӫ������(*load)���VStation,�s�J�W��������
		_stations.push_back(load);//�⥻����p�ƪ�����(load)�s�Jvector<*Station>_stations vector
	}//�p������,����S�⤸��Ū�����ᰱ��j��
	 //OpenStationsData.close;
}

vector<Station*> TicketOffice::GetStations()//���Stations��T
{
	return _stations;//�^�Ǿ�� private vector<*Station>_stations
}

vector<Ticket*> TicketOffice::GetTicketSold()
{
	return _ticketsSold;
}


bool TicketOffice::Buy(Train* train, Station * _departure, Station * _destination)
{
	double distance = fabs(_departure->Getposition() - _destination->Getposition());
	//compute distance
	int Stop = 0;
	int index1 = _departure->Getindex(), index2 = _destination->Getindex();
	
	if (train->GetTrainName() == "�۱j��") {
		if (index1 < index2) {
			for (int i = index1-1; i <= index2-1; i++) {
				if (_stations.at(i)->isMainStation() == true) Stop += 1;
			}
		}
		else if (index2 < index1) {
			for (int i = index2-1; i <= index1-1; i++) {
				if (_stations.at(i)->isMainStation() == true) Stop += 1;
			}
		}
	}

	if (train->GetTrainName() == "�϶���") {
		Stop = abs(_departure->Getindex() - _destination->Getindex()) + 1;
	}
	//compute sotp times
	Ticket *ticket = new Ticket((train->GetIsReserved() == true) ? "�︹�y" : "�ۥѮy", train->GetTrainName(), _departure->GetName(), _destination->GetName(), train->ComputePrice(distance), train->ComputeTravelTime(distance, Stop));
	ticket->Print();
	//����ticket
	cout << "�O�_�ʶR�]y/n)";
	string IsBuyIt;
	cin >> IsBuyIt;

	while (IsBuyIt != "y" && IsBuyIt != "n")
	{
		cout << "\ninput erroe! please input y/n" << endl;
		cout << "�O�_�ʶR�]y/n)";
		cin >> IsBuyIt;
	}

	if (IsBuyIt == "y") {
		cout << "�ʲ����\!" << endl;
		cout << endl;
		_ticketsSold.push_back(ticket);
		return true;
	}
	else {
		cout << "�w�����ʲ�" << endl;
		cout << endl;
		return false;
	}
	return 0;
}

void TicketOffice::DeletTicket(int ticketnumber) {
	vector <Ticket*> SaveTicketsSold;

	for (unsigned int i = _ticketsSold.size(); i > 0; i--) {
		if (i == ticketnumber) {
			_ticketsSold.pop_back();
			break;
		}
		else {
			SaveTicketsSold.push_back(_ticketsSold.at(i - 1));
			_ticketsSold.pop_back();
		}
	}

	for (unsigned int i = SaveTicketsSold.size(); i > 0; i--) {
		_ticketsSold.push_back(SaveTicketsSold.at(i - 1));
	}
	//�Q�ΰ��|��z�R��vector _ticketsSold����data
	cout << "�h�����\!\n" << endl;
}
