// example menu that catches non int and intput out of range

#include <iostream>

void menuExample(/**/)
{
	int input = -1;
	bool errorNonInt = false;

	do {
		try {
			std::cout << "Welcome to the ModuleName Menu!" << std::endl;
			std::cout << "What would you like to do today?" << std::endl;
			std::cout << "[1] Thing1\n"
				<< "[2] Thing2\n"
				<< "[3] Thing3\n"
				<< "[n] Thingn\n"	// add or remove as necessary
				<< "[0] Exit Menu\n"
				<< "[?] ";

			std::cin >> input;		// get user int
			if (std::cin.fail()) {	// catch nonint
				std::cin.clear();	// clear error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
				errorNonInt = true;	// used to avoid throwing multiple errors
				throw "Input is invalid. Please try again with an integer value.\n\n";
				input = -1;
			}

			if (input > 3 || input < 0 && errorNonInt == false)	// catch input out of range -- change 3 to max number of options
				throw "invalid number input out of range.\n";
		} catch (char *msg)	{		//interpret exception from char string passed
			std::cout << "Error: " << msg << std::endl;
			errorNonInt = false;	// reset now that we've dealt with the error
		}

		// call appropriate functions for 1, 2, .., n
		switch (input) {
			case 1 : std::cout << "1\n";
				break;
			case 2: std::cout << "2\n";
				break;
			case 3: std::cout << "3\n";
				break;
		}
	} while (input != 0);	// only exit menu on input == 0
}
