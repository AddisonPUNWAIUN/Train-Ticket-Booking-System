//�ﰶ��
//104950052
//�|��u�G
//2016.1.8
//�ǲߨϥΦh��class����, �s�@�����q���t�� �~�Ө���
//Train Ticket Booking System_HW4
#include <iostream>
#include <vector>
#include <string>
#include "TicketOffice.h"
#include "TextUI.h"

using namespace std;

int main() {
	TicketOffice ticketOffice;
	TextUI Do(&ticketOffice);
	Do.Run();

	system("PAUSE");
	return 0;
}