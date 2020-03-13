#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "defs.h"

Provider::Provider()
{
	id = 0;
	name = "";
	address = "";
	city = "";
	state = "";
	zip = 0;
}

Provider::Provider(std::string informationFile)
{
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

bool Provider::loadInformation(std::string informationFile)
{
	// File is in the format id,name,address,city,state,zip
	std::vector<std::tuple<unsigned int, std::string, std::string, std::string, std::string, unsigned int>> information;

	if (!parseFile<unsigned int, std::string, std::string, std::string, std::string, unsigned int>(informationFile, information))
		return false;

	// Setters handle data length enforcement
	setID(std::get<0>(information.at(0)));
	setName(std::get<1>(information.at(0)));
	setAddress(std::get<2>(information.at(0)));
	setCity(std::get<3>(information.at(0)));
	setState(std::get<4>(information.at(0)));
	setZip(std::get<5>(information.at(0)));

	return true;
}

bool Provider::findService(unsigned int serviceID, Service& service)
{
	auto serviceIterator = serviceDirectory.find<unsigned int>(serviceID);

	if (serviceIterator == serviceDirectory.end())
		return false;
	else
		service = *serviceIterator;

	return true;
}
		
bool Provider::checkServiceID(unsigned int serviceID)
{
	auto serviceIterator = serviceDirectory.find<unsigned int>(serviceID);

	// Find returns an iterator to end() if it can't find it
	if (serviceIterator == serviceDirectory.end())
		return false;

	return true;
}

void Provider::printServiceDirectory()
{
	// TODO make this account for spacing better
	std::cout << "Service Directory" << std::endl;
	std::cout << "ID    " << "Name                " << "Fee    " << std::endl;
	
	for (auto service = serviceDirectory.begin(); service != serviceDirectory.end(); service++)
		std::cout << *service.ID << *service.name << *service.price << std::endl;
}


void Provider::saveSessionReport(Member member, Service& service, std::chrono::year_month_day dateProvided, std::string comments)
{
	// Put data in a session struct
	Session newSession;
	newSession.providedTo = member;
	newSession.serviceProvided = service;
	newSession.dateProvided = dateProvided;
	newSession.comments = comments;
	newSession.timeRecorded = std::chrono::system_clock::now();

	// Save session in sessionRecords
	sessionRecord.push_back(newSession);
	
	// TODO write session record to disk
}

void createSessionReport()
{
	// TODO create this funcion
}

void Provider::printWeekReport() const
{
	std::cout << "Weekly Provider Report" << std::endl;
	std::cout << "Provider name: " << name << std::endl;
	std::cout << "Provider number: " << id << std::endl;
	std::cout << "Provider street address: " << address << std::endl;
	std::cout << "Provider city: " << city << std::endl;
	std::cout << "Provider zip code: " << zip << std::endl;

	std::cout << std::endl << "Services provided in the last 7 days" << std::endl;

	// Find services provided in the last 7 days
	// This gets the date 7 days ago using std::chrono dark magic
	std::chrono::year_month_day dateAWeekAgo(std::chrono::floor<days>(std::chrono::system_clock::now() - std::chrono::weeks(1)));

	// Iterate through sessionRecords printing ones that are within 7 days ago
	unsigned int numConsultations = 0;
	double totalFee = 0;
	for (auto session = sessionRecords.cbegin; session != sessionRecords.cend(); session++) {
		// print entries whos date is equal to or greater than (occured after) the date 7 days ago
		if ((*session.dateProvided <=> dateAWeekAgo) == 0 || (*session.dateProvided <=> dateAWeekAgo) > 0) {
			std::cout << "Date of service: "
					  << std::format<std::chrono::year_month_day>("%m-%d-%Y", *session.dateProvided) << std::endl;
			// Formatting a time point compared to a year_month_day really shows how far the c++ standard has come
			std::cout << "Date and time service was saved to system: "
					  << std::put_time(std::localtime(std::chrono::system_clock::to_time_t(*session.timeRecorded)),
									   "%m-%d-%Y %H:%M:%S") << std::endl;
			std::cout << "Recieving member's name: " << *session.providedTo.getName() << std::endl;
			std::cout << "Recieving member's number: " << *session.providedTo.getID() << std::endl;
			std::cout << "Service code: " << *session.name << std::endl;
			std::cout << "Fee to be paid: $" << *session.serviceProvided.price << std::endl;

			numConsultations++;
			totalFee += *session.serviceProvided.price;
		}
	}

	std::cout << "Total number of consultations: " << numConsultations << std::endl;
	std::cout << "Total fee for the week: $" << totalFee << std::endl;
}

bool Provider::providedServices() const
{
	// Date of 7 days ago
	std::chrono::year_month_day dateAWeekAgo(std::chrono::floor<days>(std::chrono::system_clock::now() - std::chrono::weeks(1)));
	
	auto session = sessionRecords.cbegin();
	while (session != sessionRecords.cend()) {
		// if we find a session whos date is within 7 days ago we're done
		if ((*session.dateProvided <=> dateAWeekAgo) == 0 || (*session.dateProvided <=> dateAWeekAgo) > 0)
			return true;

		session++;
	}

	return false;
}

double Provider::weekFeeTotal() const
{
	double feeTotal = 0;
	
	// Date of 7 days ago
	std::chrono::year_month_day dateAWeekAgo(std::chrono::floor<days>(std::chrono::system_clock::now() - std::chrono::weeks(1)));
	
	auto session = sessionRecords.cbegin();
	while (session != sessionRecords.cend()) {
		// if we find a session whos date is within 7 days ago add it to the toal
		if ((*session.dateProvided <=> dateAWeekAgo) == 0 || (*session.dateProvided <=> dateAWeekAgo) > 0)
			feeTotal++

		session++;
	}

	return feeTotal;
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


void Provider::setID(unsigned int newID)
{
	id = resizeNumber(newID, ID_DIGITS);
}

void Provider::setName(std::string newName)
{
	if (newName.size() > NAME_CHARACTERS)
		newName.resize(NAME_CHARACTERS);

	name = newName;
}

void Provider::setAddress(std::string newAddress)
{
	if (newAddress.size() > ADDRESS_CHARACTERS)
		newAddress.resize(ADDRESS_CHARACTERS);

	address = newAddress;
}

void Provider::setCity(std::string newCity)
{
	if (newCity.size() > CITY_CHARACTERS)
		newCity.resize(CITY_CHARACTERS);

	city = newCity;
}

void Provider::setState(std::string newState)
{
	if (newState.size() > STATE_CHARACTERS)
		newState.resize(STATE_CHARACTERS);

	state = newState;
}

void Provider::setZip(unsigned int newZip)
{
	zip = resizeNumber(newZip, ZIP_DIGITS);
}

unsigned int getID() const
{
	return id;
}

std::string getName() const
{
	return name;
}

std::string getAddress() const
{
	return address;
}

std::string getCity() const
{
	return city;
}

std::string getState() const
{
	return state;
}

unsigned int getZip() const
{
	return zip;
}

bool operator<(const Provider& leftSide, const Provider& rightSide)
{
	return leftSide.id < rightSide.id;
}

bool operator<(const unsigned int& leftSide, const Provider& rightSide)
{
	return leftSide < rightSide.id;
}

bool operator<(const Provider& leftSide, const unsigned int& rightSide)
{
	return leftSide.id < rightSide;
}

