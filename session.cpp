#include <ctime>
#include <string>

#include "defs.h"
#include "csvParser.h"

Session::Session()
{
	comments = "";
}

Session::Session(std::string informationFile)
{
	if (!loadInformation(informationFile))
		comments = "";
}

bool Session::loadInformation(std::string informationFile)
{
	// File format is id of member provided to,id of service provided,date provided MM-DD-YYYY,time recorded MM-DD-YYYY HH:MM:SS,comments;
	std::vector<std::tuple<unsigned int, unsigned int, std::string, std::string, std::string>> information;

	if (!parseFile<unsigned int, unsigned int, std::string, std::string, std::string>(informationFile, information))
		return false;

	// Construct member and service from their data files
	Member member(MEMBER_DATA_DIR + std::to_string(std::get<0>(information.at(0))) + ".csv");
	setProvidedTo(member);
	Service service(SERVICE_DATA_DIR + std::to_string(std::get<1>(information.at(0)) + ".csv"));
	setServiceProvided(service);

	// Create time_point from date string
	std::tm date;
	std::istringstream dateStream(std::get<2>(information.at(0)));

	std::string yearString;
	std::string monthString;
	std::string dayString;
	std::getline(dateStream, yearString, '-');
	std::getline(dateStream, monthString, '-');
	std::getline(dateStream, dayString);

	try {
		// tm stores years since 1900
		date.tm_year = std::stoi(yearString) - 1900;
		// months since january
		date.tm_mon = std::stoi(monthString) - 1;
		date.tm_mday = std::stoi(dayString);
	} catch (...) {
		return false;
	}

	setDateProvided(std::chrono::system_clock::from_time_t(std::mktime(&date)));
	

	// Create time_point from time string
	std::tm time;
	std::istringstream timeStream(std::get<3>(information.at(0)));

	yearString.clear();
	monthString.clear();
	dayString.clear();
	std::string hourString;
	std::string minuteString;
	std::string secondString;
	std::getline(timeStream, yearString, '-');
	std::getline(timeStream, monthString, '-');
	std::getline(timeStream, dayString, ' ');
	std::getline(timeStream, hourString, ':');
	std::getline(timeStream, minuteString, ':');
	std::gettline(timeStream, secondString);

	try {
		// tm stores years since 1900
		date.tm_year = std::stoi(yearString) - 1900;
		// months since january
		date.tm_mon = std::stoi(monthString) - 1;
		date.tm_mday = std::stoi(dayString);
		date.tm_hour = std::stoi(hourString);
		date.tm_min = std::stoi(minuteString);
		datte.tm_sec = std::stoi(secondString);
	} catch (...) {
		return false;
	}

	setTimeRecorded(std::chrono::system_clock::from_time_t(std::mktime(&time)));

	// Set comment string
	setComments(std::get<4>(information.at(0)));

	return true;
}

bool Session::saveRecord(std::string filePath)
{
	std::ofstream file(filePath);

	if (!file.is_open())
		return false;

	file << id << ',' << serviceProvided.getID() << ',';

	// Convert times to appropriate strings
	std::time_t dateProvidedTimeT = std::chrono::system_clock::to_time_t(dateProvided);
	file << std::put_time(std::localtime(&dateProvidedTimeT), "%m-%d-%Y") << ',';
	std::time_t timeRecordedTimeT = std::chrono::system_clock::to_time_t(timeRecorded);
	file << std::put_time(std::localtime(&timeRecordedTimeT), "%m-%d-%Y %H:%M:%S") << ',';

	file << comments << ';' << std::endl;

	file.close();

	return true;
}

void Session::setProvidedTo(Member member)
{
	providedTo = member;
}

void Session::setServiceProvided(Service service)
{
	serviceProvided = service;
}

void setProviderName(std::string name)
{
	if (name.size() > NAME_CHARACTERS)
		name.resize(NAME_CHARACTERS);

	providerName = name;
}

void Session::setDateProvided(std::chrono::system_clock::time_point date)
{
	dateProvided = date;
}

void Session::setTimeRecorded(std::chrono::system_clock::time_point time)
{
	timeRecorded = time;
}

void Session::setComments(std::strinng newComments)
{
	if (newComments.size() > COMMENT_CHARACTERS)
		newComments.resize(COMMENT_CHARACTERS);

	comments = newComments;
}

Member Session::getProvidedTo() const
{
	return providedTo;
}

Service Session::getServiceProvided() const
{
	return serviceProvided;
}

std::string getProviderName() const
{
	return providerName;
}

std::chrono::system_clock::time_point Session::getDateProvided() const
{
	return dateProvided;
}

std::chrono::system_clock::time_point Session::getTimeRecorded() const
{
	return timeRecorded;
}

std::string Session::getComments() const
{
	return comments;
}
