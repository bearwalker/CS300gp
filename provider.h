#pragma once

#include <chrono>
#include <set>
#include <string>

// Private data length constraints
const unsigned int ID_DIGITS = 9;
const unsigned int NAME_CHARACTERS = 25;
const unsigned int ADDRESS_CHARACTERS = 25;
const unsigned int CITY_CHARACTERS = 25;
const unsigned int STATE_CHARACTERS = 2;
const unsigned int ZIP_DIGITS = 5;

class Member;
class Service;

class Provider {
public:
	// Construct with null/empty values
	Provider();

	// Try to construct with data from given file, otherwise use null/empty values
	Provider(std::string informationFile);

	// Load provider information from the given file, true on success false
	bool loadInformation(std::string informationFile);

	// Check if the given ID is an existing service
	bool checkServiceID(unsigned int serviceId);

	// Add a new service to the service tree
	bool addService();

	// Add services to the provider interactively
	void setServices();

	// Set up a new provider interactively
	void setInfo();

	// Print the list of services provided
	void printServiceList();

	// Record a service provided to a member
	void createSessionReport(Member member, Service service, std::chrono::time_point time);

	// Print a report on all services provided
	void summaryReport();

	// Print name, number of services provided in last week, fee total for last week
	void printWeekReport();

	// Returns true if this provider provided services this week
	bool providedServices();

	// Returns total fees for the week
	float weekFeeTotal();

	// For sorting a std::set of Providers
	friend bool operator<(const Provider& leftSide, const Provider& rightSide);

// For finding a Provider in a set based on its ID
	friend bool operator<(const unsigned int& leftSide, const Provider& rightSide);
	friend bool operator<(const Provider& leftSide, const unsigned int& rightSide);

private:
	unsigned int id;
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	unsigned int zip;
	float feeTotal;
	unsigned int numServicesProvided;
	std::set<Service> servicesProvided;
};
