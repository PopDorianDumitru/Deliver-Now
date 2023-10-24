#include "Courier.h"

std::ifstream& operator>>(std::ifstream& fin, Courier& c)
{
	std::vector<s>tokens;
	s wholeLine;
	std::getline(fin, wholeLine);
	std::stringstream str(wholeLine);
	while (!str.eof())
	{
		s temp;
		std::getline(str, temp, ';');
		tokens.push_back(temp);
	}
	if (tokens.size() < 5)
		return fin;

	c = Courier{tokens[0], tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]),std::stoi(tokens[4])};
	return fin;
}
