/*
Author: Timo Bitterli
File: Report.cpp
Last edit: 6/13/2018
Class Report implementation
*/

#include "Report.h"

Report::Report(Inventory& object)
{
	invptr = &object;
}


Report::~Report()
{
}

int Report::getUserInput()
{
	int input = -1;
	bool errorNonInt = false;

	try {
		std::cin >> input;

		if (std::cin.fail()) {	// catch nonint
			std::cin.clear();	// clear error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
			errorNonInt = true;	// used to avoid throwing multiple errors
			throw "Input is invalid. Please try again with an integer value.\n\n";
			input = -1;
		}

		if (input > 6 || input < 0 && errorNonInt == false) {	// catch input out of range -- change 6 to max number of options
			throw "invalid number input out of range.\n";
			input = -1;
		}
	} catch (char *msg) {		//interpret exception from char string passed
		std::cout << "Error: " << msg << std::endl;
		errorNonInt = false;	// reset now that we've dealt with the error
	}

	return input;
}

void Report::processUserInput(int input)
{
	switch (input) {
	case 1:						// choose a default sort type (prefer author?)
		sortByQuantity();		// Inventory List
		reportList();
		break;
	case 2:
		sortByWholesaleValue();	// Inventory Wholesale Value
		reportWholeSaleValue();
		break;
	case 3:
		sortByRetailValue();	// Inventory Retail Value
		reportRetailValue();
		break;
	case 4:
		sortByQuantity();		// List by Quantity
		break;
	case 5:
		sortByWholesaleValue();	// List by Cost
		reportList();
		break;
	case 6:
		sortByAge();			// List by Age	
		reportList();
		break;
	}
}

void Report::moduleMenu()
{
	int input;
	do {
		std::cout << "Welcome to the ReportModule Menu!" << std::endl;
		std::cout << "What would you like to view today?" << std::endl;
		std::cout << "[1] Inventory List\n"
			<< "[2] Inventory Wholesale Value\n"
			<< "[3] Inventory Retail Value\n"
			<< "[4] List by Quantity\n"
			<< "[5] List by Cost\n"
			<< "[6] List by Age	\n"
			<< "[0] Exit Menu\n"
			<< "[?] ";
		input = getUserInput();

		if (input != -1)
			processUserInput(input);
	} while (input != 0);	// only exit menu on input == 0
}

template<typename TYPE>
void sort(TYPE **arr/*, Book *books*/)
{
	int i, j, low;
	for (i = 0; i < 5; i++) {
		low = i;
		for (j = i + 1; j < 5; j++) {
			if (*arr[j] < *arr[low]) { low = j; }
		}
		TYPE *temp = arr[low];
		arr[low] = arr[i];
		arr[i] = temp;

		Book *tempB = invptr->books[low];
		invptr->books[low] = invptr->books[i];
		invptr->books[i] = tempB;
	}
}

void Report::reportList()
{
	// inventory output
}

void Report::reportRetailValue()
{
	double total = totalRetailValue();
	// inventory output
}

void Report::reportWholeSaleValue()
{
	double total = totalWholesaleValue();
	// inventory output

}

//	age is yyyyymmdd:	20180103	20180130
void Report::sortByAge()
{
	int* ageArr[Inventory::bookCount];

	for (int i = 0; i < Inventory::bookCount; i++)
		ageArr[i] = invptr->books[i].getAge();

	sort(ageArr);
	//this->sort(ageArr); only need this if derived
}

void Report::sortByQuantity()
{
	int* quantityArr[Inventory::bookCount];

	for (int i = 0; i < Inventory::bookCount; i++)
		ageArr[i] = invptr->books[i].getStock();

	sort(quantityArr);
}

void Report::sortByRetailValue()
{
	int* retailArr[Inventory::bookCount];

	for (int i = 0; i < Inventory::bookCount; i++)
		ageArr[i] = invptr->books[i].getRetail();

	sort(retailArr);
}

void Report::sortByWholesaleValue()
{
	int* wholesaleArr[Inventory::bookCount];

	for (int i = 0; i < Inventory::bookCount; i++)
		ageArr[i] = invptr->books[i].getWholesale();

	sort(wholesaleArr);
}

double Report::totalRetailValue()
{
	double total=0.00;

	for (int i = 0; i < Inventory::bookCount; i++) {
		total+=invptr->books[i].getRetail();
	}

	return total;
}

double Report::totalWholesaleValue()
{
	double total = 0.00;

	for (int i = 0; i < Inventory::bookCount; i++) {
		total += invptr->books[i].getWholesale();
	}

	return total;
}
