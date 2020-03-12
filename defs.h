//Combined header file to be included in all cpps
#pragma once

#include <string>
#include <cctype>
#include <iostream>
#include <set>
#include <chrono>
#include <fstream>
#include <tuple>
#include <vector>

#include "csvParser.h"

//constants for cin
const int CHARMAX = 20; //max for any std::string readin?
const int INTMAX = 6; //max for num read in such as ids
const int MAX = 256; //for ignores

// Private data length constraints
const unsigned int ID_DIGITS = 9;
const unsigned int NAME_CHARACTERS = 25;
const unsigned int ADDRESS_CHARACTERS = 25;
const unsigned int CITY_CHARACTERS = 25;
const unsigned int STATE_CHARACTERS = 2;
const unsigned int ZIP_DIGITS = 5;


//Class definitions
class Member;

//Def of service struct
struct Service
{
    void setInfo();     //Set the service info
    void displayInfo(); //Display service info
    unsigned int ID;    //Service id code (max 6)
    std::string name;   //Service name (max 20)
    float price;        //Service cost (max 5)
    int times_used;     //Times service used (max 3)
};

//Def of provider class
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
	void createSessionReport(Member member, Service service, std::chrono::system_clock::time_point time);

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
	std::set<Service, std::less<>> servicesProvided;
};


//Def of member class

class Member
{
	public:
		Member(); //initializes members to 0
		bool printMemberInfo(); //Searches for member based on ID number.  Retruns false if member not found in list.
		void setMemberInfo(); //sets member info from user. Refactor to read in from file.
		bool getMemStatus();
		void memberInactive();
		void printMemServices();
		void addService(Service);

		//these operators need to overloaded in order to use set
		//for sorting a set of Members
		friend bool operator<(const Member& left_side, const Member& right_side);
		//for finding a Member in a set based on its ID
		friend bool operator<(const unsigned int& left_side, const Member& right_side);
		friend bool operator<(const Member& left_side, const unsigned int& right_side);
	private:
		unsigned int ID_number;
		bool Mem_status;
		std::string name;
		std::string address;
		std::string city;
		std::string state;
		int zip;
		std::set<Service, std::less<>> servicesUsed;
};



//Helper functions
bool operator<(const Service& leftSide, const Service& rightSide);
bool operator<(const unsigned int& leftSide, const Service& rightSide);
bool operator<(const Service& leftSide, const unsigned int& rightSide);

//Main.cpp
void managerTerminal(std::set<Member> mtree, std::set<Provider> ptree);
void providerTerminal(Provider *, std::set<Member> mtree);
