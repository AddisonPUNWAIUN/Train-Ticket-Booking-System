
class LocalTraIn :public Train {
public:
	LocalTraIn() { _TRIAN_NAME = "°Ï¶¡¨®"; _PRICE_RATE = 1.06; _SPEED = 70; _STOPPING_TIME = 2; }
	bool GetIsReserved();
	int ComputePrice(double distance) ;
};