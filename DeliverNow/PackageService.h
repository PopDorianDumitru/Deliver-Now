#pragma once
#include"PackageRepo.h"
#include<algorithm>
#include<iterator>
#include<cmath>
#include "Courier.h"
#include "Subject.h"
class PackageService : public Subject {
private:
	PackageRepo repo;
	//std::vector<Courier> couriers;
public:
	std::vector<Package> getAll() { return this->repo.getAll(); }
	std::vector<s> getStreets() {
		std::vector<s>streets;
		std::vector<Package> packs = this->repo.getAll();
		for (Package p : packs)
		{
			if (std::find(streets.begin(), streets.end(), p.getStreet()) == streets.end())
				streets.push_back(p.getStreet());
		}
		return streets;
	}
	void initializerepo() { this->repo.initializeRepo(); }
	Package& getPackage(s street, int number) { return this->repo.getPackage(street, number); }
	std::vector<Package> getUndelivered(Courier a) {
		std::vector<Package> und, t = this->repo.getAll();
		std::vector<s> streets = a.getStreets();
		std::copy_if(t.begin(), t.end(), std::back_inserter(und), [&a, &streets](Package p) {
			if (!p.getDelivered())
			{
				if (std::find(streets.begin(), streets.end(), p.getStreet()) != streets.end())
					return true;
				double dist = std::sqrt((p.getX() - a.getX()) * (p.getX() - a.getX()) + (p.getY() - a.getY()) * (p.getY() - a.getY()));
				if (dist < a.getR())
					return true;


				return false;
			}
			return false;
		});
		return und;
	}
	std::vector<Package> getByStreet(Courier a, s street)
	{
		std::vector<Package> all = this->getUndelivered(a);
		std::vector<Package> forstr;
		std::copy_if(all.begin(), all.end(), std::back_inserter(forstr), [&street](Package a) {return a.getStreet() == street; });
		return forstr;
	}
	void saveRepo()
	{
		std::vector<Package> a = this->getAll();
		std::ofstream fout("Packages.txt");
		for (Package p : a)
		{
			fout << p.getRecipient() << ';' << p.getStreet() + ';' << p.getNumber() << ';' << p.getX() << ';' << p.getY() << ';';
			if (p.getDelivered())
				fout << "true";
			else
				fout << "false";
			fout << '\n';
		}
		fout.close();
	}
	void AddPackage(Package p)
	{
		this->repo.addPackage(p);
	}
};