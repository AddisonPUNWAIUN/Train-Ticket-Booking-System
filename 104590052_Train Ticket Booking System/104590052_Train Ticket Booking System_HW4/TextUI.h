using namespace std;

class TicketOffice;

class TextUI {
public:
	TextUI(TicketOffice *ticketOffice) { _ticketOffice = ticketOffice; };
	void Run();
private:
	void ExcuteOption(string option);
	void PrintTicket();
	void PrintMenu();
	void Option_a();
	void Option_b();
	void Option_c();
	void Option_d();
	int Check(string b, string Traintype);
	TicketOffice *_ticketOffice;
};
