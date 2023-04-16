#pragma once
/*
* This file contains all of the initialized function that will be defined in the cpp files. This will allow the functions to be called from the main file when they are included in it.
Class containing functions of the ship class. Used to control ship data
*/

#include "Includes.h"
class Ship
{
public:
	
	//Default constructor and deconstructor
	Ship();
	~Ship();

	//Overloaded constructor used as the main source of creating new ships
	Ship(std::string newShipName, int newRoomBalconyNum, int newRoomOceanViewNum, int newRoomSuiteNum, int newRoomInteriorNum, bool newInService);

	//Main Functions of the program. Implements CRUD functions for Ships
	void addShip(); 
	void editShip();
	void deleteShip();

	//These functions print the various different options for ships.
	void printShipNames(); //Prints only the ship names
	void printShipsInService(); //Prints names of ships currently in service.
	void printFullListShips(); //Prints ship list with all details available. 


private:
	//variables used in the functions for the ship class.
	std::string shipName = "";
	int numOfBalconyRooms = 0;
	int numOfroomsOceanView = 0;
	int numOfRoomSuite = 0;
	int numOfInteriorRooms = 0;
	std::string shipStatus;

	//Database variables needed for database integration into the application.
	const char* directory = "c:\\CapstoneDatabase\\database.db"; //directory where the database is found and all data is stored
	sqlite3* DB;
	sqlite3_stmt* stmt;//SQLite statement
	char* errorMessage;//Variable used to collect the error message if error occurs in the various functions.
};
