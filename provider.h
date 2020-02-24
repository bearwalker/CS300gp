#pragma once

#include <chrono>
#include <set>
#include <string>

// Private data length constraints
const 

class Provider {
public:
	Provider();
	Provider(std::string informationFile);
	bool loadInformation(std::string informationFile);
	bool checkServiceID(unsigned int serviceId);
	// Set up a new provider interactively
	void setProviderInfo();
	void printServiceList();
	void createSessionReport(Member member, Service service, std::chrono::time_point time);
	void summaryReport();
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
	std::set<Service> servicesProvided;
};
