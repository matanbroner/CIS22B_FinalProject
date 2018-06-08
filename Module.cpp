#include <string>
#include <iostream>
#include "Module.h"

// Base Module Class - this will also act as the starting menu of the program
Module::Module() {
	// do nothing
}

Module::~Module() {
	// nothing to delete yet
}

int Module::displayTopMenu() {
	std::cout << "Choose from the following Menu options: " << std::endl;
	std::cout << "1. Buy books" << std::endl;
	std::cout << "2. Manage inventory" << std::endl;
	std::cout << "3. View reports" << std::endl;
	std::cout << "4. Exit" << std::endl;

	int input;
	std::cin >> input;

	return input;
}

int Module::displayInternalMenu(int input) {
	// none, Module doesn't have its own Internal menu
}