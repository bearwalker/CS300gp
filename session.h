#pragma once

#include <chrono>
#include <string>

#include "service.h"

class Session
{
public:
	// Construct with empty values
	Session();

	/*
	  Try to construct the class with data from a csv file, otherwise use empty values.
	  A session csv file should be formatted as id of member provided to,name of member provided to,id of service provided,date provided MM-DD-YYYY,time recorded MM-DD-YYYY HH:MM:SS,comments;
	  
	  @param informationFile - path to a csv file containing provider info
	*/
	Session(std::string informationFile);

	/*
	  Load information about a session from a csv file in the format
	  id of member provided to,name of member provided to,id of service provided,date provided MM-DD-YYYY,time recorded MM-DD-YYYY HH:MM:SS,comments;

	  @param informationFile - the path to the file to load from

	  @return true on success, false on failure
	*/
	bool loadInformation(std::string informationFile);

	/*
	  Saves information about the session in the same format as loaded from

	  @param filePath - the path of the file to save to
	*/
	bool saveRecord(std::string filePath);

	/*
	  Setter for serviceProvided

	  @param service - the service that was provided
	*/
	void setServiceProvided(Service service);

	/*
	  setter for memberName

	  @param name - the name of the member the service was provided to
	*/
	void setMemberName(std::string name);

	/*
	  Setter for memberID

	  @param id - the id of the member the service was provided to
	*/
	void setMemberID(unsigned int id);
	
	/*
	  Setter for providerName

	  @param name - the name of the provider that provided the service
	*/
	void setProviderName(std::string name);

	/*
	  Setter for dateProvided

	  @param date - the date the service was provided
	*/
	void setDateProvided(std::chrono::system_clock::time_point date);

	/*
	  Setter for timeRecorded

	  @param time - the time the service was recorded
	*/
	void setTimeRecorded(std::chrono::system_clock::time_point time);

	/*
	  Setter for the comments, cuts comments down to first 100 characters

	  @param newComments - the comments about the service provided
	*/
	void setComments(std::string newComments);

	/*
	  Getter for serviceProvided

	  @return a service struct of the service provided
	*/
	Service getServiceProvided() const;

	/*
	  Getter for memberName

	  @return name of the member the service was provided to
	*/
	std::string getMemberName() const;

	/*
	  Getter for memberID

	  @return the id of the member the service was provided to
	*/
	unsigned int getMemberID() const;

	/*
	  Getter for providerName

	  @return name of the provider that provided the service
	*/
	std::string getProviderName() const;
	
	/*
	  Getter for dateProvided

	  @return a time_point of the date provided
	*/
	std::chrono::system_clock::time_point getDateProvided() const;

	/*
	  Getter for timeRecorded

	  @return a time_poinnt of the time the session was recorded
	*/
	std::chrono::system_clock::time_point getTimeRecorded() const;

	/*
	  Getter foor comments

	  @return a string containing the comments on the session
	*/
	std::string getComments() const;

private:
	Service serviceProvided;
	std::string memberName;
	unsigned int memberID;
	std::string providerName;
	std::chrono::system_clock::time_point dateProvided;
	std::chrono::system_clock::time_point timeRecorded;
	std::string comments;
};
