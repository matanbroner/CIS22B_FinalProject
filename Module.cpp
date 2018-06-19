#include <string>
#include <iostream>
#include "Module.h"
#include <iomanip>

// Base Module Class - this will also act as the starting menu of the program
Module::Module() {
	// do nothing
}

Module::~Module() {
	// nothing to delete yet
}

int Module::displayTopMenu() {
	std::cout << std::setw(20) << "-- Welcome to the Serendipity Bookstore Main Menu! --" << std::endl;
	std::cout << "\nWhat would you like to do today?" << std::endl;
	std::cout << "[1] -- Buy books" << std::endl;
	std::cout << "[2] -- Manage inventory" << std::endl;
	std::cout << "[3] -- View reports" << std::endl;
	std::cout << "[0] -- Exit" << std::endl << std::endl;
	std::cout << "Option: ";

	int input;
	std::cin >> input;

	return input;
}

void Module::displayInternalMenu(/*int input*/) {
	// none, Module doesn't have its own Internal menu
	//return NULL;
}