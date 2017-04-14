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
	(*_ticketOffice).LoadStations();//���檫��TicketOffice����LoadStations()
	for (;;) {
		PrintMenu();//�L�X��ܵ��
	}
}

void TextUI::PrintMenu() {
	cout << "�����q���t�� :" << endl;
	cout << "a.�C�X�Ҧ�����" << endl;
	cout << "b.�ʶR����" << endl;
	cout << "c.�C�L����" << endl;
	cout << "d.�h��" << endl;
	cout << "�п�� :";
	string UserChoose;
	cin >> UserChoose;
	cout << endl;
	ExcuteOption(UserChoose);//���ӥΤ��J�r�����U�B�J
}

void TextUI::Option_a()
{
	vector<Station*> SaveStation = (*_ticketOffice).GetStations();//���_stations �Ȧsvector 
	cout << "�賡�F�u-���u:" << endl;
	cout << "�s���@�@���W�@�@�O�_���j��" << endl;
	for (unsigned int i = 0; i < SaveStation.size(); i++)
	{
		cout << (*SaveStation[i]).Getindex() << ".";//�L�X�s��

		if (i >= 9) cout << "     ";//����Ů�
		else cout << "      ";

		cout << (*SaveStation[i]).GetName();//�L�X��i�Ӫ��󤤪�_Name

		if (((*SaveStation[i]).GetName().size()) >= 6) cout << "      "; //����Ů�
		else cout << "        ";

		if ((*SaveStation[i]).isMainStation() == true) {//�L�X��i�Ӫ��󤤪�_isMainStation
			cout << "�O";
		}
		cout << endl;
	}
	cout << endl;
}


int TextUI::Check(string b, string Traintype)
{
	string check;
	int c;
	cout << "�п�J " << b << ":";
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
			cout << "�A��J�����O�j��,�۱j����������,�Э��s��J\n";
			return -1;
		}
	}
	if (!(c >= 0 && c <= 30))return -1;
	else return c;
}

void TextUI::Option_b()
{
	string Traintype;
	cout << "����:\n1.�϶���\n2.�۱j��" << endl;
	cout << "�п�ܨ���:";
	cin >> Traintype;
	while (Traintype != "1" && Traintype != "2" || Traintype.size() != 1) {
		cout << "��J���~,�Э��s��J" << endl;
		cout << "����:\n1.�϶���\n2.�۱j��" << endl;
		cout << "�п�ܨ���:";
		cin >> Traintype;
	}
	//choose train type
	bool reserved = false;
	string typeofseat;
	if (Traintype == "2") {
		cout << "1.�︹�y\n2.�ۥѮy" << endl;
		cout << "�п�ܲ���:";
		cin >> typeofseat;
		while (typeofseat != "1" && typeofseat != "2" || typeofseat.size() != 1) {
			cout << "��J���~,�Э��s��J" << endl;
			cout << "1.�︹�y\n2.�ۥѮy" << endl;
			cout << "�п�ܲ���:";
			cin >> typeofseat;
		}
		if (typeofseat == "1") reserved = true;
	}
	//if Traintype=2 choose the type of seat
	//if the type of seat=2 ,reserved=true else reserved=fasle
	int departure = 0, destination = 0;
	string name[2] = { "�_�I��","���I��" };
	while (1)
	{
		departure = Check(name[0], Traintype);
		if (departure == -1) {
			cout << "�_�I����J���~,�п�J1-30���" << endl << endl;
		}
		if (departure != -1)
			break;
	}

	while (1)
	{
		destination = Check(name[1], Traintype);
		if (departure == destination) {
			cout << "�_�I���M���I���@��" << endl;
			continue;
		}
		if (destination == -1) {
			cout << "���I����J���~,�п�J1-30���" << endl << endl;
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
	if (TrainTicket.size() == 0)cout << "�A�٨S�ʲ�!" << endl << endl;//�S�R��vector a��0
	else {
		for (unsigned int i = 0; i < TrainTicket.size(); i++) {
			cout << "----------------------------" << endl;
			cout << "����" << i + 1 << ":" << endl;
			TrainTicket.at(i)->Print();
		}
		cout << "----------------------------" << endl << endl;

		int TicketNumber;
		cout << "�п�ܨ����s��:";
		cin >> TicketNumber;
		while (TicketNumber > TrainTicket.size() || TicketNumber < 1) {
			cout << "\n��J���~,�п�J���T�����s��" << endl;
			cout << "�п�ܨ����s��:";
			cin >> TicketNumber;
		}
			
		cout << "�A���h�����B�� " << (TrainTicket.at(TicketNumber - 1)->GetPrice()*0.8) << " NT$" << endl;
		cout << "�O�_�h��?(y/n)";
		string Isdelet;
		cin >> Isdelet;
		while (Isdelet != "y" && Isdelet != "n")
		{
			cout << endl << "input erroe! please input y/n" << endl;
			cout << "�O�_�h��? (y / n)";
			cin >> Isdelet;
		}

		if (Isdelet == "y") _ticketOffice->DeletTicket(TicketNumber);
		else cout << "\n�w�����h��" << endl;
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

	if (trainticket.size() == 0)cout << "�A�٨S�ʲ�!" << endl << endl;//�S�R��vector a��0
	else {
		for (unsigned int i = 0; i < trainticket.size(); i++) {
			cout << "----------------------------" << endl;
			trainticket.at(i)->Print();
		}
		cout << "----------------------------" << endl << endl;
	}
}