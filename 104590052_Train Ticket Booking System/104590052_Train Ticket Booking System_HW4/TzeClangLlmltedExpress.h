
class TzeClangLlmltedExpress :public Train {
public:
	TzeClangLlmltedExpress(bool isReserved) :_isReserved(isReserved) { _TRIAN_NAME = "¦Û±j¸¹"; _PRICE_RATE = 2.27; _SPEED = 100; _STOPPING_TIME = 5; }
	bool GetIsReserved();
	int ComputePrice(double distance);
private:
	bool _isReserved;
};