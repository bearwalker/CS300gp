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
const unsigned int CITY_CHARACTERS = 25;
const unsigned int STATE_CHARACTERS = 2;
const unsigned int ZIP_DIGITS = 5;


//Class definitions
class Member;

//Def of service struct
struct Service
{
    void setInfo();     //Set the service info
    unsigned int ID;            //Service id code (max 6)
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

// csvParser.cpp
/*
Parses the given csv or csv-like file.

Example usage: 
std::vector<std::tuple<int, string, double>> data;
parseFile<int, string, double>(data, "/folder/file.csv")

will read the contents of a file like this ignoring lines starting with #:
#int,string,double
1,hi,1.4;

into a tuple, which you can retrieve the elements from using std::get like so:
int myInt = std::get<0>(data.at(0))
std::string myString = std::get<1>(data.at(0));
double mydouble = std::get<2>(data.at(0));
// myInt = 1, myString = hi, myDouble = 1.4

@param fileContents - a vector of tuples, the function fills this with tuples each containing the contents of a line
@param filePath - path to the file to read
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'
@param comment - if this character is seen at the start of a line it is ignored

@return false on failure to read file, true on success, 
data is returned via reference in fileContents
*/
template <typename... Types>
bool parseFile(std::vector<std::tuple<Types...>&> fileContents, std::string filePath, char seperator = ',', char terminator = ';', char comment = '#');

/*
Parses a line in a csv or csv-like file.

Example usage:
std::tuple<int, double> data;
std::ifstream myFile("file.csv");
parseLine<int, double>(data, myFile);

will read the contents of a file like this ignoring lines starting with #:
#int,double
1,1.4

into a tuple, which you can retrieve the elements from using std::get like so:
int myInt = std::get<0>(data);
double mydouble = std::get<1>(data);
// myInt = 1, myDouble = 1.4

@param lineContents - a tuple containing the elements in the line, the function
fills this tuple
@param file - an open filestream of the file to ready from
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'
@param comment - if this character is seen at the start of a line it is ignored, 
default is '#'

@return false on failure to read line or if line is a comment,
data is returned via refernce in the lineContents tuple
*/
template<typename... Types>
bool parseLine(std::tuple<Types...>& lineContents, std::ifstream& file, char seperator = ',', char terminator = ';', char comment = '#');

/*
Grabs a string element from a csv file line.

@param element - string reference to return element in
@param line - string containing the line to extract the element from
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'

@return false on failure, true on success
*/
bool getElement(std::string& element, std::string& line, char seperator, char terminator);

/*
Grabs an int element from a csv file line.

@param element - int reference to return element in
@param line - string containing the line to extract the element from
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'

@return false on failure, true on success
*/
bool getElement(int& element, std::string &line, char seperator, char terminator);

/*
Grabs a unsigned int element from a csv file line.

@param element - unsigned int reference to return element in
@param line - string containing the line to extract the element from
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'

@return false on failure, true on success
*/
bool getElement(unsigned int& element, std::string &line, char seperator, char terminator);

/*
Grabs a float element from a csv file line.

@param element - float reference to return element in
@param line - string containing the line to extract the element from
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'

@return false on failure, true on success
*/
bool getElement(float& element, std::string &line, char seperator, char terminator);

/*
Grabs a double element from a csv file line.

@param element - double reference to return element in
@param line - string containing the line to extract the element from
@param seperator - the seperator character between elements, default is ','
@param terminator - the line termination character, default is ';'

@return false on failure, true on success
*/
bool getElement(double& element, std::string &line, char seperator, char terminator);

//Main.cpp
void managerTerminal(std::set<Member> mtree, std::set<Provider> ptree);
void providerTerminal(Provider *, std::set<Member> mtree);
