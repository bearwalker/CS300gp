#include <chrono>
#include <ctime>
#include <fstream>
#include <ios>
#include <iostream>
#include <iomanip>
#include <string>

#ifdef GCC_OLD
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#include "provider.h"
#include "defs.h"
#include "digits.h"
#include "csvParser.h"
#include "member.h"
#include "service.h"
#include "session.h"

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

	// Load the services
	for (auto file: fs::directory_iterator(SERVICE_DATA_DIR)) {
		Service newService;
		if (newService.loadInformation(file.path()))
			serviceDirectory.insert(newService);
	}

	// Load session records
	for (auto file: fs::directory_iterator(PROVIDER_DATA_DIR + std::to_string(id) + SESSION_DATA_SUBDIR)) {
		Session newSession;
		if (file.path() != "dummyFile" && newSession.loadInformation(file.path()))
			sessionRecords.push_back(newSession);
	}

	return true;
}

bool Provider::saveEFT(std::string filePath, double fee)
{
	std::ofstream file(filePath);

	if (!file.is_open())
		return false;

	file << name << ',' << id << ',' << fee << ';' << std::endl;
	file.close();

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

bool Provider::checkServiceID(unsigned int serviceID) const
{
	auto serviceIterator = serviceDirectory.find<unsigned int>(serviceID);

	// Find returns an iterator to end() if it can't find it
	if (serviceIterator == serviceDirectory.end())
		return false;

	return true;
}

void Provider::printServiceDirectory() const
{
	std::cout << "Service Directory" << std::endl;
	std::cout << std::left << std::setw(SERVICE_ID_DIGITS + 1) << "ID" << std::setw(SERVICE_NAME_CHARACTERS + 1) << "Name" << std::setw(SERVICE_PRICE_WIDTH) << "Fee" << std::endl;

	for (auto service = serviceDirectory.begin(); service != serviceDirectory.end(); service++)
		std::cout << std::left << std::setw(SERVICE_ID_DIGITS + 1) << (*service).getID()
				  << std::setw(SERVICE_NAME_CHARACTERS + 1) << (*service).getName()
				  << std::setw(SERVICE_PRICE_WIDTH) << "$" << std::setprecision(SERVICE_PRICE_WIDTH - 1) << (*service).getPrice() << std::endl;
}


Session Provider::saveSessionReport(Member member, Service service, std::chrono::system_clock::time_point dateProvided, std::string comments)
{
	// Put data in a session struct
	Session newSession;
	newSession.setServiceProvided(service);
	newSession.setMemberName(member.getName());
	newSession.setMemberID(member.getID());
	newSession.setProviderName(name);
	newSession.setDateProvided(dateProvided);
	newSession.setComments(comments);
	newSession.setTimeRecorded(std::chrono::system_clock::now());

	// Save session in sessionRecords
	sessionRecords.push_back(newSession);

	// write session record to disk
	std::time_t dateTimeT = std::chrono::system_clock::to_time_t(dateProvided);
	std::tm dateTm = *std::localtime(&dateTimeT);
	std::ostringstream dateString;
	dateString << std::put_time(&dateTm, "%m-%d-%Y");

	std::string sessionPath = PROVIDER_DATA_DIR + std::to_string(id) + SESSION_DATA_SUBDIR + dateString.str() + "_" + member.getName() + ".csv";
	newSession.saveRecord(sessionPath);

	// write eft to disk
	std::string eftPath = EFT_DATA_DIR + "provider_" + std::to_string(id) + "_" + dateString.str() + "_" + member.getName() + ".csv";
	saveEFT(eftPath, service.getPrice());

	return newSession;
}

void Provider::printWeekReport()
{
	weekReport(std::cout);
}

bool Provider::saveWeekReport(std::string filePath)
{
	std::ofstream file(filePath);

	if (!file.is_open())
		return false;

	weekReport(file);
	file.close();
	return true;
}

void Provider::weekReport(std::ostream& out)
{
	out << "Weekly Provider Report" << std::endl;
	out << "Provider name: " << name << std::endl;
	out << "Provider number: " << id << std::endl;
	out << "Provider street address: " << address << std::endl;
	out << "Provider city: " << city << std::endl;
	out << "Provider zip code: " << zip << std::endl;

	out << std::endl << "Services provided in the last 7 days" << std::endl;

	// Find services provided in the last 7 days
	// This gets the date 7 days ago using std::chrono dark magic (a day is 86400 seconds)
	// Basically this takes the current time minus 7 days then rounds it down with floor to the nearest day
	std::chrono::system_clock::time_point dateAWeekAgo(std::chrono::floor<std::chrono::duration<int, std::ratio<86400>>>(std::chrono::system_clock::now() - (std::chrono::hours(24) * 7)));

	// Iterate through sessionRecords printing ones that are within 7 days ago
	unsigned int numConsultations = 0;
	double totalFee = 0;
	for (auto session = sessionRecords.begin(); session != sessionRecords.end(); session++) {
		// print entries whos date is equal to or greater than (occured after) the date 7 days ago
		if ((*session).getDateProvided() == dateAWeekAgo || (*session).getDateProvided() > dateAWeekAgo) {
			// Convert time_points to time_t for printing
			std::time_t dateT = std::chrono::system_clock::to_time_t(((*session).getDateProvided()));
			std::time_t timeT = std::chrono::system_clock::to_time_t(((*session).getTimeRecorded()));
			std::tm dateTm = *std::localtime(&dateT);
			std::tm timeTm = *std::localtime(&timeT);

			out << "Date of service: " << std::put_time(&dateTm, "%m-%d-%Y") << std::endl;
			out << "Date and time service was saved to system: "
					  << std::put_time(&timeTm, "%m-%d-%Y %H:%M:%S") << std::endl;
			out << "Recieving member's name: " << (*session).getMemberName() << std::endl;
			out << "Recieving member's number: " << (*session).getMemberID() << std::endl;
			out << "Service code: " << (*session).getServiceProvided().getID() << std::endl;
			out << "Fee to be paid: $" << (*session).getServiceProvided().getPrice() << std::endl << std::endl;

			numConsultations++;
			totalFee += (*session).getServiceProvided().getPrice();
		}
	}

	out << "Total number of consultations: " << numConsultations << std::endl;
	out << "Total fee for the week: $" << totalFee << std::endl;
}

int Provider::providedServices() const
{
    int servicesProvided = 0;
	// Date of 7 days ago
	std::chrono::system_clock::time_point dateAWeekAgo(std::chrono::floor<std::chrono::duration<int, std::ratio<86400>>>(std::chrono::system_clock::now() - (std::chrono::hours(24) * 7)));

	auto session = sessionRecords.cbegin();
	while (session != sessionRecords.cend()) {
		// if we find a session whos date is within 7 days ago we're done
		if ((*session).getDateProvided() == dateAWeekAgo || (*session).getDateProvided() > dateAWeekAgo)
			++servicesProvided;

		session++;
	}

	return servicesProvided;
}

double Provider::weekFeeTotal() const
{
	double feeTotal = 0;

	// Date of 7 days ago
	std::chrono::system_clock::time_point dateAWeekAgo(std::chrono::floor<std::chrono::duration<int, std::ratio<86400>>>(std::chrono::system_clock::now() - (std::chrono::hours(24) * 7)));

	auto session = sessionRecords.cbegin();
	while (session != sessionRecords.cend()) {
		// if we find a session whos date is within 7 days ago add it to the toal
		if ((*session).getDateProvided() == dateAWeekAgo || (*session).getDateProvided() > dateAWeekAgo)
			feeTotal++;

		session++;
	}

	return feeTotal;
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

unsigned int Provider::getID() const
{
	return id;
}

std::string Provider::getName() const
{
	return name;
}

std::string Provider::getAddress() const
{
	return address;
}

std::string Provider::getCity() const
{
	return city;
}

std::string Provider::getState() const
{
	return state;
}

unsigned int Provider::getZip() const
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

