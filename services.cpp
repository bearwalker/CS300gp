//Service class functions implementation

#include "defs.h"
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

void setID(unsigned int newID)
{
	id = resizeNumber(newID, SERVICE_ID_DIGITS);
}

void setName(std::string newName)
{
	if (newName.size() > SERVICE_NAME_CHARACTERS)
		newName.resize(SERVICE_NAME_CHARACTERS);

	name = newName;
}

void setPrice(double newPrice)
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
    std::cout << '\n' << "Service ID: " << ID;
    std::cout << '\n' << "Service Price: " << price;
}

unsigned int getID() const
{
	return id;
}

std::string getName() const
{
	return name;
}

double getPrice() const
{
	return price;
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

