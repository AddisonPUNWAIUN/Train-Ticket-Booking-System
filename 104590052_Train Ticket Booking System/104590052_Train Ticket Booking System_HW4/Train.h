using namespace std;

class Train {
public:
	Train() {}
	~Train() {};//new
	string GetTrainName();
	double ComputeTravelTime(double distance, int intermediateStops);
	virtual int ComputePrice(double distance);
	virtual bool GetIsReserved() { return 0; }//new
protected:
	Train(string trainName, double priceRate, double Speed, double stoppingTime) :_TRIAN_NAME(trainName), _PRICE_RATE(priceRate), _SPEED(Speed), _STOPPING_TIME(stoppingTime) {};
	string _TRIAN_NAME;
	double _PRICE_RATE;
	double _SPEED;
	double _STOPPING_TIME;
};