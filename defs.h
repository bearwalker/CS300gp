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

//constants for cin
const int CHARMAX = 20; //max for any std::string readin?
const int INTMAX = 6; //max for num read in such as ids
const int MAX = 256; //for ignores

// Private data length constraints
const unsigned int ID_DIGITS = 9;
const unsigned int NAME_CHARACTERS = 25;
const unsigned int ADDRESS_CHARACTERS = 25;
const unsigned int CITY_CHARACTERS = 14;
const unsigned int STATE_CHARACTERS = 2;
const unsigned int ZIP_DIGITS = 5;
const unsigned int COMMENT_CHARACTERS = 100;

// Services have different length constraints
const unsigned int SERVICE_ID_DIGITS = 6;
const unsigned int SERVICE_NAME_CHARACTERS = 20;
const double SERVICE_PRICE_MAX = 999.99;

// Data directoies
const std::string EFT_DATA_DIR = "data/eft/";
const std::string REPORT_DATA_DIR "data/reports/";
const std::string PROVIDER_DATA_DIR = "data/providers/";
const std::string MEMBER_DATA_DIR = "data/members/";
const std::string SERVICE_DATA_DIR = "data/services/";
// each PROVIDER_DATA_DIR will contain a SESSION_DATA_DIR
const std::string SESSION_DATA_SUBDIR = "sessions/";


//Def of service class
class Service
{
public:
	// Construct with empty values
	Service();

	/*
	  Try to construct the class with information about a service from a csv file, otherwise use empty values
	  The csv file format is:
	  id,name,price;

	  @param informationFile - path to a csv file containing Service info
	*/
	Service(std::string informationFile);

	/*
	  Load information about a service from a csv file in the format
	  id,name,price;

	  @param informationFile - the path to the file to load from

	  @return true on success, false on failure
	*/
	bool loadInformation(std::string informationFile);

	/*
	  Setter for id

	  @param newID - the number to set as id, will be resized to SERVICE_ID_DIGITS
	*/
	void setID(unsigned int newID);

	/*
	  Setter for name

	  @param newName - the string to set as the name, will be resized to SERVICE_NAME_CHARACTERS as needed
	*/
	void setName(std::string newName);

	/*
	  Setter for price

	  @param newPrice - the price to set as price, will be set to SERVICE_PRICE_MAX if too large
	*/
	void setPrice(double newPrice);

	/*
	  Getter for id

	  @return the services id code
	*/
	unsigned int getID() const;

	/*
	  Getter for name

	  @return the services name
	*/
	std::string getName() const;

	/*
	  Getter for price

	  @return the services price
	*/
	double getPrice() const;

	// Functions for comparing services and unsigned itns based on ids value
	friend bool operator<(const Service& leftSide, const Service& rightSide);
	friend bool operator<(const unsigned int& leftSide, const Service& rightSide);
	friend bool operator<(const Service& leftSide, const unsigned int& rightSide);

    void displayInfo(); //Display service info

private:
    unsigned int id;
    std::string name;
    double price;
};

//Helper functions




//Def of member class
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
	void getStatus() const;
	

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

// Def of Session class
class Session
{
public:
	// Construct with empty values
	Session();

	/*
	  Try to construct the class with data from a csv file, otherwise use empty values.
	  A provider csv file should be formatted as id of member provided to,id of service provided,date provided MM-DD-YYYY,time recorded MM-DD-YYYY HH:MM:SS,comments;
	  
	  @param informationFile - path to a csv file containing provider info
	*/
	Session(std::string informationFile);

	/*
	  Load information about a session from a csv file in the format
	  id of member provided to,id of service provided,date provided MM-DD-YYYY,time recorded MM-DD-YYYY HH:MM:SS,comments;

	  @param informationFile - the path to the file to load from

	  @return true on success, false on failure
	*/
	bool loadInformation(std::string informationFile);

	/*
	  Saves information about the session in the same format as loaded from

	  @param filePath - the path of the file to save to
	*/
	bool saveRecord(std::string filePath);

	/*
	  Setter for providedTo

	  @param member - the member the session was provided to
	*/
	void setProvidedTo(Member member);

	/*
	  Setter for serviceProvided

	  @param service - the service that was provided
	*/
	void setServiceProvided(Service service);

	/*
	  Setter for providerName

	  @param name - the name of the provider that provided the service
	*/
	void setProviderName(std::string name);

	/*
	  Setter for dateProvided

	  @param date - the date the service was provided
	*/
	void setDateProvided(std::chrono::system_clock::time_point date);

	/*
	  Setter for timeRecorded

	  @param time - the time the service was recorded
	*/
	void setTimeRecorded(std::chrono::system_clock::time_point time);

	/*
	  Setter for the comments, cuts comments down to first 100 characters

	  @param newComments - the comments about the service provided
	*/
	void setComments(std::string newComments);
	
	/*
	  Getter for providedTo

	  @return a member object of the member the service was provided to
	*/
	Member getProvidedTo() const;

	/*
	  Getter for serviceProvided

	  @return a service struct of the service provided
	*/
	Service getServiceProvided() const;

	/*
	  Getter for providerName

	  @return name of the provider that provided the service
	*/
	std::string getProviderName() const;
	
	/*
	  Getter for dateProvided

	  @return a time_point of the date provided
	*/
	std::chrono::system_clock::time_point getDateProvided() const;

	/*
	  Getter for timeRecorded

	  @return a time_poinnt of the time the session was recorded
	*/
	std::chrono::system_clock::time_point getTimeRecorded() const;

	/*
	  Getter foor comments

	  @return a string containing the comments on the session
	*/
	std::string getComments() const;

private:
	Member providedTo;
	Service serviceProvided;
	std::string providerName;
	std::chrono::system_clock::time_point dateProvided;
	std::chrono::system_clock::time_point timeRecorded;
	std::string comments;
};

//Def of provider class
class Provider {
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

	  @return true if services were provided in the last 7 days
	*/
	bool providedServices() const;

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

	// Add a new service to the service tree
	bool addService();

	// Add services to the provider interactively
	void setServices();

	// Set up a new provider interactively
	void setInfo();

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

// digits.cpp
/*
  Returns the number of digits in the given number (in base 10)

  @param the number to count the digits of

  @return the number of base 10 in the given number
*/
unsigned int numDigits(unsigned int number);
unsigned int numDigits(int number);

/*
  Resizes a number to the desired number of digits by 
  - cutting off digits starting in the ones place and increasing if there are too many digits
  - padding number with 0s starting in the ones place if there aren't enough digits
  - doing nothing if there are enough digits

  @param number - the number to resize
  @param desiredDigitCount - the number of digits to resize number to

  @return the resized number
*/
unsigned int resizeNumber(unsigned int number, unsigned int desiredDigitCount);
int resizeNumber(int number, unsigned int desiredDigitCount);

/*
  Shrinks a number by the given number of digits starting in the ones place

  @param number - the number to shrink
  @param numDigitsToRemove - the number of digits to remove from the number

  @return the shrunk number
*/
unsigned int shrinkNumber(unsigned int number, unsigned int numDigitsToRemove);
int shrinkNumber(int number, unsigned int numDigitsToRemove);

/*
  Pads a number by the given number of digits with 0s starting in the ones place

  @param number - the number to pad
  @param numDigitsToAdd - the number of digits to add to the number

  @return the padded number
*/
unsigned int padNumber(unsigned int number, unsigned int numDigitsToAdd);
int padNumber(int number, unsigned int numDigitsToAdd);

//Main.cpp
void managerTerminal(std::set<Member> mtree, std::set<Provider> ptree);
void providerTerminal(Provider *, std::set<Member> mtree);
