// functions.cpp
#include "functions.h"

void mainMenu(/*,,*/)			// mainMenu that catches non int and input out of range
{
	int input = -1;				// -1 will always be an invalid input
	bool errorNonInt = false;	// true if user entered nonInt

	do {
		try {
			std::cout << "Welcome to the Serendipity Bookstore Main Menu!" << std::endl;
			std::cout << "What would you like to do today?" << std::endl;
			std::cout << "[1] Perform a transaction\n[2] Manage Inventory\n[3] Get Reports\n[0] Exit Program\n[?] ";

			std::cin >> input;		// get user int
			if (std::cin.fail()) {	// catch nonint
				std::cin.clear();	// clear error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
				errorNonInt = true;	// used to avoid throwing multiple errors
				throw "Input is invalid. Please try again with an integer value.\n";
				input = -1;
			}

			if (input > 3 || input < 0 && errorNonInt == false)	// catch input out of range -- change 3 to max number of options
				throw "invalid number input out of range.\n";
		} catch (char *msg) {	//interpret exception from char string passed
			std::cout << "Error: " << msg << std::endl;
			errorNonInt = false; // reset now that we've dealth with the error
		}

		// call appropriate functions for 1, 2, .., n
		switch (input) {
			case 1: std::cout << "1\n";	//cashier.menu(); menu() or getInput() or whatever it's named
				break;
			case 2: std::cout << "2\n";	//inventory.menu();
				break;
			case 3: std::cout << "3\n";	//report.menu();
				break;
		}
	} while (input != 0);	// only exit menu on input == 0
}
