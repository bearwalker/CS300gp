//Service class functions implementation

#include "defs.h"

//Set service info
void Service::setInfo()
{

    std::cout << '\n' << "Enter Service ID: ";
    std::cin >> ID;
    std::cin.ignore(MAX,'\n');


    std::cout << '\n' << "Enter Service Name: ";
    std::getline(std::cin,name);
    std::cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    std::cout << '\n' << "Enter Service Price: ";
    std::cin >> price;
    std::cin.ignore(MAX,'\n');

    return;
}

bool operator<(const Service& leftSide, const Service& rightSide) {
	return leftSide.ID < rightSide.ID;
}

bool operator<(const unsigned int& leftSide, const Service& rightSide) {
	return leftSide < rightSide.ID;
}

bool operator<(const Service& leftSide, const unsigned int& rightSide) {
	return leftSide.ID < rightSide;
}

