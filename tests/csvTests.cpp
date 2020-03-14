#include "catch.hpp"

#include "../csvParser.h"

TEST_CASE("Testing parsing a good file", "[csvParser]") {
	std::vector<std::tuple<int, unsigned int, float, double, std::string>> contents;
	std::string file = "tests/testData/good.csv";

	bool result = parseFile<int, unsigned int, float, double, std::string>(file, contents);

	REQUIRE(result);
	REQUIRE(std::get<0>(contents.at(0)) == -1);
	REQUIRE(std::get<1>(contents.at(0)) == 1);
	REQUIRE(std::get<2>(contents.at(0)) == 1.5);
	REQUIRE(std::get<3>(contents.at(0)) == 2.5);
	REQUIRE(std::get<4>(contents.at(0)) == "hello");
	REQUIRE(std::get<5>(contents.at(0)) == true);
	REQUIRE(std::get<0>(contents.at(1)) == -2);
	REQUIRE(std::get<1>(contents.at(1)) == 2);
	REQUIRE(std::get<2>(contents.at(1)) == 2.5);
	REQUIRE(std::get<3>(contents.at(1)) == 3.5);
	REQUIRE(std::get<4>(contents.at(1)) == "hi");
	REQUIRE(std::get<5>(contents..at(1)) == false);
}

TEST_CASE("Tests csvParser on a bad file", "[csvParser]") {
	std::vector<std::tuple<int, unsigned int, float, double, std::string>> contents;
	std::string file = "tests/testData/bad.csv";

	bool result = parseFile<int, unsigned int, float, double, std::string>(file, contents);

	REQUIRE(result == false);
}


