/*
This cpp defines all of the functions being used by the passenger commands.
These defined functions include the constructor for passengers, functions to for acquiring variables to be printed in the print functions, and the CRUD functions.
*/
#ifndef PASSENGER_H
#define PASSENGER_H

#include "Passenger.h"

//Default constructor
Passenger::Passenger()
{

}

//Overload constructor
Passenger::Passenger(std::string newPassengerName, std::string newPassengerCruise, std::string newPassengerRoomType)
{
	passName = newPassengerName;
	passCruise = newPassengerCruise;
	passRoomType = newPassengerRoomType;
}

//Deconstructor
Passenger::~Passenger()
{

}

//CRUD functions for passengers.

//Accepts user input to create a new passenger.
void Passenger::addPassenger()
{
	//Accepts user input to be used to create a new passenger.
	std::cout << "Enter Passenger Name: \n";
	std::getline(std::cin >> std::ws, passName);

	std::cout << "Enter Cruise Name: \n";
	std::getline(std::cin >> std::ws, passCruise); 

	std::cout << "Enter the Room Type: \n";
	std::cin >> passRoomType;

	//Loop function to prevent any other value other than the 4 room types to be input.
	while (passRoomType != "BAL" && passRoomType != "OV" && passRoomType != "STE" && passRoomType != "INT")
	{
		std::cout << ":ERROR::INCORRECT::ROOM::TYPE::MUST::BE::BAL::OV::STE::INT\n";

		std::cout << "Enter the Room Type: \n";
		std::cin >> passRoomType;
	}

	//String query used to add passenger to the table
	std::string newPassengerQuery = "INSERT INTO PASSENGERS(PASSENGER_NAME, PASSENGER_CRUISE, PASSENGER_ROOM_TYPE) VALUES(?,?,?);";

	int exit = sqlite3_open(directory, &DB); //Opens the database
	exit = sqlite3_prepare_v2(DB, newPassengerQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use
	//Binds the user inputs to the query statement
	sqlite3_bind_text(stmt, 1, passName.c_str(), passName.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, passCruise.c_str(), passCruise.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, passRoomType.c_str(), passRoomType.length(), SQLITE_TRANSIENT);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the add passenger function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the passenger was successfully added to the list.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in add passenger function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Passenger added successfully";
	}

	sqlite3_close(DB); //Closes the database
}

//Function for editing the passengers on the list.
void Passenger::editPassenger()
{
	int passID; //Id of passenger to update

	std::cout << "Please enter the ID of passenger to update: \n";
	//While loop to prevent any value other than integers to be input
	while (!(std::cin >> passID))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter the ID of passenger to update: \n";
	}

	//String Queries used to update the passenger information
	std::string updateNameQuery = "UPDATE PASSENGERS SET PASSENGER_NAME = ? WHERE ID=?";
	std::string updateCruiseQuery = "UPDATE PASSENGERS SET PASSENGER_CRUISE = ? WHERE ID=?";
	std::string updateRoomTypeQuery = "UPDATE PASSENGERS SET PASSENGER_ROOM_TYPE = ? WHERE ID=?";

	int exit = sqlite3_open(directory, &DB); //Opens Database
	
	std::string userChoice = "";
	std::cout << "What do you want to update (1: Name, 2: Cruise, 3: Room Type): \n";
	std::cin >> userChoice;
	if (userChoice == "1")
	{
		std::cout << "Enter New Name: ";
		std::getline(std::cin >> std::ws, passName); passName;
		exit = sqlite3_prepare_v2(DB, updateNameQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use
		//Binds user input to the query string
		sqlite3_bind_text(stmt, 1, passName.c_str(), passName.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, passID);
	}
	else if (userChoice == "2")
	{
		std::cout << "Enter new cruise: ";
		std::getline(std::cin >> std::ws, passCruise);
		exit = sqlite3_prepare_v2(DB, updateCruiseQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use
		//Binds the user input to the query string
		sqlite3_bind_text(stmt, 2, passCruise.c_str(), passCruise.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, passID);
	}
	else if (userChoice == "3")
	{
		std::cout << "Enter new room type: ";
		std::cin >> passRoomType;

		//Loop to control the input from the users for the room choice.
		while (passRoomType != "BAL" && passRoomType != "OV" && passRoomType != "STE" && passRoomType != "INT")
		{
			std::cout << ":ERROR::INCORRECT::ROOM::TYPE::MUST::BE::BAL::OV::STE::INT\n";

			std::cout << "Enter the Room Type: \n";
			std::cin >> passRoomType;
		}
		exit = sqlite3_prepare_v2(DB, updateRoomTypeQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use
		//Binds user input to the query
		sqlite3_bind_text(stmt, 3, passRoomType.c_str(), passRoomType.length(), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, passID);
	}

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the edit passenger function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the passenger was successfully updated.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in Update PASSENGER Function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Data Updated Successfully";
	}
	
	sqlite3_close(DB); //Closes the database
}

//Function to delete a passenger from the list.
void Passenger::deletePassenger()
{
	int passID; //passenger to be deleted

	std::cout << "Enter user ID number: \n";
	//While loop to prevent any value other than integers to be input
	while (!(std::cin >> passID))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter the ID of passenger to update: \n";
	}

	//Query string to delete passenger
	std::string deleteQuery = "DELETE FROM PASSENGERS WHERE ID=?";

	int exit = sqlite3_open(directory, &DB); //Opens database
	exit = sqlite3_prepare_v2(DB, deleteQuery.c_str(), -1, &stmt, NULL);//Prepares the query for use
	sqlite3_bind_int(stmt, 1, passID); //Binds user input to the query string
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//Checks to make sure that the delete passenger function works properly and there are no connection errors. If there is an error it will print it out otherwise it will let the user know that the passenger was successfully deleted from the list.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in DELETE PASSENGER Function.\n";
		sqlite3_free(&errorMessage);
	}
	else
	{
		std::cout << "Data Deleted Successfully\n";
	}
	sqlite3_close(DB);//closes database
}

//Function for printing the passenger list.
void Passenger::printPassengerList()
{
	//String query to select all data from the passengers table
	std::string userQuery = "SELECT * FROM PASSENGERS";

	//Display for passenger data
	std::cout << "\n\t\tPASSENGER LIST\n";
	std::cout << "-------------------------------------------------------------------------------------------------------------------\n";
	std::cout << std::left << 
		std::setw(10) << "ID" << 
		std::setw(25) << "PASSENGER NAME" <<
		std::setw(25) << "CRUISE" << "ROOM TYPE\n";
	std::cout << std::left << "-------------------------------------------------------------------------------------------------------------\n";

	int exit = sqlite3_open(directory, &DB); //Opens the database
	exit = sqlite3_prepare_v2(DB, userQuery.c_str(), -1, &stmt, NULL); //Prepares the query for use

	//Checks to make sure that the print passenger details function works properly and there are no connection errors. If there is an error it will print it out otherwise it will print out the details of all the passenger in the table.
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error in print passenger function\n";
		sqlite3_free(errorMessage);
	}
	else
	{
		//Loops through each row of the table
		while ((exit = sqlite3_step(stmt) == SQLITE_ROW))
		{
			//Prints out the information from each column for each iteration
			std::cout << std::left << 
				std::setw(10) <<sqlite3_column_int(stmt, 0) <<
				std::setw(25) << sqlite3_column_text(stmt, 1) <<
				std::setw(25) << sqlite3_column_text(stmt, 2) <<
				std::setw(25) << sqlite3_column_text(stmt, 3) << std::endl;
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB); //Closes the database.
}
#endif // !PASSENGER_H


