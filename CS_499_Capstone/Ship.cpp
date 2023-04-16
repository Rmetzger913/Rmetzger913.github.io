/*
This cpp defines all of the functions being used by the ship commands.
These defined functions include the constructor for ships, functions to for acquiring variables to be printed in the print functions, and the CRUD functions.

*/

#ifndef SHIP_H
#define SHIP_H

#include "Ship.h"

//Default constructor
Ship::Ship()
{

}

//Constructor that is overloaded. This is the most common use.
Ship::Ship(std::string newShipName, int newRoomBalconyNum, int newRoomOceanViewNum, int newRoomSuiteNum, int newRoomInteriorNum, bool newInService)
{
	shipName = newShipName;
	numOfBalconyRooms = newRoomBalconyNum;
	numOfroomsOceanView = newRoomOceanViewNum;
	numOfRoomSuite = newRoomSuiteNum;
	numOfInteriorRooms = newRoomInteriorNum;
	shipStatus = newInService;
}

//Deconstructor
Ship::~Ship()
{
}

//This functions is used to add new ships to the ship list. 
void Ship::addShip()
{
	//DATA COLLECTION FUNCTIONS
	//Set of questions to acquire ship data to create a new ship.
	std::cout << "Enter ship name: \n";
	std::getline(std::cin >> std::ws, shipName);

	std::cout << "Enter number of balcony rooms: \n";
	std::cin >> numOfBalconyRooms;

	std::cout << "Enter number of rooms with an ocean view: \n";
	std::cin >> numOfroomsOceanView;

	std::cout << "Enter number of suites: \n";
	std::cin >> numOfRoomSuite;

	std::cout << "Enter number of interior rooms: \n";
	std::cin >> numOfInteriorRooms;

	std::cout << "Is the ship in service (enter yes or no): \n";
	std::getline(std::cin >> std::ws, shipStatus);

	//While loop to control the responses that users input. If the value is anything other than yes or no it will remain in the while loop.
	while (shipStatus != "yes" && shipStatus != "no")
	{
		std::cout << ":ERROR::INCORRECT::ANSWER::ENTER::YES::OR:::NO\n";

		std::cout << "Is the ship in service (enter yes or no): \n";
		std::getline(std::cin >> std::ws, shipStatus);

	}

	//DATABASE FUNCTIONS
	//Database string used to add new ships to the ship table in the database. Sets the initial string and then allows users to properly input data intt the string for full functionality.
	std::string newShipQuery = "INSERT INTO SHIPS(SHIP_NAME, BALCONY_ROOMS, OCEANVIEW_ROOMS, SUITE_ROOMS, INTERIOR_ROOMS, SHIP_STATUS) VALUES(?,?,?,?,?,?);";

	int exit = sqlite3_open(directory, &DB); //Opens database to allow interaction with it.
	exit = sqlite3_prepare_v2(DB, newShipQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use in database
	//Binds the various user inputs in the the query string. These are based on the order they are needed in the string.
	sqlite3_bind_text(stmt, 1, shipName.c_str(), shipName.length(), SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, numOfBalconyRooms);
	sqlite3_bind_int(stmt, 3, numOfroomsOceanView);
	sqlite3_bind_int(stmt, 4, numOfRoomSuite);
	sqlite3_bind_int(stmt, 5, numOfInteriorRooms);
	sqlite3_bind_text(stmt, 6, shipStatus.c_str(), shipStatus.length(), SQLITE_TRANSIENT);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the add ship function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the ship was successfully added to the list.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in add ship function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Ship added successfully";
	}

	//Closes the database after use.
	sqlite3_close(DB);
}

//Function to edit the different variables of the ships that are already added to the list. Currently only uses the name but for better work an alternative variable will need to be added to pick specific items from the list. Currently I have breaks added to prevent the loop from changing all values that are equal to the input. This isn't a efficient way of handling this.
void Ship::editShip()
{

	//Variables
	int shipID; //Id used to determine which ship is being updated
	std::string userChoice = "";

	//Strings used to query the specific update the user desires
	std::string updateNameQuery = "UPDATE SHIPS SET SHIP_NAME = ? WHERE ID=?";
	std::string updateBalconyQuery = "UPDATE SHIPS SET BALCONY_ROOMS = ? WHERE ID=?";
	std::string updateOceanQuery = "UPDATE SHIPS SET OCEANVIEW_ROOMS = ? WHERE ID=?";
	std::string updateSuiteQuery = "UPDATE SHIPS SET SUITE_ROOMS = ? WHERE ID=?";
	std::string updateInteriorQuery = "UPDATE SHIPS SET INTERIOR_ROOMS = ? WHERE ID=?";
	std::string updateStatusQuery = "UPDATE SHIPS SET SHIP_STATUS = ? WHERE ID=?";

	//Opens the database
	int exit = sqlite3_open(directory, &DB);

	//DATA COLLECTION FUNCTIONS
	std::cout << "Please enter the ID of the ship to update: \n";
	//While loop to prevent any value other than integers to be input
	while (!(std::cin >> shipID))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter the ID of the ship to update: \n";
	}

	std::cout << "What do you want to update (1: Name, 2: Number of balcony rooms, 3: Number of Ocean View Rooms, 4: Number of room Suites, 5: Number of interior rooms, 6: Service Status of Ship): \n";

	//Options for user to choose for items to update.
	std::cin >> userChoice;
	if (userChoice == "1")
	{
		std::cout << "Enter New Name: ";
		std::getline(std::cin >> std::ws, shipName);
		//prepares the statement for the query and binds the user variable to the statement.
		exit = sqlite3_prepare_v2(DB, updateNameQuery.c_str(), -1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, shipName.c_str(), shipName.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, shipID);
	}
	else if (userChoice == "2")
	{
		std::cout << "Enter Number of Balcony Rooms: \n";
		std::cin >> numOfBalconyRooms;
		//prepares the statement for the query and binds the user variable to the statement.
		exit = sqlite3_prepare_v2(DB, updateBalconyQuery.c_str(), -1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, numOfBalconyRooms);
		sqlite3_bind_int(stmt, 2, shipID);
	}
	else if (userChoice == "3")
	{
		std::cout << "Enter Number of Ocean View Rooms: \n";
		std::cin >> numOfroomsOceanView;
		//prepares the statement for the query and binds the user variable to the statement.
		exit = sqlite3_prepare_v2(DB, updateOceanQuery.c_str(), -1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, numOfroomsOceanView);
		sqlite3_bind_int(stmt, 2, shipID);
	}
	else if (userChoice == "4")
	{
		std::cout << "Enter Number of Room Suites: \n";
		std::cin >> numOfRoomSuite;
		//prepares the statement for the query and binds the user variable to the statement.
		exit = sqlite3_prepare_v2(DB, updateSuiteQuery.c_str(), -1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, numOfRoomSuite);
		sqlite3_bind_int(stmt, 2, shipID);
	}
	else if (userChoice == "5")
	{
		std::cout << "Enter Number of Interior Rooms: \n";
		std::cin >> numOfInteriorRooms;
		//prepares the statement for the query and binds the user variable to the statement.
		exit = sqlite3_prepare_v2(DB, updateInteriorQuery.c_str(), -1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, numOfInteriorRooms);
		sqlite3_bind_int(stmt, 2, shipID);
	}
	else if (userChoice == "6")
	{
		
		std::cout << "Is the ship in service (enter yes or no): \n";
		std::getline(std::cin >> std::ws, shipStatus);

		//While loop to make sure that the user inputs only yes or no. Any other answer will triger the loop.
		while (shipStatus != "yes" && shipStatus != "no")
		{
			std::cout << ":ERROR::INCORRECT::ANSWER::ENTER::YES::OR:::NO\n";

			std::cout << "Is the ship in service (enter yes or no): \n";
			std::cin >> shipStatus;
		}
		//prepares the statement for the query and binds the user variable to the statement.
		exit = sqlite3_prepare_v2(DB, updateStatusQuery.c_str(), -1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, shipStatus.c_str(), shipStatus.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, shipID);
	}

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	 
	//Checks to make sure that the update ship function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the ship was successfully updated.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in update ship function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Ship updated successfully";
	}

	//Closes database after interaction
	sqlite3_close(DB);
}


//Function to delete ships from the list.
void Ship::deleteShip()
{
	int shipID; //Variable used to identify which ship is to be deleted

	std::cout << "Enter ship ID number to delete: \n";
	//While loop to prevent any value other than integers to be input
	while (!(std::cin >> shipID))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter the ID of the ship to delete: \n";
	}

	//String command to delete the ship
	std::string deleteQuery = "DELETE FROM SHIPS WHERE ID=?";

	int exit = sqlite3_open(directory, &DB); //Opens database
	exit = sqlite3_prepare_v2(DB, deleteQuery.c_str(), -1, &stmt, NULL); //Prepared the above statement 
	sqlite3_bind_int(stmt, 1, shipID); //Binds the ship id to the string so that the correct ship is being deleted.
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the delete ship function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the ship was successfully deleted from the list.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in DELETE SHIP Function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Ship deleted successfully\n";
	}
	//closes the database
	sqlite3_close(DB);
}

//Function to print only the names of the ships on the list.
void Ship::printShipNames()
{
	//String command used to get all ship names
	std::string userQuery = "SELECT SHIP_NAME FROM SHIPS";

	int exit = sqlite3_open(directory, &DB); //Opens database
	exit = sqlite3_prepare_v2(DB, userQuery.c_str(), -1, &stmt, NULL); //Prepares the string for use

	//Checks to make sure that the print ship name function works properly and there are no connection errors. If there is an error it will print it out otherwise it will print out the names of all ships in the database.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in print ship name function\n";
		sqlite3_free(errorMessage);
	}
	else
	{
		//Loops to iterate through the table until it is done. 
		while ((exit = sqlite3_step(stmt) == SQLITE_ROW))
		{
			//Prints out all of the column text that is chosen.
			std::cout << sqlite3_column_text(stmt, 0) << std::endl;
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB); //Closes database
}

//Function to print the name of all ships that are currently active
void Ship::printShipsInService()
{
	//String Command used to get all ship names that are in service
	std::string userQuery = "SELECT SHIP_NAME FROM SHIPS WHERE SHIP_STATUS='yes'";

	std::cout << "\t\t\t\tSHIP IN ACTIVE SERVICE LIST\n";
	std::cout << "------------------------------------------------------------\n";

	int exit = sqlite3_open(directory, &DB); //Opens Database
	exit = sqlite3_prepare_v2(DB, userQuery.c_str(), -1, &stmt, NULL); //Prepared the command string for database use.

	//Checks to make sure that the print ships in service function works properly and there are no connection errors. If there is an error it will print it out otherwise it will print out the names of all ships in service in the database.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in print ship status function\n";
		sqlite3_free(errorMessage);
	}
	else
	{
		while ((exit = sqlite3_step(stmt) == SQLITE_ROW))
		{
			std::cout << sqlite3_column_text(stmt, 0) << std::endl;
		}
	}

	std::cout << "------------------------------------------------------------\n";
	sqlite3_finalize(stmt);
	sqlite3_close(DB);//closes the database
}

//Function to print the all details of the ship lists.
void Ship::printFullListShips()
{
	//String command to pull all information from the ships table to be printed.
	std::string userQuery = "SELECT * FROM SHIPS";

	//Display for ship listing
	std::cout << "\n\t\tSHIP LIST - FULL\n";
	std::cout << "------------------------------------------------------------------------------------------\n";
	std::cout << std::left << 
		std::setw(10) << "ID" <<
		std::setw(25) << "SHIP NAME" <<
		std::setw(20) << "NUMBER OF ROOMS" <<
		std::setw(25) << "STATUS\n";
	std::cout << "\t\t   BAL  OV  STE  INT\n";
	std::cout << "------------------------------------------------------------------------------------------\n";

	int exit = sqlite3_open(directory, &DB); //Opens the database
	exit = sqlite3_prepare_v2(DB, userQuery.c_str(), -1, &stmt, NULL); //prepares the query string for use. 

	//Checks to make sure that the print ship details function works properly and there are no connection errors. If there is an error it will print it out otherwise it will print out the information about all ships in the database.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in print full ship list function\n";
		sqlite3_free(errorMessage);
	}
	else
	{
		//Loops through each row in the table until there are none left.
		while ((exit = sqlite3_step(stmt) == SQLITE_ROW))
		{
			//Prints out the information from each column through out each iteration.
			std::cout << std::left <<
				std::setw(10) << sqlite3_column_int(stmt, 0) << 
				std::setw(25) << sqlite3_column_text(stmt, 1) <<
				std::setw(5) << sqlite3_column_int(stmt, 2) << 
				std::setw(4) << sqlite3_column_int(stmt, 3) << 
				std::setw(5) << sqlite3_column_int(stmt, 4) << 
				std::setw(6) << sqlite3_column_int(stmt, 5) << 
				sqlite3_column_text(stmt, 6) << std::endl;
		}
	}

	std::cout << "------------------------------------------------------------------------------------------\n";
	sqlite3_finalize(stmt);
	sqlite3_close(DB);//Closes Database
}
#endif // !SHIP_H
