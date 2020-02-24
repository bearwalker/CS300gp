//Member class for ChocAn

#include <string>
#include <iostream>
//#include "tree.hh"
using namespace std;

//defs moved to header
//using a tree as the data structure, this is managed in main. 
//We don't have to worry about the member data structure.

//TODO: should this print member info or supply info to interface developers?
bool Member::printMemberInfo(int ID){
	if(ID == current->member.ID_number)
	{
		cout << "ID: " << ID_number << endl;
		cout << "Member Status: " << Mem_status << endl;
		cout << "Member Name: " << name << endl;
		cout << "Address: " << address << endl;
		cout << city << ", " << state << " " << zip << endl << endl;
		return true;
	}
	return false;

}

// TODO: Transfer to constructor?
// TODO: Read in data from file instead.
void Member::setMemberInfo()
{
	//TODO: first check if member exists
	//TODO: use .resize to make inputs match the specifications in the requirements doc

	int num;
	string a_string;

	cout << "ID: ";
	cin >> ID_number;
	cin.ignore(MAX, '\n');
	
	cout << "Name: ";
	getline(cin, Name);
	cin.ignore(MAX, '\n');

	cout << "Address: ";
	getline(cin, address);
	cin.ignore(MAX, '\n');

	cout << "City: ";
	getline(cin, city);
	cin.ignore(MAX, '\n');
	
	cout << "State: ";
	getline(cin, state);
	cin.ignore(MAX, '\n');

	cout << "Zip: ";
	cin >> zip;
	cin.ignore(MAX, '\n');

	//TODO: initialize service tree

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

//TODO: implement function, see other classes to see how to implement print a set
void Member::printMemServices()
{

}


//TODO: implement functon, see other class for example of how to add new item to set
void Member::addService(Service)
{
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


	// tests printMemberInfo function
	cout << "\nEnter in member's ID to search for in list: ";
	int num;
	cin >> num;
	if(members.printMemberInfo(num) == false){
		cout << "\nMember not Found" << endl;
	}

	return 0;

}
