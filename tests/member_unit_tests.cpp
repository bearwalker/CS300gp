#define CONFIG_CATCH_MAIN
#include "catch.hpp"
#include "../defs.h"



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

