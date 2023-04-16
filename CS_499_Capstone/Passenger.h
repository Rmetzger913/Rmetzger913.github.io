/*
* This file contains all of the initialized function that will be defined in the cpp files. This will allow the functions to be called from the main file when they are included in it.
Class containing functions of the Passenger class. Used to control Passenger data
*/

#include "Includes.h"


class Passenger
{
public:

	//Default constructor and deconstructor
	Passenger();
	~Passenger();

	//Overload constructor
	Passenger(std::string newPassengerName, std::string newPassengerCruise, std::string newPassengerRoomType);

	//Main Functions of the program. Implements CRUD functions for Cruise.
	void addPassenger();
	void editPassenger();
	void deletePassenger();
	void printPassengerList();
	

private:
	//Variables used by the passenger class to function properly.
	std::string passName;
	std::string passCruise;
	std::string passRoomType;

	//Database variables needed for database integration into the application.
	const char* directory = "c:\\CapstoneDatabase\\database.db"; //directory where the database is found and all data is stored
	sqlite3* DB;
	sqlite3_stmt* stmt; //SQLite statement
	char* errorMessage; //Variable used to collect the error message if error occurs in the various functions.
};