//Member class for ChocAn

#include <string>
#include <iostream>
#include "defs.h"



bool Member::printMemberInfo()
{
	std::cout << "ID: " << ID_number << std::endl;
	std::cout << "Member Status: " << Mem_status << std::endl;
	std::cout << "Member Name: " << name << std::endl;
	std::cout << "Address: " << address << std::endl;
	std::cout << city << ", " << state << " " << zip << std::endl << std::endl;
	return true;

}


// TODO: Read in data from file instead.
void Member::setMemberInfo()
{
	//TODO: use .resize to make inputs match the specifications in the requirements doc

	int num;
	std::string a_string;

	std::cout << "ID: ";
	std::cin >> ID_number;
	std::cin.ignore(MAX, '\n');
	
	std::cout << "Name: ";
	std::getline(std::cin, name);
	std::cin.ignore(MAX, '\n');

	std::cout << "Address: ";
	std::getline(std::cin, address);
	std::cin.ignore(MAX, '\n');

	std::cout << "City: ";
	std::getline(std::cin, city);
	std::cin.ignore(MAX, '\n');
	
	std::cout << "State: ";
	std::getline(std::cin, state);
	std::cin.ignore(MAX, '\n');

	std::cout << "Zip: ";
	std::cin >> zip;
	std::cin.ignore(MAX, '\n');

	return;


}


bool Member::getMemStatus()
{
	return Mem_status;
}


void Member::memberInactive()
{
	Mem_status = 0;
}

void Member::printMemServices()
{
	float total = 0;

	for(std::set<Service>::iterator service = servicesUsed.begin(); service != servicesUsed.end(); service++)
	{
		total += service->price * service->times_used;

		std::cout << "Service ID: " << service->ID << std::endl;
		std::cout << "Service Name: " << service->name << std::endl;
		std::cout << "Service Price: " << service->price << std::endl;
		std::cout << "Times Used: " <<  service->times_used << std::endl;
	}
	std::cout << "Total Fees: $" << total << std::endl;

}


void Member::addService(Service used)
{
	std::set<Service>::iterator serviceIterator = servicesUsed.find<unsigned int>(used.ID);
	
	if(serviceIterator == servicesUsed.end())
		servicesUsed.insert(used);
/*	else
	{	Service repeated = servicesUsed.extract(serviceIterator);
		++(repeated.times_used);
		servicesUsed.insert(repeated);
	}
*/
}


bool operator<(const Member& left_side, const Member& right_side)
{
	return left_side.ID_number < right_side.ID_number;
}


bool operator<(const unsigned int& left_side, const Member& right_side)
{
	return left_side < right_side.ID_number;
}


bool operator<(const Member& left_side, const unsigned int& right_side)
{
	return left_side.ID_number < right_side;
}


Member::Member()
{
	ID_number = 0;
	Mem_status = 1;
	name = "";
	address = "";
	city = "";
	state = "";
	zip = 0;
}


//no dynamic memory, no destructor needed

// test the functions here as the client in main()
int main(){
	Member members;

	// tests setMemberInfo function
	members.setMemberInfo();
	
	std::cout << "Status: " << members.getMemStatus() << std::endl;

	members.memberInactive();

	std::cout << "Status: " <<members.getMemStatus() << std::endl;

	// tests printMemberInfo function
	std::cout << "\nMember Info: " << std::endl;
	if(members.printMemberInfo() == false){
		std::cout << "\nMember not Found" << std::endl;
	}

	return 0;

}
