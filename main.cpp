//Implementation of the login,provider, and man terminals

#include "defs.h"  //combined definitions list
using namespace std;

//Manager terminal
void managerTerminal(std::set <member> mtree, std::set <provider> ptree)
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
        cin.ignore(MAX,'\n');
        response = toupper(response);
        if(response == 'A'){
            //add member to the member tree
            member new_member;
            new_member.setMemberInfo();
            mtree.insert(new_member);
        }
        if(response == 'B'){
            //find and remove a member from provider tree
            int mem_ID_to_remove;
            cout << '\n' << "Enter the ID of the member to remove: ";
            cin >> mem_ID_to_remove;
            cin.ignore(MAX,'\n');
            member * to_remove = mtree.extract(find(mem_ID_to_remove));
            if(to_remove == NULL)
                cout <<'\n' << "Member was not found";
            else
                cout << '\n' << "Member #" << mem_ID_to_remove << " was removed";
        }
        if(response == 'C'){
            //add provider to provider tree
            provider new_provider;
            new_provider.setInfo();
            new_provider.setServices();
            ptree.insert(new_provider);
        }
        if(response == 'D'){
            //find and remove provider from provider tree
            int prov_ID_to_remove;
            cout << '\n' << "Enter the ID of the member to remove: ";
            cin >> prov_ID_to_remove;
            cin.ignore(MAX,'\n');
            member * to_remove = mptree.extract(find(prov_ID_to_remove));
            if(to_remove == NULL)
                cout <<'\n' << "Provider was not found";
            else
                cout << '\n' << "Provider #" << prov_ID_to_remove << " was removed";
        }
        if(response == 'E'){
            //print reports for all members
            for(auto mem_ptr = mtree.begin(); mem_ptr != mtree.end(); mem_ptr++)
            {
            TODO:
                //print members info
                //print members service tree
            }
        }
        if(response == 'F'){
            //get desired provider and print their report
            int prov_ID;
            cout << '\n' << "Enter the ID of the provider to print: ";
            cin >> prov_ID;
            cin.ignore(MAX,'\n');
            provider * prov_to_print = mptree.extract(find(prov_to_print));
            prov_to_print.summaryReport();
        }
        if(response == 'G'){
            //print the manager report
            float prov_service_total;
            int total_providers;
            for(auto prov_ptr = ptree.begin(); prov_ptr != mtree.end(); prov_ptr++)
            {
            TODO:
             //total_providers += prov_ptr->didProvide()
             //prov_service_total += prov_ptr->gettotal()
             //prov_ptr->printManReport();
            }
            cout << '\n' << "Total Providers for week: " << total_providers;
            cout << '\n' << "Overall Fee Total: " << prov_service_total;
        }
        if(response == 'H')
        {
            //find member and edit their info
            int mem_ID_to_edit;
            cout << '\n' << "Enter the ID of the member to edit: ";
            cin >> mem_ID_to_edit;
            cin.ignore(MAX,'\n');
            member * to_edit = mtree.extract(find(mem_ID_to_edit));
            if(to_edit == NULL)
                cout << '\n' << mem_ID_to_edit << " was not a valid ID";
            else
                to_edit->setMemberInfo();

        }
        if(response == 'G'){
            //find provider and edit their info
            int prov_ID_to_edit;
            cout << '\n' << "Enter the ID of the provider to edit: ";
            cin >> prov_ID_to_edit;
            cin.ignore(MAX,'\n');
            provider * to_edit = mtree.extract(find(prov_ID_to_edit));
            if(to_edit == NULL)
                cout << '\n' << prov_ID_to_edit << " was not a valid ID";
            else
                to_edit->setInfo();
        }
    }while(response != 'Q')

    //update the member and provider files

    return;
}

//Provider terminal
void providerTerminal(provider *& this_provider)
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
    std::set <provider> ptree;
    std::set <member> mtree;
    //read in provider tree
    //read in member tree

    cout << "Enter 'P' for provider or 'M' for manager : ";
    cin >> response;
    response = toupper(response);
    if(response == 'M')
    {
        cout << '\n' << "Enter manager ID: ";
        cin.get(check_id,INTMAX);
        if(check_id == "123456")
            managerTerminal(mtree,ptree);
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
