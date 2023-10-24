#pragma once
#include"Packages.h"

class PackageRepo {
private:
	std::vector<Package> packages;
public:
	std::vector<Package> getAll() { return this->packages; }
	void addPackage(Package p) { this->packages.push_back(p); }
	void initializeRepo() {
		std::ifstream fin("Packages.txt");
		Package t{};
		while (fin >> t)
		{
			this->addPackage(t);

		}
		fin.close();
	}
	Package& getPackage(s street, int number) {
		for (Package& p : this->packages)
			if (p.getStreet() == street && p.getNumber() == number)
				return p;
	}
};