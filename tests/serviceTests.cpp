#include "catch.hpp"
#include "../service.h"


TEST_CASE("Services set ID Success") {
    Service testServ;
    //implement setID() for testing/sizing?
    unsigned int testID = "123456";
    testServ.ID = testID;
	REQUIRE(testServ.ID == testID);

}

TEST_CASE("Services set Name Success") {
    Service testServ;
    String testName = "Blood Test";
    //implement setName() for testing/sizing?
    testServ.name = testName;
	REQUIRE(testServ.name == testName);
}

TEST_CASE("Services set Name Overflow") {
    Service testServ;
    String testName = "Blood Testing longer than 20 chars";
    //implement setName() for testing/sizing?
    testServ.name = testName;
	REQUIRE(strlen(testServ.name) > strlen(testName));
}

TEST_CASE("Services set Price Success") {
    Service testServ;
    float testPrice = "123.99";
    //implement setPrice() for testing/sizing?
    testServ.price = testPrice;
	REQUIRE(testServ.price == testPrice);
}

TEST_CASE("Services set Price Overflow") {
    Service testServ;
    float testPrice = "112312323.99214123421342134234";
    //implement setPrice() for testing/sizing?
    testServ.price = testPrice;
	REQUIRE(testServ.price != testPrice);
}

TEST_CASE("Services ID catch non-int") {
    Service testServ;
    int testID = "applebees";
    //implement setID() for testing/sizing?
    testServ.ID = testID;
	REQUIRE(testServ.ID != testID);
}
