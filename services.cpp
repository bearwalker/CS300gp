//Service class functions implementation

#include "defs.h"
using namespace std;

//Set service info
void Service::setInfo()
{

    cout << '\n' << "Enter Service ID: ";
    cin >> ID;
    cin.ignore(MAX,'\n');


    cout << '\n' << "Enter Service Name: ";
    getline(cin,name);
    cin.ignore(MAX,'\n');
    name.resize(CHARMAX);

    cout << '\n' << "Enter Service Price: ";
    cin >> price;
    cin.ignore(MAX,'\n');

    return;
}

bool operator<(const Service& leftSide, const Service& rightSide) {
	return left_side.id < right_side.id;
}

bool operator<(const unsigned int& leftSide, const Service& rightSide) {
	return left_side < right_side.id;
}

bool operator<(const Service& leftSide, const unsigned int& rightSide) {
	return left_side.id < right_side;
}

//test main to make sure function is working
int main()
{
    Service new_serv;

    new_serv.setInfo();

    cout << '\n' << "Service ID: " << new_serv.ID
        << '\n' << "Service name: " << new_serv.name
        << '\n' << "Service price: " << new_serv.price
        << '\n' << "Times used: " << new_serv.times_used;
    return 0;
}
