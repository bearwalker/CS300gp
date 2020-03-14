// Constants common amont almost all classes
#pragma once

#include <string>

//constants for cin
const int CHARMAX = 20; //max for any std::string readin?
const int INTMAX = 6; //max for num read in such as ids
const int MAX = 256; //for ignores

// Private data length constraints
const unsigned int ID_DIGITS = 9;
const unsigned int NAME_CHARACTERS = 25;
const unsigned int ADDRESS_CHARACTERS = 25;
const unsigned int CITY_CHARACTERS = 14;
const unsigned int STATE_CHARACTERS = 2;
const unsigned int ZIP_DIGITS = 5;
const unsigned int COMMENT_CHARACTERS = 100;

// Services have different length constraints
const unsigned int SERVICE_ID_DIGITS = 6;
const unsigned int SERVICE_NAME_CHARACTERS = 20;
const double SERVICE_PRICE_MAX = 999.99;

// Data directories
const std::string EFT_DATA_DIR = "data/eft/";
const std::string REPORT_DATA_DIR = "data/reports/";
const std::string PROVIDER_DATA_DIR = "data/providers/";
const std::string MEMBER_DATA_DIR = "data/members/";
const std::string SERVICE_DATA_DIR = "data/services/";
// each PROVIDER_DATA_DIR will contain a SESSION_DATA_DIR
const std::string SESSION_DATA_SUBDIR = "sessions/";
