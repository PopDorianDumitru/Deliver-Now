#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
typedef std::string s;

class Courier {
private:
	s name;
	std::vector<s>streets;
	int x, y,r;
public:
	Courier() {}
	Courier(s name, s streets, int x, int y, int r) : name{ name },  x{ x }, y{ y }, r{ r } {
		std::stringstream str(streets);
		while (!str.eof())
		{
			s temo;
			std::getline(str, temo, ',');
			this->streets.push_back(temo);
		}
	}
	s getName() { return this->name; }
	std::vector<s> getStreets() { return this->streets; }
	int getX() { return this->x; }
	int getY() { return this->y; }
	int getR() { return this->r; }
	friend std::ifstream& operator>>(std::ifstream& fin, Courier& c);
};