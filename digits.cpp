#include <cmath>

#include "digits.h"

unsigned int numDigits(unsigned int number)
{
	// Log_10(0) = infinity so not a good idea
	if (number == 0)
		return 1;

	// Log_10 of a number gives its number of digits - 1 (with some decimals)
	return static_cast<unsigned int>(std::floor(std::log10(number))) + 1;
}

unsigned int numDigits(int number)
{
	// Log_10(0) = infinity so not a good idea
	if (number == 0)
		return 1;

	// Negative arguments to log10() return NaN according to standard
	if (number < 0)
		number = std::abs(number);

	// Log_10 of a number gives its number of digits - 1 (with some decimals)
	return static_cast<unsigned int>(std::floor(std::log10(number))) + 1;
}

unsigned int resizeNumber(unsigned int number, unsigned int desiredDigitCount)
{
	unsigned int currentDigitCount = numDigits(number);
	
	if (currentDigitCount > desiredDigitCount)
		return shrinkNumber(number, currentDigitCount - desiredDigitCount);
	else if (currentDigitCount < desiredDigitCount)
		return padNumber(number, desiredDigitCount - currentDigitCount);
	else
		return number;
}
			
int resizeNumber(int number, unsigned int desiredDigitCount)
{
	unsigned int currentDigitCount = numDigits(number);
	
	if (currentDigitCount > desiredDigitCount)
		return shrinkNumber(number, currentDigitCount - desiredDigitCount);
	else if (currentDigitCount < desiredDigitCount)
		return padNumber(number, desiredDigitCount - currentDigitCount);
	else
		return number;
}

unsigned int shrinkNumber(unsigned int number, unsigned int numDigitsToRemove)
{
	for (unsigned int digitsRemoved = 0; digitsRemoved < numDigitsToRemove; digitsRemoved++)
		number /= 10;

	return number;
}

int shrinkNumber(int number, unsigned int numDigitsToRemove)
{
	for (unsigned int digitsRemoved = 0; digitsRemoved < numDigitsToRemove; digitsRemoved++)
		number /= 10;

	return number;
}

unsigned int padNumber(unsigned int number, unsigned int numDigitsToAdd)
{
	for (unsigned int digitsAdded = 0; digitsAdded < numDigitsToAdd; digitsAdded++)
		number *= 10;

	return number;
}

int padNumber(int number, unsigned int numDigitsToAdd)
{
	for (unsigned int digitsAdded = 0; digitsAdded < numDigitsToAdd; digitsAdded++)
		number *= 10;

	return number;
}
