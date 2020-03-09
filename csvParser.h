#pragma once

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

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
