#pragma once
#include <string>

// Base Module Class - this will also act as the starting menu of the program
class Module {

public:
	Module();
	~Module();
	virtual int displayTopMenu();
	virtual void displayInternalMenu(/*int*/);
};