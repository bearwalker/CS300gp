#pragma once

#include <chrono>
#include <map>
#include <string>

class Provider {
public:
	Provider(std::string informationFile);
	bool checkServiceID(unsigned int serviceId);
	void printServiceList();
	void createSessionReport(Member member, Service service, std::chrono::time_point time);
	void summaryReport();

private:
	unsigned int id;
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	unsigned int zip;
	std::map<Service> servicesProvided;
};


	
