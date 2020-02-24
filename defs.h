//Combined header file to be included in all cpps

#include <string>
#include <cctype>
#include <iostream>
#include <set>

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
    std::string name;   //Service name (max 20)
    float price;        //Service cost (max 5)
    int times_used;     //Times service used (max 3)
};

//Def of provider class


//Def of member class

class Member
{
	public: 
		Member(); //initializes members to 0
		bool printMemberInfo(int); //Searches for member based on ID number.  Retruns false if member not found in list.
		void setMemberInfo(); //sets member info from user. Refactor to read in from file.
		bool getMemStatus();
		void memberInactive();
		void printMemServices();
		void addService(Service);

		//these operators need to overloaded in order to use set
		//for sorting a set of Members
		friend bool operator<(const Member& left_side, const Member& right_side);
		//for finding a Member in a set based on its ID
		friend bool operator<(const unsigned int& left_side, const Member& right_side);
		friend bool operator<(const Member& left_side, const unsigned int& right_side); 
	private:
		int ID_number;
		bool Mem_status;
		string name;
		string address;
		string city;
		string state;
		int zip;
};



//Helper functions

//Main.cpp
void managerTerminal(std::set <member> mtree, std::set <provider> ptree)
void providerTerminal(provider *);
