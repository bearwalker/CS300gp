//Member class

#include <string>
using namespace std;

class Member
{
	public:
		void printMemberInfo();
		void setMemberInfo();
		void getMemberInfo(Member);
		void addService(Service);

	private:
		int ID_number;
		string Mem_status;
		string name;
		string address;
		string city;
		string state;
		int zip;
		Service Used;
};
