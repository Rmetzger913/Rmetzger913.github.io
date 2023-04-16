/*
* CS_499_Capstone.cpp : This file contains the 'main' function.Program execution begins and ends there.
* Program created by Richard Metzger
* This is the main hub for the application and the user interaction. This file contains the user authenicity and then opens into the main menu for the user to interact.
* 
*/ 

#include "Ship.h"
#include "Cruise.h"
#include "Passenger.h"


//Variables to be used in this program
std::string userSeletion; //Used to accept user input for the main function
bool loginResult = false; //Used for confirming user login functionality. Set to false by default for security.

//Variables to be able to use the functions
Passenger passenger; //New passenger objects

Ship ship; //New ship objects

Cruise cruise; //New Cruise Objects

//Proto functions to be used in this program
bool checkUserPermissions();
void displayMenu();
void createTables();

int main()
{

    checkUserPermissions();

    while (userSeletion != "x")
    {

        if (loginResult == true)
        {
            //Displays the initial menu for the user to choose from
            displayMenu();

            std::cin >> userSeletion;

            if (userSeletion == "1")
            {
                //Add Ship Function
                ship.addShip();

            }
            else if (userSeletion == "2")
            {
                ship.editShip();
            }
            else if (userSeletion == "3")
            {
                ship.deleteShip();
            }
            else if (userSeletion == "4")
            {
                cruise.addCruise();
            }
            else if (userSeletion == "5")
            {
                cruise.editCruise();
            }
            else if (userSeletion == "6")
            {
                cruise.deleteCruise();
            }
            else if (userSeletion == "7")
            {
                passenger.addPassenger();
            }
            else if (userSeletion == "8")
            {
                passenger.editPassenger();
            }
            else if (userSeletion == "9")
            {
                passenger.deletePassenger();
            }
            else if (userSeletion == "a")
            {
                ship.printShipNames();
            }
            else if (userSeletion == "b")
            {
                ship.printShipsInService();
            }
            else if (userSeletion == "c")
            {
                ship.printFullListShips();
            }
            else if (userSeletion == "d")
            {
                cruise.printCruiseList();
            }
            else if (userSeletion == "e")
            {
                cruise.printCruiseDetails();
            }
            else if (userSeletion == "f")
            {
                passenger.printPassengerList();
            }

        }
        else
        {
            //If log in is incorrect the function is called again until it is correct.
            std::cout << "Invalid User or Password\n";
            checkUserPermissions();
        }

    }

    return 0;
}

//Fuction to check if the user has permissions to interact with the database. This is just a prototype that will have a different implementation when the database is implemented.
bool checkUserPermissions()
{
    std::string userName;
    std::string userPass;

    //Testing variables
    std::string testUserName = "Richard";
    std::string testUserPass = "123";

    std::cout << "Please enter username: \n";
    std::cin >> userName;

    std::cout << "Please enter password: \n" ;
    std::cin >> userPass;

    if (userName == testUserName && userPass == testUserPass)
    {
        return loginResult = true;
    }
    else
    {
        return loginResult = false;
    }
}

//Function prints out the menu options for the user to use choose from. Additional functions for deleting an item from the lists has to be added.
void displayMenu()
{
    std::cout << "\n\n";
    std::cout << "\t\tLuxury Ocean Cruise Outings\n";
    std::cout << "\t\t\tSystem Menu\n";
    std::cout << "\t[1] Add Ship            [A] Print Ship Names\n";
    std::cout << "\t[2] Edit Ship           [B] Print Ships In Service List\n";
    std::cout << "\t[3] Delete Ship         [C] Print Ship Full List\n";
    std::cout << "\t[4] Add Cruise          [D] Print Cruise List\n";
    std::cout << "\t[5] Edit Cruise         [E] Print Cruise Details\n";
    std::cout << "\t[6] Delete Cruise       [F] Print Passenger List\n";
    std::cout << "\t[7] Add Passenger       \n";
    std::cout << "\t[8] Edit Passenger      \n";
    std::cout << "\t[9] Delete Passenger    \n";
    std::cout << "\t[x] Exit System\n";
    std::cout << "\tPlease enter choice: \n";
}

//Function to add new tables to the database. 
void createTables()
{
    //Variables used to handle the database.
    const char* directory = "c:\\CapstoneDatabase\\database.db";
    sqlite3* DB;
    char* errorMessage;

    //Strings that contain the commands for creating tables within the database. Each string contains the information for a different table.
    // These autoincrement so that the user can properly choose the item from those tables without worrying about whether or not there are duplicate information in the tables.
    //Table for use with Users
    std::string userTable = "CREATE TABLE IF NOT EXISTS USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT, USER TEXT NOT NULL, PASSWORD TEXT NOT NULL);";

    //Text to create passenger table in the SQLite database
    std::string passengerTable = "CREATE TABLE IF NOT EXISTS PASSENGERS(ID INTEGER PRIMARY KEY AUTOINCREMENT, PASSENGER_NAME TEXT NOT NULL, PASSENGER_CRUISE TEXT NOT NULL, PASSENGER_ROOM_TYPE TEXT NOT NULL);";

    std::string shipTable = "CREATE TABLE IF NOT EXISTS SHIPS(ID INTEGER PRIMARY KEY AUTOINCREMENT, SHIP_NAME TEXT NOT NULL, BALCONY_ROOMS INT NOT NULL, OCEANVIEW_ROOMS INT NOT NULL, SUITE_ROOMS INT NOT NULL, INTERIOR_ROOMS INT NOT NULL, SHIP_STATUS TEXT NOT NULL);";

    std::string cruiseTable = "CREATE TABLE IF NOT EXISTS CRUISES(ID INTEGER PRIMARY KEY AUTOINCREMENT, CRUISE_NAME TEXT NOT NULL, CRUISE_SHIP_NAME TEXT NOT NULL, DEPARTURE_PORT TEXT NOT NULL, DESTINATION TEXT NOT NULL, RETURN_PORT TEXT NOT NULL);";

    //Tries to open the database and create tables within the SQLite database. If it fails it will catch the error and print it out.
    try
    {
        //Opens the database so that the tables can be created.
        int exit = sqlite3_open(directory, &DB);

        //Executes command create table in database If the execution fails it will print out error otherwise it will let the user know that the tables are successfully created.
        exit = sqlite3_exec(DB, userTable.c_str(), NULL, 0, &errorMessage);
        if (exit != SQLITE_OK)
        {
            std::cerr << "Error in createTable ::userTable:: Function.\n";
            sqlite3_free(errorMessage);
        }
        else
        {
            std::cout << "User Table Created Successfully. \n";
        }

        exit = sqlite3_exec(DB, passengerTable.c_str(), NULL, 0, &errorMessage);
        if (exit != SQLITE_OK)
        {
            std::cerr << "Error in createTable :: passengerTable::Function.\n";
            sqlite3_free(errorMessage);
        }
        else
        {
            std::cout << "Passenger Table Created Successfully. \n";
        }

        exit = sqlite3_exec(DB, shipTable.c_str(), NULL, 0, &errorMessage);
        if (exit != SQLITE_OK)
        {
            std::cerr << "Error in createTable :: shipTable::Function.\n";
            sqlite3_free(errorMessage);
        }
        else
        {
            std::cout << "Ship Table Created Successfully. \n";
        }

        exit = sqlite3_exec(DB, cruiseTable.c_str(), NULL, 0, &errorMessage);
        if (exit != SQLITE_OK)
        {
            std::cerr << "Error in createTable :: cruiseTable::Function.\n";
            sqlite3_free(errorMessage);
        }
        else
        {
            std::cout << "Cruise Table Created Successfully. \n";
        }
        sqlite3_close(DB);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }

}

