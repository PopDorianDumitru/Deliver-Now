#pragma once
#include "DeliverNow.h"
#include "CourierCompany.h"
#include "Map.h"
class BigApp {
private:
	PackageService service;
	Map* map;
	std::vector<DeliverNow*> windows;
	CourierCompany* c;
public:
	BigApp() {
		this->service.initializerepo();
		std::ifstream fin("Couriers.txt");
		Courier c{};
		while (fin >> c)
		{
			DeliverNow* p = new DeliverNow{ c,this->service };
			this->windows.push_back(p);
			this->service.registerObserver(p);
		}
		fin.close();
		for (DeliverNow* p : this->windows)
			p->show();
		this->c = new CourierCompany{ this->service };
		this->c->show();
		this->service.registerObserver(this->c);
		map = new Map{ this->service };
		map->show();
		this->service.registerObserver(map);
	}
	~BigApp() {
		this->service.saveRepo();
		delete this->map;
		delete this->c;
		for (DeliverNow* p : this->windows)
			delete p;
	}
};