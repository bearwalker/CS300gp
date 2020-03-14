#include "catch.hpp"
#include "../member.h"
#include "../defs.h"
#include <string>



TEST_CASE("Initialize Member")
{
	Member a_member;
	REQUIRE(a_member.getID() == 0);
	REQUIRE(a_member.getStatus() == 1);
	REQUIRE(a_member.getName() == "");
	REQUIRE(a_member.getAddress() == "");
	REQUIRE(a_member.getCity() == "");
	REQUIRE(a_member.getState() == "");
	REQUIRE(a_member.getZip() == 0);
}

TEST_CASE("Test Active")
{
	Member members;
	REQUIRE(members.getStatus() == true);
}

TEST_CASE("Test Suspended")
{
	Member members;
    members.setStatus(false);
	REQUIRE(members.getStatus() == false);
}



TEST_CASE("Set Member Name Success") {
    std::string name = "Valid Name Length";
    Member test;
    test.setName(name);
    REQUIRE(name == test.getName());
}

TEST_CASE("Set Member Name Bounds Enforcing Success") {
    std::string name = "Invalid Name Length because it is too long";
    Member test;
    test.setName(name);
    std::string rn = test.getName();
    REQUIRE(NAME_CHARACTERS == rn.size());
}

TEST_CASE("Get Member Name Success") {
    std::string name = "Valid Name";
    Member test;
    test.setName(name);
    std::string rn = test.getName();
    REQUIRE(rn == name);
}

TEST_CASE("Set Member Address Success") {
    std::string addr = "Valid addr Length";
    Member test;
    test.setAddress(addr);
    REQUIRE(addr == test.getAddress());
}

TEST_CASE("Set Member Address Bounds Enforcing Success") {
    std::string addr = "Invalid addr Length because it is too long";
    Member test;
    test.setAddress(addr);
    std::string rn = test.getAddress();
    REQUIRE(ADDRESS_CHARACTERS == rn.size());
}

TEST_CASE("Get Member Address Success") {
    std::string addr = "Valid Addr";
    Member test;
    test.setAddress(addr);
    std::string rn = test.getAddress();
    REQUIRE(rn == addr);
}

TEST_CASE("Set Member ID Success") {
    unsigned int ID = 123456;
    Member test;
    test.setID(ID);
    REQUIRE(ID == test.getID());
}

TEST_CASE("Set Member ID Bounds Enforcing Success") {
    unsigned int ID = 1000000000;
    Member test;
    test.setID(ID);
    REQUIRE(sizeof(ID_DIGITS) == sizeof(test.getID()));
}

TEST_CASE("Get Member ID Success") {
    unsigned int ID = 123456;
    Member test;
    test.setID(ID);
    unsigned int rn = test.getID();
    REQUIRE(rn == ID);
}

TEST_CASE("Set Member City Success") {
    std::string city = "Valid Length";
    Member test;
    test.setCity(city);
    REQUIRE(city == test.getCity());
}

TEST_CASE("Set Member City Bounds Enforcing Success") {
    std::string city = "Valid Length";
    Member test;
    test.setCity(city);
    std::string rn = test.getCity();
    REQUIRE(CITY_CHARACTERS == rn.size());
}

TEST_CASE("Get Member City Success") {
    std::string city = "Valid Length";
    Member test;
    test.setCity(city);
    std::string rn = test.getCity();
    REQUIRE(rn == city);
}

TEST_CASE("Set Member State Success") {
    std::string state = "OR";
    Member test;
    test.setState(state);
    REQUIRE(state == test.getState());
}

TEST_CASE("Set Member State Bounds Enforcing Success") {
    std::string state = "OR but too long";
    Member test;
    test.setState(state);
    std::string rn = test.getState();
    REQUIRE(STATE_CHARACTERS == rn.size());
}

TEST_CASE("Get Member State Success") {
    std::string state = "OR";
    Member test;
    test.setState(state);
    std::string rn = test.getState();
    REQUIRE(rn == state);
}
