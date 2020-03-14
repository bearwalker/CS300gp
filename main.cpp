//Implementation of the login,Provider, and man terminals

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#ifdef GCC_OLD
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#include "defs.h"
#include "member.h"
#include "provider.h"
#include "session.h"
#include "service.h"

//Manager terminal
void managerTerminal(std::set<Member, std::less<>> members, std::set<Provider, std::less<>> providers)
{

    char response;
    do {
        std::cout << '\n' << "Enter M to print and generate Member reports"
        << '\n' << "Enter P to print Manager report"
        << '\n' << "Enter Q to exit the manager terminal"
        << '\n' << "Input: ";
        std::cin >> response;
        std::cin.ignore(MAX,'\n');
        response = toupper(response);

        switch (response) {
            case 'M': {
				// print and generate member reports
				// convert current date to a string
				std::time_t currentDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				std::ostringstream dateString;
				dateString << std::put_time(std::localtime(&currentDate), "%m-%d-%Y");

                //print and save reports for all Members
                for(auto member = members.begin(); member != members.end(); member++)
                {

					(*member).printWeekReport();

					std::string reportPath = REPORT_DATA_DIR + (*member).getName() + "_" + dateString.str() + "_report.csv";
					(*member).saveWeekReport(reportPath);
                }
                break;
            }
            case 'G': {
                //print the manager report
                double totalFee = 0;
                unsigned int totalProvided = 0;

                for(auto provider = providers.begin(); provider != providers.end(); provider++)
                {
                    unsigned int servicesProvided = (*provider).providedServices();

                    if(servicesProvided > 0){

                        std::cout << '\n' << "Provider: " << (*provider).getName() << " provided " << servicesProvided << " this week" << '\n';

						totalFee += (*provider).weekFeeTotal();
						totalProvided++;
                    }
                }
                std::cout << '\n' << "Total Providers for week: " << totalProvided;
                std::cout << '\n' << "Overall Fee Total: " << totalFee;
                break;
            }
            case 'Q':
                break;
        }
    } while(response != 'Q');
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
                if (member == members.end())
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
                if (member == members.end()) {
                    std::cout << "Member ID is invalid.\n";
					break;
				}

				if ((*member).getStatus() == false) {
                    std::cout << "Membership has been suspended.\n";
					break;
				}

				// Enter date of service
				std::string dateString;
				std::cout << "Please enter the date the service was provided (MM-DD-YYYY): ";
				std::cin >> dateString;
				std::cin.ignore(MAX,'\n');

				// convert to time_point
				std::tm dateTm;
				std::istringstream dateStream(dateString);
				std::string yearString;
				std::string monthString;
				std::string dayString;

				std::getline(dateStream, monthString, '-');
				std::getline(dateStream, dayString, '-');
				std::getline(dateStream, yearString);

				try {
					// tm stores years since 1900
					dateTm.tm_year = std::stoi(yearString) - 1900;
					// months since january
					dateTm.tm_mon = std::stoi(monthString) - 1;
					dateTm.tm_mday = std::stoi(dayString);
				} catch (...) {
					std::cout << "Invalid date" << std::endl;
					break;
				}

				std::chrono::system_clock::time_point date = std::chrono::system_clock::from_time_t(std::mktime(&dateTm));

				// print service directory
				std::cout << "Printing service directory, please find the service you are recording" << std::endl;
				currentProvider->printServiceDirectory();

				// ask for service id
				unsigned int serviceID;
				std::cout << "Enter Service ID: ";
				std::cin >> serviceID;
				std::cin.ignore(MAX,'\n');

				if (!currentProvider->checkServiceID(serviceID)) {
					std::cout << "Service ID not valid.\n";
					break;
				}

				// verify service
				char verifyServiceChoice;
				std::cout << "Is this the correct service? Y/N: ";
				std::cin >> verifyServiceChoice;
				std::cin.ignore(MAX,'\n');

				if (toupper(verifyServiceChoice == 'N')) {
					std::cout << "Please start again\n";
					break;
				}

				// Add comments optionally
				std::string comments = "";
				char commentChoice;
				std::cout << "Would you like to add additional comments? Y/N: ";
				std::cin >> commentChoice;
				std::cin.ignore(MAX,'\n');


				if (toupper(commentChoice) == 'Y') {
					std::cout << "Comments (100 characters max): ";
					std::getline(std::cin, comments);
				}

				// Record the session
				Service toProvide;
				currentProvider->findService(serviceID, toProvide);
				Session newSession = currentProvider->saveSessionReport(*member, toProvide, date, comments);

				// Save to member by removing from set then readding
				Member tempMember = *member;
				members.erase(member);
				tempMember.saveSession(newSession);
				members.insert(tempMember);
				break;
			}
			case 'F':{
				currentProvider->printWeekReport();

				// convert current date to a string
				std::time_t currentDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				std::ostringstream dateString;
				dateString << std::put_time(std::localtime(&currentDate), "%m-%d-%Y");

				std::string reportPath = REPORT_DATA_DIR + currentProvider->getName() + "_" + dateString.str() + "_report.csv";
				currentProvider->saveWeekReport(reportPath);
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
	for (auto file: fs::directory_iterator(PROVIDER_DATA_DIR)) {
		// Each providers data is in a file called info.csv in the directory named after its id
		if (file.status().type() == fs::file_type::directory) {
			Provider newProvider;
			if(newProvider.loadInformation(static_cast<std::string>(file.path()) + "/info.csv"))
				providers.insert(newProvider);
		}
	}

	// Load in member data from the data directory
	for (auto file: fs::directory_iterator(MEMBER_DATA_DIR)) {
		// Each members data is in a file called info.csv in the directory named after its id
		if (file.status().type() == fs::file_type::directory) {
			Member newMember;
			if (newMember.loadInformation(static_cast<std::string>(file.path()) + "/info.csv"))
				members.insert(newMember);
		}
	}

	// Ask which terminal they want
	char response;
	unsigned int id;

    std::cout << "Enter 'P' for Provider or 'M' for manager : ";
    std::cin >> response;
	std::cin.ignore(MAX,'\n');
    response = toupper(response);

	// Make them login
    if(response == 'M') {
        std::cout << '\n' << "Enter manager ID (Default for testing is " << MANAGER_LOGIN << ") : ";
        std::cin >> id;
        std::cin.ignore(MAX,'\n');

        if(id == MANAGER_LOGIN)
            managerTerminal(members, providers);
    } else if(response == 'P') {
        std::cout << '\n' << "Enter Provider ID (Default for testing is 100000000): ";
        std::cin >> id;
        std::cin.ignore(MAX,'\n');

        auto provider = providers.find<unsigned int>(id);
        if(provider != providers.end()){
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
