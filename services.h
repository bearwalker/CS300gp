//Services struct

#include <string>
#include <cctype>
#include <iostream>

//Declaration to go in combined .h
const int CHARMAX = 20; //max for any string readin?
const int INTMAX = 6; //max for num read in such as ids
const int MAX = 256; //for ignores
//Def of service class
struct Service
{
    //Service();          //Constructor
    //~Service();         //Destructor
    void setInfo();     //Set the service info
    uint ID;            //Service id code (max 6)
    std::string name;        //Service name (max 20)
    float price;        //Service cost (max 5)
    int times_used;     //Times service used (max 3)
};
//End of section of .h
