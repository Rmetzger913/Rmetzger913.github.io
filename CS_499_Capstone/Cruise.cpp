/*
This cpp defines all of the functions being used by the cruise commands.
These defined functions include the constructor for cruises, functions to for acquiring variables to be printed in the print functions, and the CRUD functions.
*/

#ifndef CRUISE_H
#define CRUISE_H

#include "Cruise.h"

//Default Constructor
Cruise::Cruise()
{

}

//Overloaded Constructor
Cruise::Cruise(std::string newCruiseName, std::string newCruiseShipName, std::string newDeparturePort, std::string newDestination, std::string newReturnPort)
{
	cruiseName = newCruiseName;
	cruiseShip = newCruiseShipName;
	departurePort = newDeparturePort;
	destination = newDestination;
	returnPort = newReturnPort;
}

//Deconstructor
Cruise::~Cruise()
{

}

//Function to collect and create a new cruise to be added to the list of cruises.
void Cruise::addCruise()
{
	//Display and questions to collect data for new cruise.
	std::cout << "Enter name of Cruise: \n";
	std::getline(std::cin >> std::ws, cruiseName);

	std::cout << "Enter cruise ship: \n";
	std::getline(std::cin >> std::ws, cruiseShip);

	std::cout << "Enter the departure port: \n";
	std::getline(std::cin >> std::ws, departurePort);

	std::cout << "Enter the destination of the cruise: \n";
	std::getline(std::cin >> std::ws, destination);

	std::cout << "Enter the return port: \n";
	std::getline(std::cin >> std::ws, returnPort);

	//String command used to add new cruises to the list.
	std::string newCruiseQuery = "INSERT INTO CRUISES(CRUISE_NAME, CRUISE_SHIP_NAME, DEPARTURE_PORT, DESTINATION, RETURN_PORT) VALUES(?,?,?,?,?);";

	int exit = sqlite3_open(directory, &DB); //Opens the database
	exit = sqlite3_prepare_v2(DB, newCruiseQuery.c_str(), -1, &stmt, NULL); //prepares the query for use in SQLite
	
	//Binds the user inputs to the query string based on location. 
	sqlite3_bind_text(stmt, 1, cruiseName.c_str(), cruiseName.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, cruiseShip.c_str(), cruiseShip.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, departurePort.c_str(), departurePort.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, destination.c_str(), destination.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, returnPort.c_str(), returnPort.length(), SQLITE_TRANSIENT);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the add cruise function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the cruise was successfully added to the list.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in add cruise function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Cruise added successfully";
	}

	sqlite3_close(DB); //closes database
}

//Function to edit the cruise data.
void Cruise::editCruise()
{
	int cruiseID; //Id of the cruise to be edited
	std::string userChoice = "";

	//Query strings used to update the cruise in SQLite.
	std::string updateNameQuery = "UPDATE CRUISES SET CRUISE_NAME = ? WHERE ID=?";
	std::string updateShipQuery = "UPDATE CRUISES SET CRUISE_SHIP_NAME = ? WHERE ID=?";
	std::string updateDepartureQuery = "UPDATE CRUISES SET DEPARTURE_PORT = ? WHERE ID=?";
	std::string updateDestinationQuery = "UPDATE CRUISES SET DESTINATION = ? WHERE ID=?";
	std::string updateReturnQuery = "UPDATE CRUISES SET RETURN_PORT = ? WHERE ID=?";

	//Determines what cruise the user wants to change.
	std::cout << "Please enter the ID of cruise to change: \n";
	//While loop to prevent any value other than integers to be input
	while (!(std::cin >> cruiseID))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter the ID of cruise to update: \n";
	}

	int exit = sqlite3_open(directory, &DB); //Opens database

	std::cout << "What do you want to update (1: Cruise Name, 2: Name of Cruise Ship, 3: Departure Port, 4: Destination, 5: Return Port): \n";

	//User choices they can edit.
	std::cin >> userChoice;
	if (userChoice == "1")
	{
		std::cout << "Enter New Cruise Name: ";
		std::getline(std::cin >> std::ws, cruiseName);
		exit = sqlite3_prepare_v2(DB, updateNameQuery.c_str(), -1, &stmt, NULL); //Prepares the query string for use
		//Binds the user inputs to the query string.
		sqlite3_bind_text(stmt, 1, cruiseName.c_str(), cruiseName.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, cruiseID);
	}
	else if (userChoice == "2")
	{
		std::cout << "Enter new cruise ship name: ";
		std::getline(std::cin >> std::ws, cruiseShip);
		exit = sqlite3_prepare_v2(DB, updateShipQuery.c_str(), -1, &stmt, NULL);//Prepares the query string for use
		//Binds the user inputs to the query string
		sqlite3_bind_text(stmt, 1, cruiseShip.c_str(), cruiseShip.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, cruiseID);
	}
	else if (userChoice == "3")
	{
		std::cout << "Enter New Departure Port Name: ";
		std::getline(std::cin >> std::ws, departurePort);
		exit = sqlite3_prepare_v2(DB, updateDepartureQuery.c_str(), -1, &stmt, NULL); //Prepares query string for use
		//Binds user inputs to the query string
		sqlite3_bind_text(stmt, 1, departurePort.c_str(), departurePort.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, cruiseID);
	}
	else if (userChoice == "4")
	{
		std::cout << "Enter New Destination Name: ";
		std::getline(std::cin >> std::ws, destination);
		exit = sqlite3_prepare_v2(DB, updateDestinationQuery.c_str(), -1, &stmt, NULL); //Prpares the query string for use
		//Binds the user inputs to the query string
		sqlite3_bind_text(stmt, 1, destination.c_str(), destination.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, cruiseID);
	}
	else if (userChoice == "5")
	{
		std::cout << "Enter New Return Port Name: ";
		std::getline(std::cin >> std::ws, returnPort);
		exit = sqlite3_prepare_v2(DB, updateReturnQuery.c_str(), -1, &stmt, NULL); //Prepares the query string for use
		//Binds the user inputs to the query string
		sqlite3_bind_text(stmt, 1, returnPort.c_str(), returnPort.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, cruiseID);
	}

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the update cruise function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the cruise was successfully updated.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in update cruise Function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Data updated successfully";
	}

	sqlite3_close(DB); //closes the database
}

//Function for deleteing cruise data. 
void Cruise::deleteCruise()
{
	int cruiseID; //ID of cruise to be deleted

	std::cout << "Enter cruise ID number: \n";
	//While loop to prevent any value other than integers to be input
	while (!(std::cin >> cruiseID))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter the ID of cruise to update: \n";
	}

	//Query string used to delete the cruise
	std::string deleteQuery = "DELETE FROM CRUISES WHERE ID=?";

	int exit = sqlite3_open(directory, &DB); //Opens the Database
	exit = sqlite3_prepare_v2(DB, deleteQuery.c_str(), -1, &stmt, NULL); //Prepares query string for us
	sqlite3_bind_int(stmt, 1, cruiseID); //Binds the user input to the ID
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the delete cruise function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the cruise was successfully deleted from the list.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in delete cruise function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Cruise deleted successfully\n";
	}

	sqlite3_close(DB); //Closes the database

}

//Function for printing out the list of cruises
void Cruise::printCruiseList()
{
	//Query string used to select the names of cruises
	std::string userQuery = "SELECT CRUISE_NAME FROM CRUISES";

	int exit = sqlite3_open(directory, &DB); //Opens Database
	exit = sqlite3_prepare_v2(DB, userQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use

	//Checks to make sure that the print cruise names function works properly and there are no connection errors. If there is an error it will print it out otherwise it will print out the names of all the cruises in the table.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in print cruise name function\n";
		sqlite3_free(errorMessage);
	}
	else
	{
		while ((exit = sqlite3_step(stmt) == SQLITE_ROW))
		{
			std::cout << sqlite3_column_text(stmt, 0) << std::endl;
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB); //Closes database
}

//Function for printing out all cruise details.
void Cruise::printCruiseDetails()
{
	//Query string used to select all data from the cruise table
	std::string userQuery = "SELECT * FROM CRUISES";

	//Display for the cruise details
	std::cout <<"\n\t\tCRUISE LIST - Details\n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "\t\t\t\t\t\t\t\t|----------------------PORTS-----------------------|\n";
	std::cout << std::left << 
		std::setw(10) << "ID" <<
		std::setw(25) << "CRUISE NAME" <<
		std::setw(25) << "SHIP NAME" <<
		std::setw(25) << "DEPARTURE" <<
		std::setw(25) << "DESTINATION" << "RETURN\n";
	std::cout << "----------------------------------------------------------------------------------------------------------------------\n";;

	int exit = sqlite3_open(directory, &DB); //Opens Database
	exit = sqlite3_prepare_v2(DB, userQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use

	//Checks to make sure that the print cruise details function works properly and there are no connection errors. If there is an error it will print it out otherwise it will print out the details of all the cruises in the table.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in print cruise details function\n";
		sqlite3_free(errorMessage);
	}
	else
	{
		//Loops through each row in the table
		while ((exit = sqlite3_step(stmt) == SQLITE_ROW))
		{
			//Prints the data in each column
			std::cout << std::left << 
				std::setw(10) << sqlite3_column_int(stmt, 0) << 
				std::setw(25) << sqlite3_column_text(stmt, 1) <<
				std::setw(25) << sqlite3_column_text(stmt, 2) <<
				std::setw(25) << sqlite3_column_text(stmt, 3) <<
				std::setw(25) << sqlite3_column_text(stmt, 4) <<
				std::setw(25) << sqlite3_column_text(stmt, 5) << std::endl;
		}
	}

	std::cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
	sqlite3_finalize(stmt);
	sqlite3_close(DB); //Closes the database

}
#endif // !CRUISE_H