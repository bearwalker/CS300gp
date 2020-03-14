/*
@file csvParser.h
@author Aelric Riggs

This file contains the prototypes and implementation of several functions for parsing csv and csv-like files.
Please see the comments above the function prototypes for information on how to use this parser.
Also note that due to the use of templates the implementation must be compiled whenever its used in your code, 
which is why this file contains the implementation.
*/
#pragma once

#include <cctype>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

/*
Parses the given csv file.

-How to Use-
Given a data file "example.csv" that contains:
# lines starting with # are treated as comments
# this file has the format int,string,double
1,hi,1.4;
2,hey,1.1;

The following code would read example.csv then store its data in some local variables:
std::vector<std::tuple<int, string, double>> data;
parseFile<int, string, double>(data, "/folder/example.csv")

// note that data.at(0) returns the tuple in the vector containing the first line
// std::get<index>(tuple) is used to retrieve data from tuples
int myInt = std::get<0>(data.at(0)) // myInt = 1
std::string myString = std::get<1>(data.at(0)); // myString = hi
double myDouble = std::get<2>(data.at(0)); // myDouble = 1.4
// data.at(1) contains the second line
int myInt2 = std::get<0>(data.at(1)) // myInt2 = 2
std::string myString2 = std::get<1>(data.at(1)); // myString2 = hey
double myDouble2 = std::get<2>(data.at(1)); // myDouble2 = 1.1

@param filePath - path to the file to read
@param fileContents - a vector of tuples, the function fills this with tuples each containing the contents of a line

@return false on failure to read file and true on success, data is returned via reference in fileContents
*/
template <typename... Types>
bool parseFile(std::string filePath, std::vector<std::tuple<Types...>>& fileContents);

/*
Parses the given csv or csv-like file.
This is the actual implementation of the parseFile, 
the one above just calls this with default values of seperator = ',', terminator = ';', and comment = '#'.
This function takes the same arguments as above, but with three extra argument specifying file formatting.

@param seperator - the seperator character between elements
@param terminator - the line termination character
@param comment - if this character is seen at the start of a line it is ignored
*/
template <typename... Types>
bool parseFile(std::string filePath, char seperator, char terminator, char comment, std::vector<std::tuple<Types...>>& fileContents);

/*
Parses a line in a csv file, used by parseFile.

-How to Use-
Given a file called example.csv that contains:
# lines starting with # are comments
#int,double
1,1.4;

The following code would retrieve data from first non-comment line in example.csv and store it in some variables
std::tuple<int, double> data;
std::ifstream myFile("example.csv"); // you should check if the file is valid in actual code
parseLine<int, double>(data, myFile);
// note std::get<index>(tuple) returns the value stored at that index in the tuple
int myInt = std::get<0>(data); // myInt = 1
double mydouble = std::get<1>(data); // myDouble = 1.4

@param file - an open filestream of the file to ready from
@param lineContents - a tuple containing the elements in the line, the function fills this tuple

@return False on failure to read line and true on success, data is returned via reference in the lineContents tuple
*/
template<typename... Types>
bool parseLine(std::istream& file, std::tuple<Types...>& lineContents);

/*
Parses a line the given csv or csv-like file, used by parseFile.
This is the actual implementation of the parseLine, 
the one above just calls this with default values of seperator = ',', terminator = ';', and comment = '#'.
This function takes the same arguments as above, but with three extra argument specifying file formatting.

@param seperator - the seperator character between elements
@param terminator - the line termination character
@param comment - if this character is seen at the start of a line it is ignored
*/
template<typename... Types>
bool parseLine(std::ifstream& file, char seperator, char terminator, char comment, std::tuple<Types...>& lineContents);

/*
Grabs an element from a csv line, used by parseFile and parseLine.
This function is overloaded based on the type of the element to get, 
currently std::string, int, unsigned int, float, and double are supported.

The easiest way to add support for another data type is to add another overload for this function 
that uses the string version to retrieve the raw data then converts that to the data type you want.
That's how the versions for int, unsigned int, float, and double work.

@param element - reference to return the element in
@param line - string containing the line to extract the element from, 
note that this string is modified to remove the element from the string to allow successive calls to getElement
@param seperator - the seperator character between elements
@param terminator - the line termination character

@return false on failure and true on success, data is returned via reference in element
*/
bool getElement(std::string& element, std::string& line, char seperator, char terminator);
bool getElement(int& element, std::string& line, char seperator, char terminator);
bool getElement(unsigned int& element, std::string& line, char seperator, char terminator);
bool getElement(float& element, std::string& line, char seperator, char terminator);
bool getElement(double& element, std::string& line, char seperator, char terminator);

// ----Function implementations----
template <typename... Types>
bool parseFile(std::string filePath, std::vector<std::tuple<Types...>>& fileContents)
{
	return parseFile<Types...>(filePath, ',', ';', '#', fileContents);
}

template <typename... Types>
bool parseFile(std::string filePath, char seperator, char terminator, char comment, std::vector<std::tuple<Types...>>& fileContents)
{
	// Try and open the file
	std::ifstream file(filePath);

	if (!file.is_open())
		return false;

	// Parse file one line at a time while we haven't reached the end of it
	while (!(file >> std::ws).eof()) {
		std::tuple<Types...> lineContents;

		if (parseLine<Types...>(file, seperator, terminator, comment, lineContents))
			fileContents.push_back(lineContents);
		else
			return false;
	}

	// If we didn't read anything return false
	if (fileContents.size() == 0)
		return false;

	file.close();
	return true;
}

template<typename... Types>
bool parseLine(std::istream& file, std::tuple<Types...>& lineContents)
{
	return parseLine<Types...>(file, ',', ';', '#', lineContents);
}

template<typename... Types>
bool parseLine(std::ifstream& file, char seperator, char terminator, char comment, std::tuple<Types...>& lineContents)
{
	// File should be open and have contents
	if (!file.is_open() || file.eof() || std::isspace(static_cast<unsigned char>(file.peek())))
		return false;

	// Try to grab the line
	std::string line;
	std::getline(file, line);

	if (file.fail())
		return false;

	// Skip over comments
	while (line.at(0) == comment) {
		line.clear();
		std::getline(file, line);
	}
	
	// Grab elements in the line
	// This uses C++17's std::apply and a lambda function to emulate a for loop over a std::tuple
	bool returnValue =	std::apply([&](auto&... elements) -> bool {
									   return (getElement(elements, line, seperator, terminator) && ...);
								   }, lineContents);

	return returnValue;
}

bool getElement(std::string& element, std::string& line, char seperator, char terminator)
{
	std::string::size_type seperatorPosition = line.find(seperator);
	std::string::size_type terminatorPosition = line.find(terminator);

	// If we can't find the either seperator or the terminator there we can't ready data
	if (seperatorPosition == std::string::npos && terminatorPosition == std::string::npos)
		return false;
	
	// Grab contents until seperator or terminator, whichever comes first
	if (seperatorPosition < terminatorPosition) {
		// Substring and erase go from start to start+num characters
		element = line.substr(0, seperatorPosition);
		line.erase(0, seperatorPosition + 1);
	} else {
		element = line.substr(0, terminatorPosition);
		line.erase(0, terminatorPosition + 1);
	}

	return true;
}

bool getElement(int& element, std::string& line, char seperator, char terminator)
{
	std::string buffer;

	// Read raw data as string
	if (!getElement(buffer, line, seperator, terminator))
		return false;

	// Try to convert to int
	try {
		element = std::stoi(buffer);
	} catch (...) {
		return false;
	}

	return true;
}

bool getElement(unsigned int& element, std::string& line, char seperator, char terminator)
{
	std::string buffer;

	// Read raw data as string
	if (!getElement(buffer, line, seperator, terminator))
		return false;

	// Try to convert to unsigned int
	try {
		element = std::stoul(buffer);
	} catch (...) {
		return false;
	}

	return true;
}

bool getElement(float& element, std::string& line, char seperator, char terminator)
{
	std::string buffer;

	// Read raw data as string
	if (!getElement(buffer,line,seperator, terminator))
		return false;

	// Try to convert to float
	try {
		element = std::stof(buffer);
	} catch (...) {
		return false;
	}

	return true;
}

bool getElement(double& element, std::string& line, char seperator, char terminator)
{
	std::string buffer;

	// Read raw data as string
	if (!getElement(buffer, line, seperator, terminator))
		return false;

	// Try to convert to double
	try {
		element = std::stod(buffer);
	} catch (...) {
		return false;
	}

	return true;
}

bool getElement(bool& element, std::string& line, char seperator, char terminator)
{
	std::string buffer;

	// Read raw data as string
	if (!getElement(buffer, line seperator, terminator))
		return false;

	// Convert string to uppercase
	std::transform(buffer.begin(), buffer.end(), buffer.begin(),
				   [](unsigned char character) -> unsigned char{ return std::toupper(character); });

	// Only TRUE and FALSE are valid bools
	if (buffer == "TRUE") {
		element = true;
		return true;
	} else if (buffer == "FALSE") {
		element = false;
		return true;
	}

	return false;
}
