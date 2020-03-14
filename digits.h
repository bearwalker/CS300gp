#pragma once

/*
  Returns the number of digits in the given number (in base 10)

  @param the number to count the digits of

  @return the number of base 10 in the given number
*/
unsigned int numDigits(unsigned int number);
unsigned int numDigits(int number);

/*
  Resizes a number to the desired number of digits by 
  - cutting off digits starting in the ones place and increasing if there are too many digits
  - padding number with 0s starting in the ones place if there aren't enough digits
  - doing nothing if there are enough digits

  @param number - the number to resize
  @param desiredDigitCount - the number of digits to resize number to

  @return the resized number
*/
unsigned int resizeNumber(unsigned int number, unsigned int desiredDigitCount);
int resizeNumber(int number, unsigned int desiredDigitCount);

/*
  Shrinks a number by the given number of digits starting in the ones place

  @param number - the number to shrink
  @param numDigitsToRemove - the number of digits to remove from the number

  @return the shrunk number
*/
unsigned int shrinkNumber(unsigned int number, unsigned int numDigitsToRemove);
int shrinkNumber(int number, unsigned int numDigitsToRemove);

/*
  Pads a number by the given number of digits with 0s starting in the ones place

  @param number - the number to pad
  @param numDigitsToAdd - the number of digits to add to the number

  @return the padded number
*/
unsigned int padNumber(unsigned int number, unsigned int numDigitsToAdd);
int padNumber(int number, unsigned int numDigitsToAdd);
