#include "catch.hpp"
#include "../member.h"
#include "../defs.h"



TEST_CASE("Initialize Member")
{
	Member a_member;
	REQUIRE(a_member.getID() == 0);
	REQUIRE(a_member.getStatus() == 1);
	REQUIRE(a_member.getName() == "");
	REQUIRE(a_member.getAddress() == "");
	REQUIRE(a_member.getCity() == "");
	REQUIRE(a_member.getState() == "");
	REQUIRE(a_member.getZip() == "");
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

TEST_CASE("Test Suspended")
{
	Member members;
	REQUIRE(members.setStatus(false) == false);
}



TEST_CASE("Set Member Name Success") {
    String name = "Valid Name Length";
    Member test;
    test.setName(name);
    REQUIRE(name == test.getName());
}

TEST_CASE("Set Member Name Bounds Enforcing Success") {
    String name = "Invalid Name Length because it is too long";
    Member test;
    test.setName(name);
    REQUIRE(NAME_CHARACTERS == (test.getName()).size());
}

TEST_CASE("Get Member Name Success") {
    String name = "Valid Name";
    Member test;
    test.setName(name);
    String rn = test.getName();
    REQUIRE(rn == name);
}

TEST_CASE("Set Member Address Success") {
    String addr = "Valid addr Length";
    Member test;
    test.setAddress(addr);
    REQUIRE(addr == test.getAddress());
}

TEST_CASE("Set Member Address Bounds Enforcing Success") {
    String addr = "Invalid addr Length because it is too long";
    Member test;
    test.setAddress(addr);
    REQUIRE(ADDRESS_CHARACTERS == (test.getAddress()).size());
}

TEST_CASE("Get Member Address Success") {
    String addr = "Valid Addr";
    Member test;
    test.setAddress(addr);
    String rn = test.getAddress();
    REQUIRE(rn == addr);
}

TEST_CASE("Set Member ID Success") {
    unsigned int ID = 123456;
    Member test;
    test.setID(ID);
    REQUIRE(ID == test.getID());
}

TEST_CASE("Set Member ID Bounds Enforcing Success") {
    unsigned int ID = 12345678910;
    Member test;
    test.setID(ID);
    REQUIRE(ID == test.id);
    REQUIRE(sizeof(ID_DIGITS) == sizeof(test.getID()));
}

TEST_CASE("Get Member ID Success") {
    unsigned int ID = 123456;
    Member test;
    test.setID(ID);
    String rn = test.getID();
    REQUIRE(rn == ID);
}

TEST_CASE("Set Member City Success") {
    String city = "Valid Length";
    Member test;
    test.setCity(city);
    REQUIRE(city == test.getCity());
}

TEST_CASE("Set Member City Bounds Enforcing Success") {
    String city = "Valid Length";
    Member test;
    test.setCity(city);
    REQUIRE(CITY_CHARACTERS == (test.getCity()).size());
}

TEST_CASE("Get Member City Success") {
    String city = "Valid Length";
    Member test;
    test.setCity(city);
    String rn = test.getCity();
    REQUIRE(rn == city);
}

TEST_CASE("Set Member State Success") {
    String state = "OR";
    Member test;
    test.setState(state);
    REQUIRE(state == test.getState());
}

TEST_CASE("Set Member State Bounds Enforcing Success") {
    String city = "OR but too long";
    Member test;
    test.setState(state);
    REQUIRE(STATE_CHARACTERS == (test.getCity()).size());
}

TEST_CASE("Get Member State Success") {
    String state = "OR";
    Member test;
    test.setState(state);
    String rn = test.getState();
    REQUIRE(rn == state);
}
