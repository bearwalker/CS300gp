#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "defs.h"

Provider::Provider() {
	id = 0;
	name = "";
	address = "";
	city = "";
	state = "";
	zip = 0;
}

Provider::Provider(std::string informationFile) {
	// If the information file can't be read use null defaults
	if (!loadInformation(informationFile)) {
			id = 0;
			name = "";
			address = "";
			city = "";
			state = "";
			zip = 0;
	}
}

bool Provider::loadInformation(std::string informationFile) {
	std::ifstream infoFile(informationFile);

	// Check if the file could be opened
	if (!infoFile.is_open())
		return false;

	// Read in comma seperated info, see data/provider-format.csv for format
	std::string idBuffer;
	std::string nameBuffer;
	std::string addressBuffer;
	std::string cityBuffer;
	std::string stateBuffer;
	std::string zipBuffer;

	std::getline(infoFile, idBuffer, ',');
	std::getline(infoFile, nameBuffer, ',');
	std::getline(infoFile, addressBuffer, ',');
	std::getline(infoFile, cityBuffer, ',');
	std::getline(infoFile, stateBuffer, ',');
	std::getline(infoFile, zipBuffer, ',');

	// Convert ID and Zip to ints
	unsigned int tempID;
	unsigned int tempZip;

	try {
		// std::stoi throws an exception if it fails to convert
		tempID = std::stoi(idBuffer);
		tempZip = std::stoi(zipBuffer);
	}
	catch(...) {
		return false;
	}

	// Check length constraints
	//if (numDigits()

	return true;


}


bool Provider::checkServiceID(unsigned int serviceID) {
	auto serviceIterator = servicesProvided.find<unsigned int>(serviceID);

	// Find returns an iterator to end() if it can't find it
	if (serviceIterator == servicesProvided.end())
		return false;

	return true;
}

void Provider::summaryReport() {
	float total = 0;

	// Print each service and total up the running cost
	for (auto service = servicesProvided.begin(); service != servicesProvided.end(); service++) {
		total += service->price * service->times_used;

		std::cout << "Service ID: " << service->ID << std::endl;
		std::cout << "Service Name: " << service->name << std::endl;
		std::cout << "Service Price: $" << service->price << std::endl;
		std::cout << "Times Used: " << service->times_used << std::endl;
	}

	std::cout << "Total Fees: $" << total << std::endl;
}

void Provider::printWeekReport() {
	std::cout << name << std::endl;
	std::cout << "Provided " << numServicesProvided << " Services" << std::endl;
	std::cout << "Fees total: " << feeTotal << std::endl;
}

bool Provider::providedServices() {
	return numServicesProvided > 0;
}

void Provider::setInfo()
{
    char response;

    std::cout << '\n' << "Enter Name of provider: ";
    std::getline(std::cin,name);
    std::cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    std::cout << '\n' << "Enter " << name << " Provider ID: ";
    std::cin >> id;
    std::cin.ignore(MAX,'\n');

    std::cout << '\n' << "Enter " << name << " Street Address: ";
    std::getline(std::cin,address);
    std::cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    std::cout << '\n' << "Enter " << name << " City: ";
    std::getline(std::cin,city);
    std::cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    std::cout << '\n' << "Enter " << name << " State(EG:OR): ";
    std::getline(std::cin,state);
    std::cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    std::cout << '\n' << "Enter " << name << " ZIP: ";
    std::cin >> zip;
    std::cin.ignore(MAX,'\n');

    std::cout << '\n' << "Add Services? (Y/N)" << '\n';
    std::cin >> response;
    std::cin.ignore(MAX,'\n');
    response = toupper(response);

    if(response == 'Y')
        setServices();
    return;

}

void Provider::setServices()
{
    char response;
    do{
        addService();
        std::cout << '\n' << "Add Another? (Y/N)" << '\n';
        std::cin >> response;
        std::cin.ignore('\n',MAX);
        response = toupper(response);
    }while(response != 'N');
    return;

}

bool Provider::addService()
{
    Service new_serv;
    new_serv.setInfo();
    servicesProvided.insert(new_serv);
    return true;
}

void Provider::printServiceList()
{
    for(auto serv_ptr = servicesProvided.begin(); serv_ptr != servicesProvided.end(); serv_ptr++){
        Service current = *serv_ptr;
        current.displayInfo();
        std::cout << '\n' << '\n';
    }
    return;
}


float Provider::weekFeeTotal() {
	return feeTotal;
}

bool operator<(const Provider& leftSide, const Provider& rightSide) {
	return leftSide.id < rightSide.id;
}

bool operator<(const unsigned int& leftSide, const Provider& rightSide) {
	return leftSide < rightSide.id;
}

bool operator<(const Provider& leftSide, const unsigned int& rightSide) {
	return leftSide.id < rightSide;
}

