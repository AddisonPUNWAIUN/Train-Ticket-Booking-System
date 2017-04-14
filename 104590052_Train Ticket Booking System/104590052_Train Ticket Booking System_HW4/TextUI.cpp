#include <iostream>
#include <vector>
#include <string>
#include "TextUI.h"
#include "TicketOffice.h"
#include "Ticket.h"
#include "Station.h"
#include "Train.h"
#include "LocalTraIn.h"
#include "TzeClangLlmltedExpress.h"
#include <ctype.h>
using namespace std;

void TextUI::Run() {
	(*_ticketOffice).LoadStations();//執行物件TicketOffice里的LoadStations()
	for (;;) {
		PrintMenu();//印出選擇菜單
	}
}

void TextUI::PrintMenu() {
	cout << "火車訂票系統 :" << endl;
	cout << "a.列出所有車站" << endl;
	cout << "b.購買車票" << endl;
	cout << "c.列印車票" << endl;
	cout << "d.退票" << endl;
	cout << "請選擇 :";
	string UserChoose;
	cin >> UserChoose;
	cout << endl;
	ExcuteOption(UserChoose);//按照用戶輸入字串執行各步驟
}

void TextUI::Option_a()
{
	vector<Station*> SaveStation = (*_ticketOffice).GetStations();//獲取_stations 暫存vector 
	cout << "西部幹線-海線:" << endl;
	cout << "編號　　站名　　是否為大站" << endl;
	for (unsigned int i = 0; i < SaveStation.size(); i++)
	{
		cout << (*SaveStation[i]).Getindex() << ".";//印出編號

		if (i >= 9) cout << "     ";//控制空格
		else cout << "      ";

		cout << (*SaveStation[i]).GetName();//印出第i個物件中的_Name

		if (((*SaveStation[i]).GetName().size()) >= 6) cout << "      "; //控制空格
		else cout << "        ";

		if ((*SaveStation[i]).isMainStation() == true) {//印出第i個物件中的_isMainStation
			cout << "是";
		}
		cout << endl;
	}
	cout << endl;
}


int TextUI::Check(string b, string Traintype)
{
	string check;
	int c;
	cout << "請輸入 " << b << ":";
	cin >> check;

	for (unsigned int i = 0; i < check.length(); i++)
	{
		if (check.at(i) > '9' || check.at(i) < '0')
			return -1;
	}
	c = stoi(check);
	if (Traintype == "2") {
		vector<Station*>s = (*_ticketOffice).GetStations();
		if (s.at(c-1)->isMainStation() == false) {
			cout << "你輸入的不是大站,自強號不停此站,請重新輸入\n";
			return -1;
		}
	}
	if (!(c >= 0 && c <= 30))return -1;
	else return c;
}

void TextUI::Option_b()
{
	string Traintype;
	cout << "車種:\n1.區間車\n2.自強號" << endl;
	cout << "請選擇車種:";
	cin >> Traintype;
	while (Traintype != "1" && Traintype != "2" || Traintype.size() != 1) {
		cout << "輸入錯誤,請重新輸入" << endl;
		cout << "車種:\n1.區間車\n2.自強號" << endl;
		cout << "請選擇車種:";
		cin >> Traintype;
	}
	//choose train type
	bool reserved = false;
	string typeofseat;
	if (Traintype == "2") {
		cout << "1.對號座\n2.自由座" << endl;
		cout << "請選擇票種:";
		cin >> typeofseat;
		while (typeofseat != "1" && typeofseat != "2" || typeofseat.size() != 1) {
			cout << "輸入錯誤,請重新輸入" << endl;
			cout << "1.對號座\n2.自由座" << endl;
			cout << "請選擇票種:";
			cin >> typeofseat;
		}
		if (typeofseat == "1") reserved = true;
	}
	//if Traintype=2 choose the type of seat
	//if the type of seat=2 ,reserved=true else reserved=fasle
	int departure = 0, destination = 0;
	string name[2] = { "起點站","終點站" };
	while (1)
	{
		departure = Check(name[0], Traintype);
		if (departure == -1) {
			cout << "起點站輸入錯誤,請輸入1-30整數" << endl << endl;
		}
		if (departure != -1)
			break;
	}

	while (1)
	{
		destination = Check(name[1], Traintype);
		if (departure == destination) {
			cout << "起點站和終點站一樣" << endl;
			continue;
		}
		if (destination == -1) {
			cout << "終點站輸入錯誤,請輸入1-30整數" << endl << endl;
		}
		if (destination != -1)
			break;
	}
	//input departure and destination
	vector<Station*>s = (*_ticketOffice).GetStations();

	if (Traintype == "1") {
		Train *T = new LocalTraIn();
		(*_ticketOffice).Buy(T, s.at(departure - 1), s.at(destination - 1));
		delete T;
	}
	else {
		Train *T = new TzeClangLlmltedExpress(reserved);
		(*_ticketOffice).Buy(T, s.at(departure - 1), s.at(destination - 1));
		delete T;
	}
}

void TextUI::Option_c()
{
	PrintTicket();
}

void TextUI::Option_d()
{
	vector<Ticket*> TrainTicket = _ticketOffice->GetTicketSold();
	if (TrainTicket.size() == 0)cout << "你還沒購票!" << endl << endl;//沒買票vector a為0
	else {
		for (unsigned int i = 0; i < TrainTicket.size(); i++) {
			cout << "----------------------------" << endl;
			cout << "車票" << i + 1 << ":" << endl;
			TrainTicket.at(i)->Print();
		}
		cout << "----------------------------" << endl << endl;

		int TicketNumber;
		cout << "請選擇車票編號:";
		cin >> TicketNumber;
		while (TicketNumber > TrainTicket.size() || TicketNumber < 1) {
			cout << "\n輸入錯誤,請輸入正確車票編號" << endl;
			cout << "請選擇車票編號:";
			cin >> TicketNumber;
		}
			
		cout << "你的退票金額為 " << (TrainTicket.at(TicketNumber - 1)->GetPrice()*0.8) << " NT$" << endl;
		cout << "是否退票?(y/n)";
		string Isdelet;
		cin >> Isdelet;
		while (Isdelet != "y" && Isdelet != "n")
		{
			cout << endl << "input erroe! please input y/n" << endl;
			cout << "是否退票? (y / n)";
			cin >> Isdelet;
		}

		if (Isdelet == "y") _ticketOffice->DeletTicket(TicketNumber);
		else cout << "\n已取消退票" << endl;
	}
}

void TextUI::ExcuteOption(string option) {
	if (option == "a") Option_a();
	if (option == "b") Option_b();
	if (option == "c") Option_c();
	if (option == "d") Option_d();
	if ((option != "a") && (option != "b") && (option != "c") && (option != "d"))
	{
		cout << "input error!Please input a/b/c/d" << endl << endl;
	}
}

void TextUI::PrintTicket()
{
	vector<Ticket*> trainticket = _ticketOffice->GetTicketSold();

	if (trainticket.size() == 0)cout << "你還沒購票!" << endl << endl;//沒買票vector a為0
	else {
		for (unsigned int i = 0; i < trainticket.size(); i++) {
			cout << "----------------------------" << endl;
			trainticket.at(i)->Print();
		}
		cout << "----------------------------" << endl << endl;
	}
}