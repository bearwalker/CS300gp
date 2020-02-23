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
	friend bool operator<(const Provider& left_side, const Provider& right_side);
	friend bool operator==(const Provider& left_side, const Provider& right_side);

private:
	unsigned int id;
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	unsigned int zip;
	std::set<Service> servicesProvided;
};
