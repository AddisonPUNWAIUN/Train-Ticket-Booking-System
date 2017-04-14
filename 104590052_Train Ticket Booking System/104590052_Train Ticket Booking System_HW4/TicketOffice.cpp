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

	while (OpenStationsData >> index) {//stations.TXT 第一個元素(1)存入StationsName
		OpenStationsData >> StationsName;     //stations.TXT 第二個元素(基隆)存入StationsName
		OpenStationsData >> Distance;         //stations.TXT 第三個元素(0)存入Distance
		OpenStationsData >> saveIsMainStation;//stations.TXT 第四個元素(true)存入saveIsMainStation
		IsMainStation = (saveIsMainStation == "true");//判斷saveIsMainStation字串是否為true,是,存入IsMainStation
		Station *load = new Station(index, StationsName, Distance, IsMainStation);//建立一個物件指標(*load)指向Station,存入上面的元素
		_stations.push_back(load);//把本次初如化的物件(load)存入vector<*Station>_stations vector
	}//如此類推,直到沒把元素讀取完後停止迴圈
	 //OpenStationsData.close;
}

vector<Station*> TicketOffice::GetStations()//獲取Stations資訊
{
	return _stations;//回傳整個 private vector<*Station>_stations
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
	
	if (train->GetTrainName() == "自強號") {
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

	if (train->GetTrainName() == "區間車") {
		Stop = abs(_departure->Getindex() - _destination->Getindex()) + 1;
	}
	//compute sotp times
	Ticket *ticket = new Ticket((train->GetIsReserved() == true) ? "對號座" : "自由座", train->GetTrainName(), _departure->GetName(), _destination->GetName(), train->ComputePrice(distance), train->ComputeTravelTime(distance, Stop));
	ticket->Print();
	//產生ticket
	cout << "是否購買（y/n)";
	string IsBuyIt;
	cin >> IsBuyIt;

	while (IsBuyIt != "y" && IsBuyIt != "n")
	{
		cout << "\ninput erroe! please input y/n" << endl;
		cout << "是否購買（y/n)";
		cin >> IsBuyIt;
	}

	if (IsBuyIt == "y") {
		cout << "購票成功!" << endl;
		cout << endl;
		_ticketsSold.push_back(ticket);
		return true;
	}
	else {
		cout << "已取消購票" << endl;
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
	//利用堆疊原理刪除vector _ticketsSold中的data
	cout << "退票成功!\n" << endl;
}
