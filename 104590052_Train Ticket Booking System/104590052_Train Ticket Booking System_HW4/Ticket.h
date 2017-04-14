using namespace std;

class Ticket {
public:
	Ticket(string traintype, string trainName, string deaparture, string destination, int price, double travelTime) :_TRAVEL_TYPE(traintype), _TRAIN_NAME(trainName), _DEPARTURE(deaparture), _DESTINATION(destination), _PRICE(price), _TRAVEL_TIME(travelTime) {};
	int GetPrice();
	string GetTrainName();
	string GetDeparture();
	string GetDestination();
	string GetTravelTimeText();
	string GetTicketType();
	void Print();
private:
	const string _TRAIN_NAME;
	const string _DEPARTURE;
	const string _DESTINATION;
	const int _PRICE;
	const double _TRAVEL_TIME;
	const string _TRAVEL_TYPE;//·s¼W
};