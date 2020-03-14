#include "catch.hpp"

#include "../provider.h"
#include "../defs.h"
#include <string>

TEST_CASE("Set Provider Name Success") {
    std::string name = "Valid Name Length";
    Provider test;
    test.setName(name);
    REQUIRE(name == test.getName());
}

TEST_CASE("Set Provider Name Bounds Enforcing Success") {
    std::string name = "Invalid Name Length because it is too long";
    Provider test;
    test.setName(name);
    std::string rn = test.getName();
    REQUIRE(NAME_CHARACTERS == rn.size());
}

TEST_CASE("Get Provider Name Success") {
    std::string name = "Valid Name";
    Provider test;
    test.setName(name);
    std::string rn = test.getName();
    REQUIRE(rn == name);
}

TEST_CASE("Set Provider Address Success") {
    std::string addr = "Valid addr Length";
    Provider test;
    test.setAddress(addr);
    REQUIRE(addr == test.getAddress());
}

TEST_CASE("Set Provider Address Bounds Enforcing Success") {
    std::string addr = "Invalid addr Length because it is too long";
    Provider test;
    test.setAddress(addr);
    std::string rn = test.getAddress();
    REQUIRE(ADDRESS_CHARACTERS == rn.size());
}

TEST_CASE("Get Provider Address Success") {
    std::string addr = "Valid Addr";
    Provider test;
    test.setAddress(addr);
    std::string rn = test.getAddress();
    REQUIRE(rn == addr);
}

TEST_CASE("Set Provider ID Success") {
    unsigned int ID = 123456;
    Provider test;
    test.setID(ID);
    REQUIRE(ID == test.getID());
}

TEST_CASE("Set Provider ID Bounds Enforcing Success") {
    unsigned int ID = 1000000000;
    Provider test;
    test.setID(ID);
    REQUIRE(sizeof(ID_DIGITS) == sizeof(test.getID()));
}

TEST_CASE("Get Provider ID Success") {
    unsigned int ID = 123456;
    Provider test;
    test.setID(ID);
    unsigned int rn = test.getID();
    REQUIRE(rn == ID);
}

TEST_CASE("Set Provider City Success") {
    std::string city = "Valid Length";
    Provider test;
    test.setCity(city);
    REQUIRE(city == test.getCity());
}

TEST_CASE("Set Provider City Bounds Enforcing Success") {
    std::string city = "Valid Length";
    Provider test;
    test.setCity(city);
    std::string rn = test.getCity();
    REQUIRE(CITY_CHARACTERS == rn.size());
}

TEST_CASE("Get Provider City Success") {
    std::string city = "Valid Length";
    Provider test;
    test.setCity(city);
    std::string rn = test.getCity();
    REQUIRE(rn == city);
}

TEST_CASE("Set Provider State Success") {
    std::string state = "OR";
    Provider test;
    test.setState(state);
    REQUIRE(state == test.getState());
}

TEST_CASE("Set Provider State Bounds Enforcing Success") {
    std::string state = "OR but too long";
    Provider test;
    test.setState(state);
    std::string rn = test.getState();
    REQUIRE(STATE_CHARACTERS == rn.size());
}

TEST_CASE("Get Provider State Success") {
    std::string state = "OR";
    Provider test;
    test.setState(state);
    std::string rn = test.getState();
    REQUIRE(rn == state);
}
