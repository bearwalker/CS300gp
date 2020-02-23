#include <fstream>
#include <string>

#include "Provider.h"

Provider::Provider() {
	id = 0;
	name = "";
	address = "";
	city = "";
	state = "";
	zip = 0;
}

Provider::Provider(std::sring informationFile) {
	// If the information file can't be read use null defaults
	if (!loadInformation(informationFile)) {
			id = 0;
			name = "";
			address = "";
			city = "";
			state = "";
			zip = 0;
	}
}

bool Provider::loadInformation(std::string informationFile) {
	// 
	std::ifstream;
}


	

bool Provider::checkServiceID(unsigned int serviceID) {
	auto serviceIterator = servicesProvided.find(serviceID);

	// Find returns an iterator to end() if it can't find it
	if (serviceIterator == servicesProvided.end())
		return false;
	else
		return true;
}


bool operator<(const Provider& left_side, const Provider& right_side) {
	return left_side.id < right_side.id;
}

bool operator<(const unsigned int& left_side, const Provider& right_side) {
	return left_side < right_side.id;
}

bool operator<(const Provider& left_side, const unsigned int& right_side) {
	return left_side.id < right_side;
}

