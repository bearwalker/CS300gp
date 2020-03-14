//Service class functions implementation

#include <iostream>
#include <string>

#include "service.h"
#include "defs.h"
#include "digits.h"
#include "csvParser.h"

Service::Service()
{
	id = 0;
	name = "";
	price = 0;
}

Service::Service(std::string informationFile)
{
	if (!loadInformation(informationFile)) {
		id = 0;
		name = "";
		price = 0;
	}
}

bool Service::loadInformation(std::string informationFile)
{
	// File is in format id,name,price
	std::vector<std::tuple<unsigned int, std::string, double>> information;

	if(!parseFile<unsigned int, std::string, double>(informationFile, information))
		return false;

	setID(std::get<0>(information.at(0)));
	setName(std::get<1>(information.at(0)));
	setPrice(std::get<2>(information.at(0)));

	return true;
}

void Service::setID(unsigned int newID)
{
	id = resizeNumber(newID, SERVICE_ID_DIGITS);
}

void Service::setName(std::string newName)
{
	if (newName.size() > SERVICE_NAME_CHARACTERS)
		newName.resize(SERVICE_NAME_CHARACTERS);

	name = newName;
}

void Service::setPrice(double newPrice)
{
	if (newPrice > SERVICE_PRICE_MAX)
		price = SERVICE_PRICE_MAX;
	else
		price = newPrice;
}

//Display service info
void Service::displayInfo()
{
    std::cout << '\n' << "Service Name: " << name;
    std::cout << '\n' << "Service ID: " << id;
    std::cout << '\n' << "Service Price: " << price;
}

unsigned int Service::getID() const
{
	return id;
}

std::string Service::getName() const
{
	return name;
}

double Service::getPrice() const
{
	return price;
}

bool operator<(const Service& leftSide, const Service& rightSide) {
	return leftSide.id < rightSide.id;
}

bool operator<(const unsigned int& leftSide, const Service& rightSide) {
	return leftSide < rightSide.id;
}

bool operator<(const Service& leftSide, const unsigned int& rightSide) {
	return leftSide.id < rightSide;
}

