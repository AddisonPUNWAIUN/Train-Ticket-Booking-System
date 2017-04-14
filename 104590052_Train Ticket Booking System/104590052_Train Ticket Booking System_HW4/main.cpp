//潘偉源
//104950052
//四資工二
//2016.1.8
//學習使用多個class互動, 製作火車訂票系統 繼承車種
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