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
        switch (response)
        {
            case 'A':
            //add member to the member tree
                break;
            case 'B':
            //find and remove member from member tree
                break;
            case 'C':
            //add provider to provider tree
                break;
            case 'D':
            //find and remove provider from provider tree
                break;
            case 'E':
            //print reports for all members
                break;
            case 'F':
            //get desired provider and print their report
                break;
            case 'G':
            //print the manager report
                break;
            case 'H':
            //find member and edit their info
                break;
            case 'I':
            //find provider and edit their info
                break;
            case 'Q':
                return;
                break;
            default: cout << "Unknown command.\n";
                break;
        }

    }while(response != 'Q')

    //update the member and provider files

    return;
}

//Provider terminal
void providerTerminal(provider * this_provider, std::set <member> mtree)
{
    //read in member tree

    char response;
    int numres;

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
        switch (response)
        {
            case 'A':
                cout << "Enter Member ID: "; //implement functionality to check list of valid and suspended ID's
                cin >> numres;
                member * mvalid = mtree.extract(find(numres));
                if (mvalid == NULL) cout << "Member ID is invalid.\n";
                else if (mvalid->getMemStatus() == FALSE) cout << "Membership has been suspended.\n";
                else cout << "Member ID is valid.\n";
                break;
            case 'B':
                cout << "ERROR: FUNCTIONALITY NOT IMPLEMENTED YET.\n";
                break;
            case 'C':
                cout << "Enter Service ID: ";  //implement functionality to check list of valid ID's
                cin >> numres;
                bool svalid = this_provider->checkServiceID(numres);
                if (svalid == FALSE) cout << "Service ID is not valid.\n";
                else cout << "Service ID is valid.\n";
                break;
            case 'D':
                this_provider->printServiceList();
                break;
            case 'E':
                cout << "Enter Member ID: "; //implement functionality to check list of valid and suspended ID's
                cin >> numres;
                member * mvalid = mtree.extract(find(numres));
                if (mvalid == NULL) cout << "Member ID is invalid.\n";
                else if (mvalid->getMemStatus() == FALSE) cout << "Membership has been suspended.\n";
                else
                {
                    cout << "Enter Service ID: ";  //implement functionality to check list of valid ID's
                    cin >> numres;
                    bool svalid = this_provider->checkServiceID(numres);
                    if (svalid == FALSE) cout << "Service ID is not valid.\n";
                    else cout << "ERROR: SERVICE PROVISION FUNCTIONALITY NOT IMPLEMENTED.\n";
                }
                break;
            case 'F':
                cout << "ERROR: FUNCTIONALITY NOT IMPLEMENTED YET.\n";
                break;
            case 'Q':
                return;
                break;
            default: cout << "Unknown command."
        }
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
    else if(response == 'P')
    {
        cout << '\n' << "Enter provider ID: ";
        cin.get(check_id,INTMAX);
        if(check_id == "one of the provider ids")
            //find provider in provider tree
            providerTerminal(/*found provider*/);
    }
    else cout << "Invalid command.\n";

    return 0;
}
