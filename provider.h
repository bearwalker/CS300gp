#pragma once

#include <chrono>
#include <set>
#include <string>
#include <vector>

#include "member.h"
#include "service.h"
#include "session.h"

class Provider
{
public:
	// Construct with empty values
	Provider();

	/*
	  Try to construct the class with data from a csv file, otherwise use empty values.
	  A provider csv file should be formatted as id,name,address,city,state,zip;
	  
	  @param informationFile - path to a csv file containing provider info
	*/
	Provider(std::string informationFile);

	/*
	  Loads provider information from a csv file.
	  A provider csv file should be formatted as id,name,address,city,state,zip;

	  @param informationFile - path to a csv file containing provider info

	  @return true on success, false on failure.
	*/
	bool loadInformation(std::string informationFile);

	/*
	  Saves eft data data for recording fees

	  @param filePath - the path to save the data in
	  @param fee - the amount of the fee
	*/
	bool saveEFT(std::string filePath, double fee);

	/*
	  Finds a service in the providers service directory.

	  @param serviceID - the service ID to search by
	  @param service - a reference to the found service, filled in when its found
	  
	  @return true if service was found, false if not, 
	  a reference to the service is returned via the service parameter
	*/
	bool findService(unsigned int serviceID, Service& service);

	/*
	  Check if the given ID matches an exisiting service in the service directory

	  @param serviceID - the service ID to check

	  @return true if a matching entry was found in the service directory, else false
	*/
	bool checkServiceID(unsigned int serviceId) const;

	/*
	  Prints the list of services provided, aka the contents of the service directory
	  formatted as so:
	  ID num - name - fee
	*/
	void printServiceDirectory() const;

	/*
	  Create a record of a service provided to a member
	  
	  @param member - the member the service was provided to
	  @param service - the service that was provided
	  @param dateProvided - the date the service was provided on
	  @param comments - any comments the provider wants to make on the session

	  @return the session that was created and saved
	*/
	Session saveSessionReport(Member member, Service service, std::chrono::system_clock::time_point dateProvided, std::string comments);

	/*
	  Outputs a report containing the following information for the last 7 days to the given stream:
	  - Provider name 25 characters
	  - Provider number 9 digits
	  - Provider street address 25 characters
	  - Provider city 14 characters
	  - Provider state 2 letters
	  - Providr zip 5 digits
	  - Data for each service provided: 
	  	- Date of service MM-DD-YYYY
		- Date and time data was received by computer MM-DD-YYYY HH:MM:SS
		- Member name 25 characters
		- Member number 9 digits
		- Service code 6 digits
		- Fee to be paid up to $999.99
	  - Total number of consultations in past 7 days 3 digits
	  - Total fee for the past 7 days up to $99,999.99

	  @param out - the ostream to output the report to
	 */
	void weekReport(std::ostream& out);

	/*
	  Prints weekReport to std::cout
	*/
	void printWeekReport();

	/*
	  Prints weekReport to the given file

	  @param filePath - path to the file to save the report in

	  @return true if file was opened, false if it couldn't be
	*/
	bool saveWeekReport(std::string filePath);

	/*
	  Checks if any services were provided by the provided during the last 7 days

	  @return the number of services provided in the last 7 days
	*/
	int providedServices() const;

	/*
	  Gives a total of the fees for the last 7 days of services provided

	  @return total fees for the last 7 days of services provided
	*/
	double weekFeeTotal() const;

	/*
	  Sets id to the given unsigned int, cutting it down to the first ID_DIGITS digits if too large
	  or padding it with 0's if too small

	  @param newID - the number to set ID to
	*/
	void setID(unsigned int newID);

	/*
	  Sets name to the given string, cutting it down to NAME_CHARACTERS if too large

	  @param newName - the string to set name to
	*/
	void setName(std::string newName);

	/*
	  Sets address to the given string, cutting it down to ADDRESS_CHARACTERS if too large

	  @param newAddress - the string to set address to
	*/
	void setAddress(std::string newAddress);

	/*
	  Sets city to the given string, cutting it down to CITY_CHARACTERS if too large

	  @param newCity - the string to set city to
	*/
	void setCity(std::string newCity);

	/*
	  Sets state to the given string, cutting it down to STATE_CHARACTERS if too large

	  @param newState - the string to set state to
	*/
	void setState(std::string newState);

	/*
	  Sets zip to the given unsigned int, cutting it down to ZIP_DIGITS if too large or padding with
	  0's if too small

	  @param newZip - the number to set zip to
	*/
	void setZip(unsigned int newZip);

	/*
	  Getter for ID

	  @return the providers ID
	*/
	unsigned int getID() const;

	/*
	  Getter for name

	  @return the providers name
	*/
	std::string getName() const;

	/*
	  Getter for address

	  @return the providers address
	*/
	std::string getAddress() const;

	/*
	  Getter for city

	  @return the city the provider is located in
	*/
	std::string getCity() const;

	/*
	  Getter for state

	  @return the state the provider is in
	*/
	std::string getState() const;

	/*
	  Getter for zip

	  @return the providers zip code
	*/
	unsigned int getZip() const;

	/*
	  Compares two providers based on who was the numerically lower ID number, 
	  for storing providers in std::set

	  @param leftSide - Provider on the left of the <
	  @param rightSide - Provider on the right of the <

	  @return true if leftSide's ID is numerically lower than rightSide's, else false
	*/
	friend bool operator<(const Provider& leftSide, const Provider& rightSide);

	/*
	  Compares a Provider to an unsigned int based on the Providers ID number, 
	  for searching for Providers in std::set

	  @param leftSide - ID number to compare to Provider
	  @param rightSide - Provider to compare to ID number

	  @return true if the ID number is less than the providers ID
	*/
	friend bool operator<(const unsigned int& leftSide, const Provider& rightSide);

	/*
	  Compares a Provider to an unsigned int based on the Providers ID number, 
	  for searching for Providers in std::set

	  @param leftSide - Provider to compare to ID number
	  @param rightSide - ID number to compare to Provider

	  @return true if the providers ID is less than the ID number given
	*/
	friend bool operator<(const Provider& leftSide, const unsigned int& rightSide);

private:
	unsigned int id;
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	unsigned int zip;
	std::set<Service, std::less<>> serviceDirectory;
	std::vector<Session> sessionRecords;
};
