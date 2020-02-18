//Member class

#include <string>
#include <iostream>
#include "tree.hh"
using namespace std;

class Member
{
	public:
		void printMemberInfo();
		void setMemberInfo();
		void getMemberInfo(Member);
		void addService(Service);

	private:
		int ID_number;
		string Mem_status;
		string name;
		string address;
		string city;
		string state;
		int zip;
		tree<Service> Used;
};

//should this print member info or supply info to interface developers?
void Member::printMemberInfo()
{
	cout << ID_number << endl;
	cout << Mem_status << endl;
	cout << name << endl;
	cout << address << endl;
	cout << city << ", " << state << zip << endl;
	//print service tree?
}


void Member::setMemberInfo()
{
	


}


void Member::getMemberInfo(Member)
{



}


void Member::addService(Service)
{



}
