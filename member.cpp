//Member class for ChocAn

#include <chrono>
#include <ctime>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>
#include <iostream>
#include <iomanip>

#ifdef GCC_OLD
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#include "member.h"
#include "defs.h"
#include "digits.h"
#include "csvParser.h"
#include "session.h"


Member::Member()
{
	id = 0;
	name = "";
	address = "";
	city = "";
	state = "";
	zip = 0;
	status = false;
}

Member::Member(std::string informationFile)
{
	if (!loadInformation(informationFile)) {
		id = 0;
		name = "";
		address = "";
		city = "";
		state = "";
		zip = 0;
		status = false;
	}
}

bool Member::loadInformation(std::string informationFile)
{
	// File is in the format id,name,address,city,state,zip,status
	std::vector<std::tuple<unsigned int, std::string, std::string, std::string, std::string, unsigned int, bool>> information;

	if(!parseFile<unsigned int, std::string, std::string, std::string, std::string, unsigned int, bool>(informationFile, information))
		return false;

	// Setters handle data length enforcement
	setID(std::get<0>(information.at(0)));
	setName(std::get<1>(information.at(0)));
	setAddress(std::get<2>(information.at(0)));
	setCity(std::get<3>(information.at(0)));
	setState(std::get<4>(information.at(0)));
	setZip(std::get<5>(information.at(0)));
	setStatus(std::get<6>(information.at(0)));

	// Load session records
	for (auto file: fs::directory_iterator(MEMBER_DATA_DIR + std::to_string(id) + SESSION_DATA_SUBDIR)) {
		Session newSession;
		if (file.path() != "dummyFile" && newSession.loadInformation(file.path()))
			sessions.push_back(newSession);
	}

	return true;
}

void Member::saveSession(Session session)
{
	sessions.push_back(session);

	// write session to disk
	std::time_t dateTimeT = std::chrono::system_clock::to_time_t(session.getDateProvided());
	std::tm dateTm = *std::localtime(&dateTimeT);
	std::ostringstream dateString;
	dateString << std::put_time(&dateTm, "%m-%d-%Y");
	std::string sessionPath = MEMBER_DATA_DIR + std::to_string(id) + SESSION_DATA_SUBDIR + dateString.str() + "_" + name + ".csv";
	session.saveRecord(sessionPath);
}

void Member::weekReport(std::ostream& out) const
{
	out << "Weekly Member Report" << std::endl;
	out << "Member name: " << name << std::endl;
	out << "Member number: " << id << std::endl;
	out << "Member street address: " << address << std::endl;
	out << "Member city: " << city << std::endl;
	out << "Member state: " << state << std::endl;
	out << "Member zip code: " << zip << std::endl;


	// Find services provided in the last 7 days
	// This gets the date 7 days ago using std::chrono dark magic (a day is 86400 seconds)
	// Basically this takes the current time minus 7 days then rounds it down with floor to the nearest day
	std::chrono::system_clock::time_point dateAWeekAgo(std::chrono::floor<std::chrono::duration<int, std::ratio<86400>>>(std::chrono::system_clock::now() - (std::chrono::hours(24) * 7)));

	// Iterate through sessions printing ones that are within 7 days ago
	for (auto session = sessions.begin(); session != sessions.end(); session++) {
		if ((*session).getDateProvided() == dateAWeekAgo || (*session).getDateProvided() > dateAWeekAgo) {
			// Convert service date for printing
			std::time_t dateProvided = std::chrono::system_clock::to_time_t((*session).getDateProvided());

			out << "Date of service: " << std::put_time(std::localtime(&dateProvided), "%m-%d-%Y") << std::endl;
			out << "Provider name: " << (*session).getProviderName() << std::endl;
			out << "Service name: " << (*session).getServiceProvided().getName() << std::endl << std::endl;
		}
	}
}

void Member::printWeekReport() const
{
	weekReport(std::cout);
}

bool Member::saveWeekReport(std::string filePath) const
{
	std::ofstream file(filePath);

	if (!file.is_open())
		return false;

	weekReport(file);
	file.close();
	return true;
}

void Member::setID(unsigned int newID)
{
	id = resizeNumber(newID, ID_DIGITS);
}

void Member::setName(std::string newName)
{
	if (newName.size() > NAME_CHARACTERS)
		newName.resize(NAME_CHARACTERS);

	name = newName;
}

void Member::setAddress(std::string newAddress)
{
	if (newAddress.size() > ADDRESS_CHARACTERS)
		newAddress.resize(ADDRESS_CHARACTERS);

	address = newAddress;
}

void Member::setCity(std::string newCity)
{
	if (newCity.size() > CITY_CHARACTERS)
		newCity.resize(CITY_CHARACTERS);

	city = newCity;
}

void Member::setState(std::string newState)
{
	if (newState.size() > STATE_CHARACTERS)
		newState.resize(STATE_CHARACTERS);

	state = newState;
}

void Member::setZip(unsigned int newZip)
{
	zip = resizeNumber(newZip, ZIP_DIGITS);
}

void Member::setStatus(bool newStatus)
{
	status = newStatus;
}

unsigned int Member::getID() const
{
	return id;
}

std::string Member::getName() const
{
	return name;
}

std::string Member::getAddress() const
{
	return address;
}

std::string Member::getCity() const
{
	return city;
}

std::string Member::getState() const
{
	return state;
}

unsigned int Member::getZip() const
{
	return zip;
}

bool Member::getStatus() const
{
	return status;
}

void Member::printMemberInfo() const
{
	std::cout << "Member Information" << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Address: " << address << std::endl;
	std::cout << "City: " << city << std::endl;
	std::cout << "State: " << state << std::endl;
	std::cout << "Zip: " << zip << std::endl;

	std::cout << "Status: ";
	if (status)
		std::cout << "Valid" << std::endl;
	else
		std::cout << "Suspended" << std::endl;
}

bool operator<(const Member& left_side, const Member& right_side)
{
	return left_side.id < right_side.id;
}


bool operator<(const unsigned int& left_side, const Member& right_side)
{
	return left_side < right_side.id;
}


bool operator<(const Member& left_side, const unsigned int& right_side)
{
	return left_side.id < right_side;
}



