#include "catch.hpp"

#include "../defs.h"

TEST_CASE("Testing that numDigits returns correct values for unsigned ints", "[digits]")
{
	unsigned int oneDigit = 1;
	unsigned int twoDigits = 12;
	unsigned int threeDigits = 123;
	unsigned int fourDigits = 1234;
	unsigned int fiveDigits = 12345;
	unsigned int tenDigits = 1234567890;

	REQUIRE(numDigits(oneDigit) == 1);
	REQUIRE(numDigits(twoDigits) == 2);
	REQUIRE(numDigits(threeDigits) == 3);
	REQUIRE(numDigits(fourDigits) == 4);
	REQUIRE(numDigits(fiveDigits) == 5);
	REQUIRE(numDigits(tenDigits) == 10);
}

TEST_CASE("Testing that numDigits returns correct values for (signed) ints", "[digits]")
{
	int oneDigit = 1;
	int twoDigits = 12;
	int threeDigits = 123;
	int fourDigits = 1234;
	int fiveDigits = 12345;
	int tenDigits = 1234567890;

	REQUIRE(numDigits(oneDigit) == 1);
	REQUIRE(numDigits(twoDigits) == 2);
	REQUIRE(numDigits(threeDigits) == 3);
	REQUIRE(numDigits(fourDigits) == 4);
	REQUIRE(numDigits(fiveDigits) == 5);
	REQUIRE(numDigits(tenDigits) == 10);
}

TEST_CASE("Testing that numDigits returns correct values for negative ints", "[digits]")
{
	int oneDigit = -1;
	int twoDigits = -12;
	int threeDigits = -123;
	int fourDigits = -1234;
	int fiveDigits = -12345;
	int tenDigits = -1234567890;

	REQUIRE(numDigits(oneDigit) == 1);
	REQUIRE(numDigits(twoDigits) == 2);
	REQUIRE(numDigits(threeDigits) == 3);
	REQUIRE(numDigits(fourDigits) == 4);
	REQUIRE(numDigits(fiveDigits) == 5);
	REQUIRE(numDigits(tenDigits) == 10);
}

TEST_CASE("Testing that numDigits handles 0 correctly", "[digits]")
{
	unsigned int unsignedZero = 0;
	int signedZero = 0;

	REQUIRE(numDigits(unsignedZero) == 1);
	REQUIRE(numDigits(signedZero) == 1);
}

TEST_CASE("Testing that shrinkNumber shrinks numbers correctly", "[digits]")
{
	unsigned int number1 = 1234;
	int number2 = 11115555;
	int number3 = -1234;

	REQUIRE(shrinkNumber(number1, 2) == 12);
	REQUIRE(shrinkNumber(number2, 4) == 1111);
	REQUIRE(shrinkNumber(number3, 2) == -12);
}

TEST_CASE("Testing that padNumber pads numbers correctly", "[digits]")
{
	unsigned int number1 = 68;
	int number2 = 36048; // random number courtesy of slamming my hand on the numpad
	int number3 = -5678;

	REQUIRE(padNumber(number1, 2) == 6800);
	REQUIRE(padNumber(number2, 4) == 360480000);
	REQUIRE(padNumber(number3, 1) == -56780);
}

TEST_CASE("Testing that resizeNumber doesn't modify correctly sized numbers", "[digits]")
{
	unsigned int sixDigits = 685493;
	int fourDigits = 3261;
	int sevenDigits = -5628411;

	REQUIRE(resizeNumber(sixDigits, 6) == sixDigits);
	REQUIRE(resizeNumber(fourDigits, 4) == fourDigits);
	REQUIRE(resizeNumber(sevenDigits, 7) == sevenDigits);
}
