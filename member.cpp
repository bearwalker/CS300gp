//Member class for ChocAn

#include <string>
#include <iostream>
//#include "tree.hh"
using namespace std;

//defs moved to header

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
// sets ChocAn member info. Stops when you enter 99 (arbitrary number for test purposes only)
void Member::setMemberInfo()
{
	//TODO: first check if member exists
	//TODO: use .resize to make inputs match the specifications in the requirements doc

	int num;
	string a_string;

	Mem_status = 1;

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

// Commented out so file is compileable (no "Service" type)
/*
void Member::addService(Service)
{
}
*/

// TODO: initialize all variables to their 0 equivalent.
Member::Member()
{
	ID_number = 0;
	zip = 0;
}


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
