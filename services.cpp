//Service class functions implementation

#include "defs.h"

//Set service info
void Service::setInfo()
{

    std::cout << '\n' << "Enter Name of New Service: ";
    std::getline(std::cin,name);
    std::cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    std::cout << '\n' << "Enter " << name << " Service ID: ";
    std::cin >> ID;
    std::cin.ignore(MAX,'\n');

    std::cout << '\n' << "Enter " << name << " Service Price: ";
    std::cin >> price;
    std::cin.ignore(MAX,'\n');

    return;
}

//Display service info
void Service::displayInfo()
{
    std::cout << '\n' << "Service Name: " << name;
    std::cout << '\n' << "Service ID: " << ID;
    std::cout << '\n' << "Service Price: " << price;
    std::cout << '\n' << "Times Service Used: " << times_used;
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

