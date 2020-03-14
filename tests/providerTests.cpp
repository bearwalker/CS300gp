#include "catch.hpp"

#include "../provider.h"
#include <string>

TEST_CASE("Set Provider Name Success") {
    String name = "Valid Name Length";
    Provider test;
    test.setName(name);
    REQUIRE(name == test.getName());
}

TEST_CASE("Set Provider Name Bounds Enforcing Success") {
    String name = "Invalid Name Length because it is too long";
    Provider test;
    test.setName(name);
    REQUIRE(NAME_CHARACTERS == (test.getName()).size());
}

TEST_CASE("Get Provider Name Success") {
    String name = "Valid Name";
    Provider test;
    test.setName(name);
    String rn = test.getName();
    REQUIRE(rn == name);
}

TEST_CASE("Set Provider Address Success") {
    String addr = "Valid addr Length";
    Provider test;
    test.setAddress(addr);
    REQUIRE(addr == test.getAddress());
}

TEST_CASE("Set Provider Address Bounds Enforcing Success") {
    String addr = "Invalid addr Length because it is too long";
    Provider test;
    test.setAddress(addr);
    REQUIRE(ADDRESS_CHARACTERS == (test.getAddress()).size());
}

TEST_CASE("Get Provider Address Success") {
    String addr = "Valid Addr";
    Provider test;
    test.setAddress(addr);
    String rn = test.getAddress();
    REQUIRE(rn == addr);
}

TEST_CASE("Set Provider ID Success") {
    unsigned int ID = 123456;
    Provider test;
    test.setID(ID);
    REQUIRE(ID == test.getID());
}

TEST_CASE("Set Provider ID Bounds Enforcing Success") {
    unsigned int ID = 12345678910;
    Provider test;
    test.setID(ID);
    REQUIRE(ID == test.id);
    REQUIRE(sizeof(ID_DIGITS) == sizeof(test.getID()));
}

TEST_CASE("Get Provider ID Success") {
    unsigned int ID = 123456;
    Provider test;
    test.setID(ID);
    String rn = test.getID();
    REQUIRE(rn == ID);
}

TEST_CASE("Set Provider City Success") {
    String city = "Valid Length";
    Provider test;
    test.setCity(city);
    REQUIRE(city == test.getCity());
}

TEST_CASE("Set Provider City Bounds Enforcing Success") {
    String city = "Valid Length";
    Provider test;
    test.setCity(city);
    REQUIRE(CITY_CHARACTERS == (test.getCity()).size());
}

TEST_CASE("Get Provider City Success") {
    String city = "Valid Length";
    Provider test;
    test.setCity(city);
    String rn = test.getCity();
    REQUIRE(rn == city);
}

TEST_CASE("Set Provider State Success") {
    String state = "OR";
    Provider test;
    test.setState(state);
    REQUIRE(state == test.getState());
}

TEST_CASE("Set Provider State Bounds Enforcing Success") {
    String city = "OR but too long";
    Provider test;
    test.setState(state);
    REQUIRE(STATE_CHARACTERS == (test.getCity()).size());
}

TEST_CASE("Get Provider State Success") {
    String state = "OR";
    Provider test;
    test.setState(state);
    String rn = test.getState();
    REQUIRE(rn == state);
}
