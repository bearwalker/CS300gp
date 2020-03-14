#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "session.h"

class Member
{
public:
	// Construct with empty values
	Member();

	/*
	  Try to construct the class with data from a csv file, otherwise use empty values.
	  A member csv file should be formatted as id,name,address,city,state,zip,status;
	  
	  @param informationFile - path to a csv file containing provider info
	*/
	Member(std::string informationFile);

	/*
	  Loads member information from a csv file formatted like so:
	  id,name,address,city,state,zip,status;

	  @param informationFile - path to a csv file containing member info

	  @return true on success, false on failure
	*/
	bool loadInformation(std::string informationFile);

	/*
	  Saves a session into sessions and writes to members session data directory
	  Typical usage would be to save a session returned by Provider::saveSessionReport()

	  @param session - the session to save
	*/
	void saveSession(Session session);

	/*
	  Outputs a report containing the following information for the last 7 days to the given stream:
	  - Member name 25 characters
	  - Member number 9 digits
	  - Member street address 25 characters
	  - Member city 14 characters
	  - Member state 2 characters
	  - Member zip code 5 digits
	  - Data for each service used
	  	- Date of service MM-DD-YYYY
		- Provider name 25 characters
		- Service name 20 characters

	  @param out - the ostream to output he report to
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
	  Sets the members status. False indicates suspended, true indicates valid/not suspended.

	  @param newStatus - the members new status
	*/
	void setStatus(bool newStatus);

	/*
	  Getter for ID
	  
	  @return the memberss ID
	*/
	unsigned int getID() const;

	/*
	  Getter for name

	  @return the members name
	*/
	std::string getName() const;

	/*
	  Getter for address

	  @return the members address
	*/
	std::string getAddress() const;

	/*
	  Getter for city

	  @return the city the member lives in
	*/
	std::string getCity() const;

	/*
	  Getter for state

	  @return the state the member lives in
	*/
	std::string getState() const;

	/*
	  Getter for zip

	  @return the members zip code
	*/
	unsigned int getZip() const;

	/*
	  Getter for status

	  @return the members status, false indicates suspended, true indicates not suspended/valid
	*/
	bool getStatus() const;
	

	/*
	  Prints information about the member in the following format
	  - member id
	  - member name
	  - member address
	  - member city
	  - member state
	  - member zip
	  - member status
	*/
	void printMemberInfo() const;
	
	//these operators need to overloaded in order to use set
	//for sorting a set of Members
	friend bool operator<(const Member& left_side, const Member& right_side);
	//for finding a Member in a set based on its ID
	friend bool operator<(const unsigned int& left_side, const Member& right_side);
	friend bool operator<(const Member& left_side, const unsigned int& right_side);
	
private:
	unsigned int id;
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	unsigned int zip;
	bool status;
	std::vector<Session> sessions;
};

