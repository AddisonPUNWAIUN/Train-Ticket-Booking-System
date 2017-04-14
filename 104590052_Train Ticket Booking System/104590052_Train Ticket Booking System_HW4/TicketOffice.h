using namespace std;

class Station;
class Ticket;
class Train;

class TicketOffice {
public:
	void LoadStations();
	vector <Station*> GetStations();
	vector <Ticket*> GetTicketSold();
	bool Buy(Train* train, Station *_departure, Station *_destination);
	void DeletTicket(int ticketnumber);
private:
	vector <Station*> _stations;
	vector <Ticket*> _ticketsSold;
};