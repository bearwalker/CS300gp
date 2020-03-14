//Implementation of the login,Provider, and man terminals

#include <iostream>
#include <set>
#include <string>

#include "defs.h" 

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
                unsigned int mem_ID_to_remove;
                std::cout << '\n' << "Enter the ID of the Member to remove: ";
                std::cin >> mem_ID_to_remove;
                std::cin.ignore(MAX,'\n');
                auto memberIterator = mtree.find<unsigned int>(mem_ID_to_remove);
                if(memberIterator == mtree.end())
                    std::cout <<'\n' << "Member was not found";
                else{
                    mtree.erase(memberIterator);
                    std::cout << '\n' << "Member #" << mem_ID_to_remove << " was removed";
                }
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
                auto providerIterator = ptree.find(prov_ID_to_remove);
                if(providerIterator == ptree.end())
                    std::cout <<'\n' << "Provider was not found";
                else{
                    ptree.erase(providerIterator);
                    std::cout << '\n' << "Provider #" << prov_ID_to_remove << " was removed";
                }
                break;
                }
            case 'E':{
                //print reports for all Members
                for(auto mem_ptr = mtree.begin(); mem_ptr != mtree.end(); mem_ptr++)
                {
                //print Members info
                //print Members service tree
                    Member to_print = *mem_ptr;
                    to_print.printMemberInfo();
                    to_print.printMemServices();
                }
                break;
            }
            case 'F':{
                //get desired Provider and print their report
                int prov_ID;
                std::cout << '\n' << "Enter the ID of the Provider to print: ";
                std::cin >> prov_ID;
                std::cin.ignore(MAX,'\n');
                auto prov_to_print = ptree.find(prov_ID);
                Provider to_print = *prov_to_print;
                to_print.summaryReport();
                break;
            }
            case 'G':{
                //print the manager report
                float prov_service_total=0;
                int total_Providers =0;
                for(auto prov_ptr = ptree.begin(); prov_ptr != ptree.end(); prov_ptr++)
                {
                    int servicesProvided = 0;
                    Provider to_print = *prov_ptr;
                    servicesProvided = to_print.providedServices();
                    if(servicesProvided > 0){
                        ++total_Providers;
                        prov_service_total += to_print.weekFeeTotal();
                        std::cout << '\n' << "Provider: " << to_print.getName() << " provided " << servicesProvided << " this week" << '\n';

                    }
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
                auto to_edit = mtree.find(mem_ID_to_edit);
                if(to_edit == mtree.end())
                    std::cout << '\n' << mem_ID_to_edit << " was not a valid ID";
                else{
                    Member mem_to_edit = *to_edit;
                    mem_to_edit.setMemberInfo();
                }
                break;
            }
            case 'I':{
                //find Provider and edit their info
                int prov_ID_to_edit;
                std::cout << '\n' << "Enter the ID of the Provider to edit: ";
                std::cin >> prov_ID_to_edit;
                std::cin.ignore(MAX,'\n');
                auto to_edit = ptree.find(prov_ID_to_edit);
                if(to_edit == ptree.end())
                    std::cout << '\n' << prov_ID_to_edit << " was not a valid ID";
                else{
                    Provider prov_to_edit = *to_edit;
                    prov_to_edit.setInfo();
                }
                break;
                }
            case 'Q':
                break;
        }
    }while(response != 'Q');

    //update the Member and Provider files

    return;
}

//Provider terminal
void providerTerminal(Provider * currentProvider, std::set<Member, std::less<>> members)
{

    char response;

    do {
        std::cout << '\n' << "Enter A to check Member ID status"
        << '\n' << "Enter C to check service ID"
        << '\n' << "Enter D to view the service directory"
        << '\n' << "Enter E to provide service"
        << '\n' << "Enter F to print a provider report for the week"
        << '\n' << "Enter Q to exit terminal"
        << '\n' << "Input: ";
        std::cin >> response;
        std::cin.ignore(MAX,'\n');
        response = toupper(response);

        switch (response) {
            case 'A': {
				// check member status
				unsigned int memberID;
				
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;
                std::cin.ignore(MAX,'\n');
				
                auto member = members.find(memberID);
                if (member == mtree.end())
					std::cout << "Member ID is invalid.\n";
				else if (!(*member).getStatus())
                    std::cout << "Membership has been suspended.\n";
                else
                    std::cout << "Member ID is valid.\n";
                break;
			}
            case 'C': {
				// check if service id is valid
				unsigned int serviceID;
				
                std::cout << "Enter Service ID: ";
                std::cin >> serviceID;
                std::cin.ignore(MAX,'\n');
				
                bool serviceCheck = currentProvider->checkServiceID(serviceID);
                if (serviceCheck)
					std::cout << "Service ID " << serviceID << " is valid.\n";
                else
					std::cout << "Service ID " << serviceID << " is not valid.\n";
                break;
			}
            case 'D':{
				// print the providers service directory
                currentProvider->printServiceDirectory();
                break;
			}
            case 'E': {
				// record a service provided to a member
				unsigned int memberID;
				
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;
                std::cin.ignore(MAX,'\n');

                auto member = members.find(memberID);
                if (member == mtree.end())
                    std::cout << "Member ID is invalid.\n";
                Member to_check = *mvalid;
                if (to_check.getMemStatus() == false)
                    std::cout << "Membership has been suspended.\n";
                else
                {
                    std::cout << "Enter Service ID: ";  //implement functionality to check list of valid ID's
                    std::cin >> numres;
                    std::cin.ignore(MAX,'\n');
                    bool svalid = this_Provider->checkServiceID(numres);
                    if (svalid == false)
                        std::cout << "Service ID is not valid.\n";
                    else
                    {
                        //provide service to member
                        Service toProvide;
                        this_Provider.findService(numres,toProvide);

                        to_check.saveSession(this_Provider.saveSessionReport(to_check,toProvide,std::chrono::system_clock::now(), );
											 ++toProvide.times_used;
											 this_Provider.createSessionReport(to_check,toProvide);
											 }
					}
					break;
                }
				case 'F':{
					this_Provider->weekReport(std::cout);
					break;
                }
					case 'Q':
						return;
						break;
						default:
							std::cout << "Unknown command.";
			}
		} while(response != 'Q');
}

//login terminal that branches to Provider or manager
int main(void)
{
    std::set<Provider, std::less<>> providers;
    std::set<Member, std::less<>> members;

	// Load in provider data from the data directory
	for (auto file: std::filesystem::directory_iterator(PROVIDER_DATA_DIR)) {
		// Each providers data is in a file called info.csv in the directory named after its id
		if (file.is_directory()) {
			Provider newProvider;
			if(newProvider.loadInformation(file.path() + "/info.csv"))
				providers.insert(newProvider);
		}
	}

	// Load in member data from the data directory
	for (auto file: std::filesystem::directory_iterator(MEMBER_DATA_DIR)) {
		// Each members data is in a file called info.csv in the directory named after its id
		if (file.is_directory()) {
			Member newMember;
			if (newMember.loadInformation(file.path() + "/info.csv"))
				members.insert(newMember);
		}
	}

	// Ask which terminal they want
	char response;
	unsigned int id;
	
    std::cout << "Enter 'P' for Provider or 'M' for manager : ";
    std::cin >> response;
    response = toupper(response);

	// Make them login
    if(response == 'M') {
        std::cout << '\n' << "Enter manager ID (Default for testing is " << MANAGER_LOGIN << ") : ";
        std::cin >> id;
        std::cin.ignore(MAX,'\n');
		
        if(id == MANAGER_LOGIN)
            managerTerminal(members, providers);
    } else if(response == 'P') {
        std::cout << '\n' << "Enter Provider ID: ";
        std::cin >> id;
        std::cin.ignore(MAX,'\n');
		
        auto provider = providers.find<unsigned int>(id);
        if(provider != ptree.end()){
            // found provider in providers
            Provider found = *provider;
            providerTerminal(&found, members);
        }
    } else {
        std::cout << "Invalid command, please restart program and try again.\n";
		return -1;
	}

    return 0;
}
