#include "defs.h"
#include "provider.h"

Provider(std::string informationFile);
bool checkServiceID(unsigned int serviceId);
void printServiceList();
void createSessionReport(Member member, Service service, std::chrono::time_point time);
void summaryReport();
