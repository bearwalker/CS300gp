#pragma once

#include <chrono>
#include <set>
#include <string>

class Provider {
public:
	Provider();
	Provider(std::string informationFile);
	bool loadInformation(std::string informationFile);
	bool checkServiceID(unsigned int serviceId);
	void printServiceList();
	void createSessionReport(Member member, Service service, std::chrono::time_point time);
	void summaryReport();
	// For sorting a std::set of Providers
	friend bool operator<(const Provider& left_side, const Provider& right_side);
	// For finding a Provider in a set based on its ID
	friend bool operator<(const unsigned int& left_side, const Provider& right_side);
	friend bool operator<(const Provider& left_side, const unsigned int& right_side);

private:
	unsigned int id;
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	unsigned int zip;
	std::set<Service> servicesProvided;
};
