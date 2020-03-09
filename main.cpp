//Implementation of the login,Provider, and man terminals

#include "defs.h"  //combined definitions list

//Manager terminal
void managerTerminal(std::set<Member, std::less<>> mtree, std::set<Provider, std::less<>> ptree)
{

    char response;
    do
    {
        std::cout << '\n' << "Enter A to add new Member"
        << '\n' << "Enter B to remove a Member"
        << '\n' << "Enter C to add new Provider"
        << '\n' << "Enter D to remove a Provider"
        << '\n' << "Enter E to print Member reports"
        << '\n' << "Enter F to print Provider report"
        << '\n' << "Enter G to print Manager report"
        << '\n' << "Enter H to edit Member info"
        << '\n' << "Enter I to edit Provider info"
        << '\n' << "Enter Q to exit the manager terminal"
        << '\n' << "Input: ";
        std::cin >> response;
        std::cin.ignore(MAX,'\n');
        response = toupper(response);
        switch (response)
        {
            case 'A':{
                //add Member to the Member tree
                Member new_Member;
                new_Member.setMemberInfo();
                mtree.insert(new_Member);
                break;
                }
            case 'B':{
                //find and remove a Member from Provider tree
                int mem_ID_to_remove;
                std::cout << '\n' << "Enter the ID of the Member to remove: ";
                std::cin >> mem_ID_to_remove;
                std::cin.ignore(MAX,'\n');
                Member * to_remove = mtree.extract(mtree.find<unsigned int>(mem_ID_to_remove));
                if(to_remove == NULL)
                    std::cout <<'\n' << "Member was not found";
                else
                    std::cout << '\n' << "Member #" << mem_ID_to_remove << " was removed";
                break;
                }
            case 'C':{
                //add Provider to Provider tree
                Provider new_Provider;
                new_Provider.setInfo();
                new_Provider.setServices();
                ptree.insert(new_Provider);
                break;
                }
            case 'D':{
                //find and remove Provider from Provider tree
                int prov_ID_to_remove;
                std::cout << '\n' << "Enter the ID of the Member to remove: ";
                std::cin >> prov_ID_to_remove;
                std::cin.ignore(MAX,'\n');
                Provider * to_remove = ptree.extract(ptree.find(prov_ID_to_remove));
                if(to_remove == NULL)
                    std::cout <<'\n' << "Provider was not found";
                else
                    std::cout << '\n' << "Provider #" << prov_ID_to_remove << " was removed";
                break;
                }
            case 'E':{
                //print reports for all Members
                for(auto mem_ptr = mtree.begin(); mem_ptr != mtree.end(); mem_ptr++)
                {
            //TODO:
                //print Members info
                //print Members service tree
                }
                break;
                }
            case 'F':{
                //get desired Provider and print their report
                int prov_ID;
                std::cout << '\n' << "Enter the ID of the Provider to print: ";
                std::cin >> prov_ID;
                std::cin.ignore(MAX,'\n');
                Provider * prov_to_print = ptree.extract(ptree.find(prov_to_print));
                prov_to_print->summaryReport();
                break;
                }
            case 'G':{
                //print the manager report
                float prov_service_total;
                int total_Providers;
                for(auto prov_ptr = ptree.begin(); prov_ptr != ptree.end(); prov_ptr++)
                {
            //TODO:
             //total_Providers += prov_ptr->didProvide()
             //prov_service_total += prov_ptr->gettotal()
             //prov_ptr->printManReport();
                }
                std::cout << '\n' << "Total Providers for week: " << total_Providers;
                std::cout << '\n' << "Overall Fee Total: " << prov_service_total;
                break;
                }
            case 'H':{
                //find Member and edit their info
                int mem_ID_to_edit;
                std::cout << '\n' << "Enter the ID of the Member to edit: ";
                std::cin >> mem_ID_to_edit;
                std::cin.ignore(MAX,'\n');
                Member * to_edit = mtree.extract(mtree.find(mem_ID_to_edit));
                if(to_edit == NULL)
                    std::cout << '\n' << mem_ID_to_edit << " was not a valid ID";
                else
                    to_edit->setMemberInfo();
                break;
                }
            case 'I':{
                //find Provider and edit their info
                int prov_ID_to_edit;
                std::cout << '\n' << "Enter the ID of the Provider to edit: ";
                std::cin >> prov_ID_to_edit;
                std::cin.ignore(MAX,'\n');
                Provider * to_edit = ptree.extract(ptree.find(prov_ID_to_edit));
                if(to_edit == NULL)
                    std::cout << '\n' << prov_ID_to_edit << " was not a valid ID";
                else
                    to_edit->setInfo();
                break;
                }
            case 'Q':
                break;
    }while(response != 'Q');

    //update the Member and Provider files

    return;
}

//Provider terminal
void providerTerminal(Provider * this_Provider, std::set<Member, std::less<>> mtree)
{

    char response;
    int numres;
    bool svalid;

    do{
        std::cout << '\n' << "Enter A to check Member ID status"
        << '\n' << "Enter B to add a new service"
        << '\n' << "Enter C to check service ID"
        << '\n' << "Enter D to view services list"
        << '\n' << "Enter E to provide service"
        << '\n' << "Enter F to print Provider report"
        << '\n' << "Enter Q to exit terminal"
        << '\n' << "Input: ";
        std::cin >> response;
        std::cin.ignore(MAX,'\n');
        response = toupper(response);
        switch (response)
        {
            case 'A':{
                std::cout << "Enter Member ID: "; //implement functionality to check list of valid and suspended ID's
                std::cin >> numres;
                std::cin.ignore(MAX,'\n');
                Member * mvalid = mtree.extract(mtree.find(numres));
                if (mvalid == NULL) std::cout << "Member ID is invalid.\n";
                else if (mvalid->getMemStatus() == -1) std::cout << "Membership has been suspended.\n";
                else std::cout << "Member ID is valid.\n";
                break;
                }
            case 'B':{
                this_Provider.addService();
                break;
                }
            case 'C':{
                std::cout << "Enter Service ID: ";  //implement functionality to check list of valid ID's
                std::cin >> numres;
                std::cin.ignore(MAX,'\n');
                svalid = this_Provider->checkServiceID(numres);
                if (svalid == -1) std::cout << "Service ID is not valid.\n";
                else std::cout << "Service ID " << numres << " is valid.\n";
                break;
                }
            case 'D':{
                this_Provider->printServiceList();
                break;
                }
            case 'E':{
                std::cout << "Enter Member ID: "; //implement functionality to check list of valid and suspended ID's
                std::cin >> numres;
                std::cin.ignore(MAX,'\n');
                Member * mvalid = mtree.extract(mtree.find(numres));
                if (mvalid == NULL) std::cout << "Member ID is invalid.\n";
                else if (mvalid->getMemStatus() == -1) std::cout << "Membership has been suspended.\n";
                else
                {
                    std::cout << "Enter Service ID: ";  //implement functionality to check list of valid ID's
                    std::cin >> numres;
                    std::cin.ignore(MAX,'\n');
                    svalid = this_Provider->checkServiceID(numres);
                    if (svalid == -1) std::cout << "Service ID is not valid.\n";
                    else std::cout << "ERROR: SERVICE PROVISION FUNCTIONALITY NOT IMPLEMENTED.\n";
                }
                break;
                }
            case 'F':{
                this_Provider.summaryReport();
                break;
                }
            case 'Q':
                return;
                break;
            default:
                std::cout << "Unknown command.";
        }
    }while(response != 'Q');
    return;
}

//login terminal that branches to Provider or manager
int main(void)
{
    char response;
    int check_id;
    int manID = 123456;
    std::set<Provider, std::less<>> ptree;
    std::set<Member, std::less<>> mtree;
    //read in Provider tree
    //read in Member tree

    std::cout << "Enter 'P' for Provider or 'M' for manager : ";
    std::cin >> response;
    response = toupper(response);
    if(response == 'M')
    {
        std::cout << '\n' << "Enter manager ID: ";
        std::cin.get(check_id,INTMAX);
        if(check_id == manID)
            managerTerminal(mtree,ptree);
    }
    else if(response == 'P')
    {
        std::cout << '\n' << "Enter Provider ID: ";
        std::cin.get(check_id,INTMAX);
        if(check_id == "one of the Provider ids")
            //find Provider in Provider tree
            ProviderTerminal(/*found Provider*/);
    }
    else
        std::cout << "Invalid command.\n";

    return 0;
}
