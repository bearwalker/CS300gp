#include "catch.hpp"
#include "../service.h"
#include "../defs.h"
#include <string>


TEST_CASE("Set Service Name Success") {
    std::string name = "Valid Name Length";
    Service test;
    test.setName(name);
    REQUIRE(name == test.getName());
}

TEST_CASE("Set Service Name Bounds Enforcing Success") {
    std::string name = "Invalid Name Length because it is too long";
    Service test;
    test.setName(name);
    std::string rn = test.getName();
    REQUIRE(NAME_CHARACTERS == rn.size());
}

TEST_CASE("Get Service Name Success") {
    std::string name = "Valid Name";
    Service test;
    test.setName(name);
    std::string rn = test.getName();
    REQUIRE(rn == name);
}

TEST_CASE("Set Service Price Success") {
    double price = 12.99;
    Service test;
    test.setPrice(price);
    REQUIRE(price == test.getPrice());
}

TEST_CASE("Set Service Price Bounds Enforcing Success") {
    double price = 123124124214.1422222222222;
    Service test;
    test.setPrice(price);
    REQUIRE(sizeof(SERVICE_PRICE_MAX) == sizeof(test.getPrice()));
}

TEST_CASE("Get Service Price Success") {
    double price = 12.99;
    Service test;
    test.setPrice(price);
    double rn = test.getPrice();
    REQUIRE(rn == price);
}

TEST_CASE("Set Service ID Success") {
    unsigned int ID = 123456;
    Service test;
    test.setID(ID);
    REQUIRE(ID == test.getID());
}

TEST_CASE("Set Service ID Bounds Enforcing Success") {
    unsigned int ID = 1000000000;
    Service test;
    test.setID(ID);
    REQUIRE(sizeof(ID_DIGITS) == sizeof(test.getID()));
}

TEST_CASE("Get Service ID Success") {
    unsigned int ID = 123456;
    Service test;
    test.setID(ID);
    unsigned int rn = test.getID();
    REQUIRE(rn == ID);
}
