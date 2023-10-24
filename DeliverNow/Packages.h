#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
typedef std::string s;
class Package {
private:
	s recipient,  street;
	int number;
	int x, y;
	bool delivered;
public:
	Package() {}
	Package(s recipient, s street, int number, int x, int y, s del) : recipient{ recipient },  street{ street }, number{ number }, x{ x }, y{ y } {
		if (del == "true")
			delivered = true;
		else
			delivered = false;
	}
	s getRecipient() { return this->recipient;}
	//s getAddress() { return this->address; }
	s getStreet() { return this->street; }
	int getNumber() { return this->number; }
	int getX() { return this->x; }
	void setDelivered() { this->delivered = true; }
	int getY() { return this->y; }
	bool getDelivered() { return this->delivered;}
	friend std::ifstream& operator>>(std::ifstream& fin, Package& c);

};