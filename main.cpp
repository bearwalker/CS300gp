//Implementation of the login,provider, and man terminals

#include "defs.h"  //combined definitions list
using namespace std;

//Manager terminal
void managerTerminal(member * mem_head, provider * prov_head)
{

    char response;
    do
    {
        cout << '\n' << "Enter A to add new member"
        << '\n' << "Enter B to remove a member"
        << '\n' << "Enter C to add new provider"
        << '\n' << "Enter D to remove a provider"
        << '\n' << "Enter E to print member reports"
        << '\n' << "Enter F to print provider report"
        << '\n' << "Enter G to print Manager report"
        << '\n' << "Enter H to edit member info"
        << '\n' << "Enter I to edit provider info"
        << '\n' << "Enter Q to exit the manager terminal"
        << '\n' << "Input: ";
        cin >> reponse;
        response = toupper(response);
        if(response == 'A')
            //add member to the member tree
        if(response == 'B')
            //find and remove member from member tree
        if(response == 'C')
            //add provider to provider tree
        if(response == 'D')
            //find and remove provider from provider tree
        if(response == 'E')
            //print reports for all members
        if(response == 'F')
            //get desired provider and print their report
        if(response == 'G')
            //print the manager report
        if(response == 'H')
            //find member and edit their info
        if(response == 'G')
            //find provider and edit their info


    }while(response != 'Q')

    //update the member and provider files

    return;
}

//Provider terminal
void providerTerminal(provider * this_provider)
{
    //read in member tree

    char response;

    do{
        cout << '\n' << "Enter A to check a member ID"
        << '\n' << "Enter B to add a new service"
        << '\n' << "Enter C to check service ID"
        << '\n' << "Enter D to view services list"
        << '\n' << "Enter E to provide service"
        << '\n' << "Enter F to print provider report"
        << '\n' << "Enter Q to exit terminal"
        << '\n' << "Input: ";
        cin >> reponse;
        response = toupper(response);
        if(response == 'A')
            //check if member id is valid
        if(response == 'B')
            //add a new service to the providers service tree
        if(response == 'C')
            //check whether a service ID is valid
            //if it is print its info
        if(response == 'D')
            //print the list of all provider services
        if(response == 'E')
            //inc service counter for provider and member being provided the service
            //write out the session report
        if(response == 'F')
            //print the providers report

    }while(response != 'Q')
    return;
}

//login terminal that branches to provider or manager
int main()
{
    char response;
    int check_id;
    //read in provider tree
    //read in member tree
    //member * mem_head
    //provider * prov_head

    cout << "Enter 'P' for provider or 'M' for manager : ";
    cin >> response;
    response = toupper(response);
    if(response == 'M')
    {
        cout << '\n' << "Enter manager ID: ";
        cin.get(check_id,INTMAX);
        if(check_id == "123456")
            managerTerminal(mem_head,prov_head);
    }
    if(response == 'P')
    {
        cout << '\n' << "Enter provider ID: ";
        cin.get(check_id,INTMAX);
        if(check_id == "one of the provider ids")
            //find provider in provider tree
            providerTerminal(/*found provider*/);
    }

    return 0;
}
