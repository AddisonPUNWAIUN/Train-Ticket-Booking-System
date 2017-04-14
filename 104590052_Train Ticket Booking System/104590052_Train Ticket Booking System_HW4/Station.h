using namespace std;

class Station {
public:
	Station(int index, string name, double position, bool isMainStation) { _index = index, _name = name; _position = position; _isMainStation = isMainStation; };
	int Getindex();
	string GetName();
	double Getposition();
	bool isMainStation();
private:
	string _name;
	double _position; ;
	bool _isMainStation;
	int _index;
};