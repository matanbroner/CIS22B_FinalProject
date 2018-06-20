/*
Author: Timo Bitterli
File: Report.h
Last edit: 6/18/2018
Class Report to display to user user specified total and or user specified type of sort sorted inventory.
More details on functions:

char[10],	string,	string,	string,		char[8],	int,		double,	double
isbn,		title,	author,	publisher,	date,		quantity,	cost,	saleprice

void reportList();
Inventory List	A list of information on all books in the inventory.

void sortByWholesaleValue();
int totalWholesaleValue();
void reportWholeSaleValue();
Inventory Wholesale Value	A list of the wholesale value of all books in the
inventory and	the total wholesale value of the inventory.

void sortyByRetailValue();
int totalRetailValue();
void reportRetailValue();
Inventory Retail Value		A list of the retail value of all books in the inventory
and the		total retail value of the inventory.

void sortByQuantity();
void reportList();
List by Quantity			A list of all books in the inventory sorted by quantity on hand.
The books with the greatest quantity on hand will be listed first.

void sortByWholesaleValue();
void reportWholesale()
List by Cost			A list of all books in the inventory, sorted by wholesale cost.The
books with the greatest wholesale cost will be listed first.

void sortByAge();
void reportList();
List by Age				A list of all books in the inventory, sorted by purchase date.The
books that have been in the inventory longest will be listed first.
*/

#ifndef REPORT_H
#define REPORT_H
#include "Inventory.h"				// has book.h
#include "Module.h"

class Report :
	public Module
{
private:
	Inventory* invptr;
	int* sortArr;

public:
	//Report();						// no default constructor, needs inventory
	Report(Inventory*);				// books are private in inventory (contains array of book objects)
	~Report();

	int getUserInput();
	void displayInternalMenu(int);
	int displayTopMenu();

	template<typename TYPE>
	void sort(TYPE**);				// sorts list if type is compatible with < operator

	void reverseSort();

	void reportList();				// output inventory list as is
	void reportAge();				// Inventory::viewInventory with Age
	void reportWholesale();			// Inventory::viewInventory with WholeSale

	void reportRetailValue();		// reportlist() modified with int totalRetailValue();
	void reportWholeSaleValue();	// reportWholesale() modified with int totalWholesaleValue();

	void sortByAge();				// string
	void sortByQuantity();			// int
	void sortByRetailValue();		// double
	void sortByWholesaleValue();	// double

	double totalRetailValue();		// double
	double totalWholesaleValue();	// double
};

#endif
