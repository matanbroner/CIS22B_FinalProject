/*
Author: Timo Bitterli
File: Report.cpp
Last edit: 6/18/2018
Class Report implementation
*/

#include "Report.h"

Report::Report(Inventory* object)
{
	invptr = object;
}

Report::Report(Module* object)
{
	//invptr = object[3];
	modptr = object;
	object->bookCount;		// no idea how to get tihs goin
	invptr = object;		// 
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

void Report::displayInternalMenu(int input)
{
	sortArr = new int[invptr->bookCount];
	for (int i = 0; i < invptr->bookCount; i++)
		sortArr[i] = i; 

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
		reportList();
		break;
	case 5:
		sortByWholesaleValue();	// List by Cost
		reportWholesale();
		break;
	case 6:
		sortByAge();			// List by Age	
		reportAge();
		break;
	}
	delete[] sortArr;
}

void Report::displayTopMenu()
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
			<< "[6] List by Age\n"
			<< "[0] Exit Menu\n"
			<< "[?] ";
		input = getUserInput();

		if (input != -1)
			displayInternalMenu(input);
	} while (input != 0);	// only exit menu on input == 0
}

template<typename TYPE>
void Report::sort(TYPE **arr)
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

	int tempi = sortArr[i];
	sortArr[low] = sortArr[i];
	sortArr[i] = tempi;
	}
}

void Report::reportList() // quantity
{
	// inventory output
	invptr->viewInventory();
}

void Report::reportAge()
{
	int pages = 0;
	if (invptr->bookCount % 10 == 0) // book count is divisible by 10
		pages = invptr->bookCount / 10;
	else pages = (invptr->bookCount / 10) + 1; // add extra page for remainder

	cout << "There are " << pages << " in your Inventory." << std::endl;
	cout << "View Page: ";
	cin >> pages;

	cout << setw(30) << "Page " << pages << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;
	cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(5) << "Date Added" << setw(5) << "Stock" << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;

	if (10 * pages > invptr->bookCount) // bookc count is not divisible by 10 and user chose last page
	{
		int diff = invptr->bookCount - (10 * (pages - 1));
		for (int i = invptr->bookCount - diff; i < invptr->bookCount; i++)
		{
			cout << setw(25) << left << invptr->books[sortArr[i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getPub() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getDate() << "   ";
			cout << invptr->books[sortArr[i]]->getStock() << std::endl;
		}
	}

	else // normal page display if user chose any page before last
	{
		for (int i = 10; i >= 1; i--)
		{
			cout << setw(25) << left << invptr->books[sortArr[(10 * pages) - i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getPub() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getDate() << "   ";
			cout << invptr->books[sortArr[(10 * pages) - i]]->getStock() << std::endl;
		}
	}
}

void Report::reportWholesale()
{
	// inventory output
	int pages = 0;
	if (invptr->bookCount % 10 == 0) // book count is divisible by 10
		pages = invptr->bookCount / 10;
	else pages = (invptr->bookCount / 10) + 1; // add extra page for remainder

	cout << "There are " << pages << " in your Inventory." << std::endl;
	cout << "View Page: ";
	cin >> pages;

	cout << setw(30) << "Page " << pages << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;
	cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(5) << "Cost" << setw(5) << "Stock" << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;

	if (10 * pages > invptr->bookCount) // book count is not divisible by 10 and user chose last page
	{
		int diff = invptr->bookCount - (10 * (pages - 1));
		for (int i = invptr->bookCount - diff; i < invptr->bookCount; i++)
		{
			cout << setw(25) << left << invptr->books[sortArr[i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getPub() << "   ";
			//cout << setw(15) << invptr->books[sortArr[i]]->getCost() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getWholesale() << "   ";
			cout << invptr->books[sortArr[i]]->getStock() << std::endl;
		}
	}

	else // normal page display if user chose any page before last
	{
		for (int i = 10; i >= 1; i--)
		{
			cout << setw(25) << left << invptr->books[sortArr[(10 * pages) - i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getPub() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getWholesale() << "   ";
			cout << invptr->books[sortArr[(10 * pages) - i]]->getStock() << std::endl;
		}
	}
}

void Report::reportRetailValue() // entire retail + retail
{
	double total = totalRetailValue();
	std::cout << "The total Retail Value of the inventory is: " << total << ".\n";

	// inventory output
	int pages = 0;
	if (invptr->bookCount % 10 == 0) // book count is divisible by 10
		pages = invptr->bookCount / 10;
	else pages = (invptr->bookCount / 10) + 1; // add extra page for remainder

	cout << "There are " << pages << " in your Inventory." << std::endl;
	cout << "View Page: ";
	cin >> pages;

	cout << setw(30) << "Page " << pages << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;
	cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(5) << "Price" << setw(5) << "Stock" << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;

	if (10 * pages > invptr->bookCount) // book count is not divisible by 10 and user chose last page
	{
		int diff = invptr->bookCount - (10 * (pages - 1));
		for (int i = invptr->bookCount - diff; i < invptr->bookCount; i++)
		{
			cout << setw(25) << left << invptr->books[sortArr[i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getPub() << "   ";
			//cout << setw(15) << invptr->books[sortArr[i]]->getPrice() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getRetail() << "   ";
			cout << invptr->books[sortArr[i]]->getStock() << std::endl;
		}
	}

	else // normal page display if user chose any page before last
	{
		for (int i = 10; i >= 1; i--)
		{
			cout << setw(25) << left << invptr->books[sortArr[(10 * pages) - i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getPub() << "   ";
			cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getRetail() << "   ";
			cout << invptr->books[sortArr[(10 * pages) - i]]->getStock() << std::endl;
		}
	}
}

void Report::reportWholeSaleValue() // entire wholesale + wholesale
{
	double total = totalWholesaleValue();
	std::cout << "The total Wholesale Value of the inventory is: " << total << ".\n";
	// inventory output
	reportWholesale();
}

//	age is yyyyymmdd:	20180103	20180130
void Report::sortByAge()
{
	//const int count = invptr->bookCount;
	//int* ageArr[count];
	//Book** ageBooks = new Book*[invptr->bookCount];

	int** ageArr = new int*[invptr->bookCount];
	for (int i = 0; i < invptr->bookCount; i++)
		*ageArr[i] = stoi(invptr->books[sortArr[i]]->getDate());
		//*ageArr[i] = invptr->books[i]->getDate();

	sort(ageArr);
	
	//reportAge(&ageArr);
	for (int i = 0; i < invptr->bookCount; i++)
		delete ageArr[i];
	delete[] ageArr;
}

void Report::sortByQuantity()
{
	//int* quantityArr[invptr->bookCount];
	int** quantityArr = new int*[invptr->bookCount];

	for (int i = 0; i < invptr->bookCount; i++)
		*quantityArr[i] = invptr->books[sortArr[i]]->getStock();

	sort(quantityArr);
	for (int i = 0; i < invptr->bookCount; i++)
		delete quantityArr[i];
	delete[] quantityArr;
}

void Report::sortByRetailValue()
{
	//int* retailArr[invptr->bookCount];
	double** retailArr = new double*[invptr->bookCount];

	for (int i = 0; i < invptr->bookCount; i++)
		*retailArr[i] = invptr->books[sortArr[i]]->getRetail();

	sort(retailArr);
	for (int i = 0; i < invptr->bookCount; i++)
		delete retailArr[i];
	delete[] retailArr;
}

void Report::sortByWholesaleValue()
{
	int tempint = invptr->bookCount;

	//int* wholesaleArr[invptr->bookCount];
	double** wholesaleArr = new double*[invptr->bookCount];

	for (int i = 0; i < invptr->bookCount; i++)
		*wholesaleArr[i] = invptr->books[sortArr[i]]->getWholesale();

	sort(wholesaleArr);
	for (int i = 0; i < invptr->bookCount; i++)
		delete wholesaleArr[i];
	delete[] wholesaleArr;
}

double Report::totalRetailValue()
{
	double total=0.00;

	for (int i = 0; i < invptr->bookCount; i++) {
		total+= invptr->books[sortArr[i]]->getRetail();
	}

	return total;
}

double Report::totalWholesaleValue()
{
	double total = 0.00;

	for (int i = 0; i < invptr->bookCount; i++) {
		total += invptr->books[sortArr[i]]->getWholesale();
	}

	return total;
}
