#include "catch.hpp"
#include "../service.h"
#include "../defs.h"


TEST_CASE("Set Service Name Success") {
    String name = "Valid Name Length";
    Service test;
    test.setName(name);
    REQUIRE(name == test.getName());
}

TEST_CASE("Set Service Name Bounds Enforcing Success") {
    String name = "Invalid Name Length because it is too long";
    Service test;
    test.setName(name);
    REQUIRE(NAME_CHARACTERS == (test.getName()).size());
}

TEST_CASE("Get Service Name Success") {
    String name = "Valid Name";
    Service test;
    test.setName(name);
    String rn = test.getName();
    REQUIRE(rn == name);
}

TEST_CASE("Set Service Price Success") {
    double price = "12.99";
    Service test;
    test.setPrice(price);
    REQUIRE(price == test.getPrice());
}

TEST_CASE("Set Service Price Bounds Enforcing Success") {
    double price = "123124124214.1422222222222";
    Service test;
    test.setPrice(price);
    REQUIRE(priceESS_CHARACTERS == (test.getPrice()).size());
}

TEST_CASE("Get Service Price Success") {
    double price = "12.99";
    Service test;
    test.setPrice(price);
    String rn = test.getPrice();
    REQUIRE(rn == price);
}

TEST_CASE("Set Service ID Success") {
    unsigned int ID = 123456;
    Service test;
    test.setID(ID);
    REQUIRE(ID == test.getID());
}

TEST_CASE("Set Service ID Bounds Enforcing Success") {
    unsigned int ID = 12345678910;
    Service test;
    test.setID(ID);
    REQUIRE(ID == test.id);
    REQUIRE(sizeof(ID_DIGITS) == sizeof(test.getID()));
}

TEST_CASE("Get Service ID Success") {
    unsigned int ID = 123456;
    Service test;
    test.setID(ID);
    String rn = test.getID();
    REQUIRE(rn == price);
}
