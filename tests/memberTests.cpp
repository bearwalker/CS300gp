#include "catch.hpp"
#include "../member.h"



TEST_CASE("Initialize Member")
{
	Member a_member;
	REQUIRE(a_member.ID_number == 0);
	REQUIRE(a_member.Mem_status == 1);
	REQUIRE(a_member.name == "");
	REQUIRE(a_member.address == "");
	REQUIRE(a_member.city == "");
	REQUIRE(a_member.state == "");
	REQUIRE(a_member.zip == "");
}


TEST_CASE("Testing print member info")
{
	Member members;
	REQUIRE(members.printMemberInfo() == true);

}

TEST_CASE("Test Active")
{
	Member members;
	REQUIRE(members.getMemStatus() == true);
}

TEST_CASE("Test Inactive")
{
	Member members;
	members.memberInactive();
	REQUIRE(members.getMemStatus() == false);
}

TEST_CASE("Add a Service")
{
	Member members;
	Service used;
	REQUIRE(members.addService(used) == 1 || members.addService(used) == 2);

}

TEST_CASE("Test print service")
{
	Member members;
	REQUIRE(members,printMemServices() == true);
}
