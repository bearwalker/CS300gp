//Combined header file to be included in all cpps

#include <string>
#include <cctype>
#include <iostream>

//constants for cin
const int CHARMAX = 20; //max for any string readin?
const int INTMAX = 6; //max for num read in such as ids
const int MAX = 256; //for ignores


//Class definitions

//Def of service struct
struct Service
{
    void setInfo();     //Set the service info
    uint ID;            //Service id code (max 6)
    std::string name;        //Service name (max 20)
    float price;        //Service cost (max 5)
    int times_used;     //Times service used (max 3)
};

//Def of provider class


//Def of member class

class Member
{
	public: 
		Member(); //initializes members to 0
		~Member(); //deallocates LLL
		bool printMemberInfo(int); //Searches for member based on ID number.  Retruns false if member not found in list.
		void printAllMembers();//Prints all members in list
		void setMemberInfo(); //sets member info from user. Refactor to read in from file.
		void createMember(); //TODO: creates a single member
		void getMemberInfo(Member);
		//void addService(Service);
	private:
		node * head;
		int ID_number;
		int Mem_status;
		string name;
		string address;
		string city;
		string state;
		int zip;
};

struct node
{
	node * next;
	Member member;
}
	


//Helper functions

//Main.cpp
void managerTerminal(member * , provider *);
void providerTerminal(provider *);
