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
	sortArr = new int[invptr->booksPossible];
}

Report::~Report()
{
	delete[] sortArr;
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
			throw string ("Input is invalid. Please try again with an integer value.\n\n");
			input = -1;
		}

		if (input > 6 || input < 0 && errorNonInt == false) {	// catch input out of range -- change 6 to max number of options
			throw string ("invalid number input out of range.\n");
			input = -1;
		}
	} catch (string msg) {		//interpret exception from char string passed
		std::cout << "Error: " << msg << std::endl;
		errorNonInt = false;	// reset now that we've dealt with the error
	}

	return input;
}

void Report::displayInternalMenu(int input)
{
	for (int i = 0; i < invptr->bookCount; i++) {
		sortArr[i] = i;
	}

	switch (input) {
	case 1:
		reportList();			// default sort is unsorted
		break;
	case 2:
		sortByWholesaleValue();	// Inventory Wholesale Value
		reverseSort();
		reportWholeSaleValue();
		break;
	case 3:
		sortByRetailValue();	// Inventory Retail Value
		reverseSort();
		reportRetailValue();
		break;
	case 4:
		sortByQuantity();		// List by Quantity
		reverseSort();
		reportList();
		break;
	case 5:
		sortByWholesaleValue();	// List by Cost
		reverseSort();
		reportWholesale();
		break;
	case 6:
		sortByAge();			// List by Age	
		reportAge();
		break;
	}
}

int Report::displayTopMenu()
{
	int input;
	do {
		std::cout << std::endl;
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
	return NULL;
}

template<typename TYPE>
void Report::sort(TYPE **arr)
{
	const int count = invptr->bookCount - 1;

	int i, j, low;
	for (i = 0; i < count; i++) {
		low = i;
		for (j = i + 1; j < count; j++) {
			if (*arr[j] < *arr[low]) { low = j; }
		}
		TYPE *temp = arr[low];
		arr[low] = arr[i];
		arr[i] = temp;

		int tempi = sortArr[low];
		sortArr[low] = sortArr[i];
		sortArr[i] = tempi;
	}
}

void Report::reverseSort()
{
	const int arraylength = invptr->bookCount - 1;
	for (int i = 0; i < (arraylength / 2); i++) {
		int temp = sortArr[i];
		sortArr[i] = sortArr[(arraylength - 1) - i];
		sortArr[(arraylength - 1) - i] = temp;
	}
}

void Report::reportList() // quantity
{
	// inventory output
	int pages = 0;
	if (invptr->bookCount % 10 == 0) // book count is divisible by 10
		pages = invptr->bookCount / 10;
	else pages = (invptr->bookCount / 10) + 1; // add extra page for remainder

	std::cout << "There are " << pages << " pages in your Inventory." << endl;
	std::cout << "View Page: ";
	std::cin >> pages;

	std::cout << "Page " << pages << endl;
	std::cout << "---------------------------------------------------------------------" << endl;
	std::cout << left << setw(27) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(15) << "Stock" << endl;
	std::cout << "---------------------------------------------------------------------" << endl;

	if (10 * pages > invptr->bookCount) // bookc count is not divisible by 10 and user chose last page
	{
		int diff = invptr->bookCount - (10 * (pages - 1));
		for (int i = invptr->bookCount - diff; i < invptr->bookCount; i++)
		{
			std::cout << left << setw(25) <<invptr->books[sortArr[i]]->getTitle() << "   ";
			std::cout << setw(15) <<invptr->books[sortArr[i]]->getAuthor() << "   ";
			std::cout << setw(15) <<invptr->books[sortArr[i]]->getPub() << "   ";
			std::cout << invptr->books[sortArr[i]]->getStock() << endl;
		}
	}

	else // normal page display if user chose any page before last
	{
		for (int i = 10; i >= 1; i--)
		{
			std::cout << left << setw(25) << invptr->books[sortArr[(10 * pages) - i]]->getTitle() << "   ";
			std::cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getAuthor() << "   ";
			std::cout << setw(15) << invptr->books[sortArr[(10 * pages) - i]]->getPub() << "   ";
			std::cout << invptr->books[sortArr[(10 * pages) - i]]->getStock() << endl;
		}
	}
}

void Report::reportAge()
{
	int pages = 0;
	if (invptr->bookCount % 10 == 0) // book count is divisible by 10
		pages = invptr->bookCount / 10;
	else pages = (invptr->bookCount / 10) + 1; // add extra page for remainder

	cout << "There are " << pages << " pages in your Inventory." << std::endl;
	cout << "View Page: ";
	cin >> pages;

	cout << setw(30) << "Page " << pages << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;
	cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(15) << "Date Added" << setw(15) << "Stock" << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;

	if (10 * pages > invptr->bookCount) // book count is not divisible by 10 and user chose last page
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

	cout << "There are " << pages << " pages in your Inventory." << std::endl;
	cout << "View Page: ";
	cin >> pages;

	cout << setw(30) << "Page " << pages << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;
	cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(15) << "Cost" << setw(5) << "Stock" << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;

	if (10 * pages > invptr->bookCount) // book count is not divisible by 10 and user chose last page
	{
		int diff = invptr->bookCount - (10 * (pages - 1));
		for (int i = invptr->bookCount - diff; i < invptr->bookCount; i++)
		{
			cout << setw(25) << left << invptr->books[sortArr[i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getPub() << "   ";
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
	std::cout << std::endl;
	std::cout << setprecision(2) << fixed << "The total Retail Value of the inventory is: $" << total << ".\n";

	// inventory output
	int pages = 0;
	if (invptr->bookCount % 10 == 0) // book count is divisible by 10
		pages = invptr->bookCount / 10;
	else pages = (invptr->bookCount / 10) + 1; // add extra page for remainder

	cout << "There are " << pages << " pages in your Inventory." << std::endl;
	cout << "View Page: ";
	cin >> pages;

	cout << setw(30) << "Page " << pages << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;
	cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(15) << "Price" << setw(5) << "Stock" << std::endl;
	cout << "----------------------------------------------------------------" << std::endl;

	if (10 * pages > invptr->bookCount) // book count is not divisible by 10 and user chose last page
	{
		int diff = invptr->bookCount - (10 * (pages - 1));
		for (int i = invptr->bookCount - diff; i < invptr->bookCount; i++)
		{
			cout << setw(25) << left << invptr->books[sortArr[i]]->getTitle() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getAuthor() << "   ";
			cout << setw(15) << invptr->books[sortArr[i]]->getPub() << "   ";
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
	std::cout << std::endl;
	std::cout << setprecision(2) << fixed << "The total Wholesale Value of the inventory is: $" << total << ".\n";
	// inventory output
	reportWholesale();
}

//	age is yyyyymmdd:	20180103	20180130
void Report::sortByAge()
{
	const int count = invptr->bookCount - 1;

	int** ageArr = new int*[count];
	for (int i = 0; i < count; i++) {
		ageArr[i] = new int;
		std::string temp = invptr->books[sortArr[i]]->getDate();
		*ageArr[i] = std::stoi(temp);
	}

	sort(ageArr);
	
	for (int i = 0; i < count; i++)
		delete ageArr[i];
	delete[] ageArr;
}

void Report::sortByQuantity()
{
	int** quantityArr = new int*[invptr->bookCount];

	for (int i = 0; i < invptr->bookCount; i++) {
		quantityArr[i] = new int;
		*quantityArr[i] = invptr->books[sortArr[i]]->getStock();
	}

	sort(quantityArr);
	for (int i = 0; i < invptr->bookCount; i++)
		delete quantityArr[i];
	delete[] quantityArr;
}

void Report::sortByRetailValue()
{
	double** retailArr = new double*[invptr->bookCount];

	for (int i = 0; i < invptr->bookCount; i++) {
		retailArr[i] = new double;
		*retailArr[i] = invptr->books[sortArr[i]]->getRetail();
	}

	sort(retailArr);
	for (int i = 0; i < invptr->bookCount; i++)
		delete retailArr[i];
	delete[] retailArr;
}

void Report::sortByWholesaleValue()
{
	int tempint = invptr->bookCount;

	double** wholesaleArr = new double*[invptr->bookCount];

	for (int i = 0; i < invptr->bookCount; i++) {
		wholesaleArr[i] = new double;
		*wholesaleArr[i] = invptr->books[sortArr[i]]->getWholesale();
	}

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
