#include <iostream>

#include "/usr/local/include/gtest/gtest.h"

#include "../csvParser.h"

TEST(CsvTests, GoodFile) {
	std::vector<std::tuple<int, unsigned int, float, double, std::string>> contents;
	std::string file = "good.csv";

	bool result = parseFile<int, unsigned int, float, double, std::string>(contents, file);

	ASSERT_TRUE(result);
	ASSERT_EQ(std::get<0>(contents.at(0)), -1);
	ASSERT_EQ(std::get<1>(contents.at(0)), 1);
	ASSERT_EQ(std::get<2>(contents.at(0)), 1.5);
	ASSERT_EQ(std::get<3>(contents.at(0)), 2.5);
	ASSERT_EQ(std::get<4>(contents.at(0)), "hello");
	ASSERT_EQ(std::get<0>(contents.at(1)), -2);
	ASSERT_EQ(std::get<1>(contents.at(1)), 2);
	ASSERT_EQ(std::get<2>(contents.at(1)), 2.5);
	ASSERT_EQ(std::get<3>(contents.at(1)), 3.5);
	ASSERT_EQ(std::get<4>(contents.at(1)), "hi");

}

TEST(CsvTests, BadFile) {
	std::vector<std::tuple<int, unsigned int, float, double, std::string>> contents;
	std::string file = "bad.csv";

	bool result = parseFile<int, unsigned int, float, double, std::string>(contents, file);

	ASSERT_FALSE(result);
}
