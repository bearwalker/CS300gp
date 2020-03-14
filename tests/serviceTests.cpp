#include "catch.hpp"
#include "../services.h"


TEST_CASE("Services set ID Success") {
    Service testServ;
    unsigned int testID = "123456";
    testServ.ID = testID;
	REQUIRE(testServ.ID == testID);

}

TEST_CASE("Services set Name Success") {
    Service testServ;
    String testName = "Blood Test";
    testServ.name = testName;
	REQUIRE(testServ.name == testName);
}

TEST_CASE("Services set Name Overflow") {
    Service testServ;
    String testName = "Blood Testing longer than 20 chars";
    testServ.name = testName;
	REQUIRE(strlen(testServ.name) > strlen(testName));
}

TEST_CASE("Services set Price Success") {
    Service testServ;
    float testPrice = "123.99";
    testServ.price = testPrice;
	REQUIRE(testServ.price == testPrice);
}

TEST_CASE("Services set Price Overflow") {
    Service testServ;
    float testPrice = "112312323.99214123421342134234";
    testServ.price = testPrice;
	REQUIRE(testServ.price != testPrice);
}

TEST_CASE("Services ID catch non-int") {
    Service testServ;
    int testID = "applebees";
    testServ.ID = testID;
	REQUIRE(testServ.ID != testID);
}
