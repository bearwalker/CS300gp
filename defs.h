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

//Helper functions

//Main.cpp
void managerTerminal(member * , provider *);
void providerTerminal(provider *);
