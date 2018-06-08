#pragma once
#include <string>

// Base Module Class - this will also act as the starting menu of the program
class Module {

public:
	Module();
	~Module();
	int displayTopMenu();
	int displayInternalMenu(int);
};