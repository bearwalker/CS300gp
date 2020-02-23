//Member class for ChocAn

#include <string>
#include <iostream>
//#include "tree.hh"
using namespace std;
/*
// Forward declarations
struct node;

class Member
{
	public:
		Member(); // initializes members to 0
		~Member(); // deallocates LLL
		bool printMemberInfo(int); // Searches for member based on ID number. Returns false if member not found in list. 
		void printAllMembers(); // Prints all members in list
		void setMemberInfo(); // sets member info from user. Refactor to read in from file.
		void createMember(); // TODO: creates a single member
		void getMemberInfo(Member);
		//void addService(Service);

	private:
		node * head;

		int ID_number;
		string Mem_status; // TODO: int type would work here too, easier. 
		string name;
		string address;
		string city;
		string state;
		int zip;
		//tree<Service> Used;
};

// LLL of ChocAn members
struct node{
	node * next;
	Member member;
};

*/
//TODO: should this print member info or supply info to interface developers?
bool Member::printMemberInfo(int ID){
	node * current = head;

	while(current){
		if(ID == current->member.ID_number){
			cout << "ID: " << current->member.ID_number << endl;
			// .... TODO: print rest of member data here

			return true;
		}
		current = current->next;
	}

	return false;

}
void Member::printAllMembers()
{
	node * current = head;

	while(current){
		cout << current->member.ID_number << endl;
		//cout << Mem_status << endl;
		//cout << name << endl;
		//cout << address << endl;
		//cout << city << ", " << state << zip << endl;

		current = current->next;
	}
	//print service tree?
}

// TODO: Transfer to constructor?
// TODO: Read in data from file instead.
// sets ChocAn member info. Stops when you enter 99 (arbitrary number for test purposes only)
void Member::setMemberInfo()
{
	int num;
	node * current;

	cout << "ID: ";
	cin >> num;

	while(num != 99){ // TODO: change this condition to something more sensible.
		if(!head){
			head = new node;
			head->next = NULL;
			current = head;
		}
		else{
			node * temp = new node;
			temp->next = NULL;
			current->next = temp;
			current = temp;
		}
		current->member.ID_number = num;
		// TODO: ... rest of data members here
		
		cout << "ID: ";
		cin >> num;
	}

}


void Member::getMemberInfo(Member)
{

}


// Commented out so file is compileable (no "Service" type)
/*
void Member::addService(Service)
{
}
*/

// TODO: initialize all variables to their 0 equivalent.
Member::Member(){
	ID_number = 0;
	zip = 0;
	head = NULL;
}

Member::~Member(){
	if(!head){
		return;
	}
	node * temp = head;
	while(temp){
		temp = temp->next;
		delete head;
		head = temp;
	}
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
