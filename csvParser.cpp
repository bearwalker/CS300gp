#include <cctype>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "csvParser.h"

template <typename... Types>
bool parseFile(std::vector<std::tuple<Types...>>& fileContents, std::string filePath, char seperator, char terminator, char comment) {
	// Try and open the file
	std::ifstream file(filePath);

	if (!file.is_open())
		return false;

	// Parse file one line at a time
	while (!(file >> std::ws).eof()) {
		std::tuple<Types...> lineContents;

		if (parseLine(lineContents, file, seperator, terminator))
			fileContents.insert(lineContents);
	}

	// If we didn't read anything return false
	if (fileContents.size == 0)
		return false;
	
	return true;
}

template<typename... Types>
bool parseLine(std::tuple<Types...>& lineContents, std::ifstream& file, char seperator, char terminator, char comment) {
	// File should be open and have contents
	if (!file.is_open() || file.eof() || std::isspace(static_cast<unsigned char>(file.peek())))
		return false;

	// Grab whole line
	std::string line;
	std::getline(file, line);

	// Check if line is a comment
	if (line.at(0) == comment)
		return false;

	if (file.fail())
		return false;
	
	// Grab elements in the line
	bool returnValue = std::apply([](std::string& line, char seperator, char terminator, auto& ...element){return (getElement(line, element, seperator, terminator) && ...);}, lineContents);

	return returnValue;
}

// string, uint, int, double, float
bool getElement(std::string& element, std::string& line, char seperator, char terminator) {
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

bool getElement(int& element, std::string &line, char seperator, char terminator) {
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

bool getElement(unsigned int& element, std::string &line, char seperator, char terminator) {
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

bool getElement(float& element, std::string &line, char seperator, char terminator) {
	std::string buffer;

	// Ready raw data as string
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

bool getElement(double& element, std::string &line, char seperator, char terminator) {
	std::string buffer;

	// Ready raw data as string
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
