#pragma once
/*
* * This file contains all of the initialized function that will be defined in the cpp files. This will allow the functions to be called from the main file when they are included in it.
Class containing functions of the Cruise class. Used to control Cruise data
*/
#include "Includes.h"

class Cruise
{
public:
	//Constructors and Deconstructor
	Cruise();
	~Cruise();

	//Overloaded constructor
	Cruise(std::string newCruiseName, std::string newCruiseShipName, std::string newDeparturePort, std::string newDestination, std::string newReturnPort);

	//Main Functions of the program. Implements CRUD functions for Cruise.
	void addCruise();
	void editCruise();
	void deleteCruise();
	void printCruiseList();
	void printCruiseDetails();

private:

	//variables used in the functions for the cruise class. 
	std::string cruiseName;
	std::string cruiseShip;
	std::string departurePort;
	std::string destination;
	std::string returnPort;

	//Database variables needed for database integration into the application.
	const char* directory = "c:\\CapstoneDatabase\\database.db"; //directory where the database is found and all data is stored
	sqlite3* DB;
	sqlite3_stmt* stmt;//SQLite statement
	char* errorMessage;//Variable used to collect the error message if error occurs in the various functions.
};