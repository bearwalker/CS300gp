#pragma once

#include <string>

class Service
{
public:
	// Construct with empty values
	Service();

	/*
	  Try to construct the class with information about a service from a csv file, otherwise use empty values
	  The csv file format is:
	  id,name,price;

	  @param informationFile - path to a csv file containing Service info
	*/
	Service(std::string informationFile);

	/*
	  Load information about a service from a csv file in the format
	  id,name,price;

	  @param informationFile - the path to the file to load from

	  @return true on success, false on failure
	*/
	bool loadInformation(std::string informationFile);

	/*
	  Setter for id

	  @param newID - the number to set as id, will be resized to SERVICE_ID_DIGITS
	*/
	void setID(unsigned int newID);

	/*
	  Setter for name

	  @param newName - the string to set as the name, will be resized to SERVICE_NAME_CHARACTERS as needed
	*/
	void setName(std::string newName);

	/*
	  Setter for price

	  @param newPrice - the price to set as price, will be set to SERVICE_PRICE_MAX if too large
	*/
	void setPrice(double newPrice);

	/*
	  Getter for id

	  @return the services id code
	*/
	unsigned int getID() const;

	/*
	  Getter for name

	  @return the services name
	*/
	std::string getName() const;

	/*
	  Getter for price

	  @return the services price
	*/
	double getPrice() const;

	// Functions for comparing services and unsigned itns based on ids value
	friend bool operator<(const Service& leftSide, const Service& rightSide);
	friend bool operator<(const unsigned int& leftSide, const Service& rightSide);
	friend bool operator<(const Service& leftSide, const unsigned int& rightSide);

    void displayInfo(); //Display service info

private:
    unsigned int id;
    std::string name;
    double price;
};
