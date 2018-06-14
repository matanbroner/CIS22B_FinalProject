/*
Current status:

Template sort has been tested. (took me a while to figure out how to make it work...)

Module needs:
friend with inventory books* and friend or public access to Inventory::bookCount
user output displays
some menu work
*/

/*
Author: Timo Bitterli
File: Report.h
Last edit: 6/13/2018
Class Report to display to user user specified total and or user specified type of sort sorted inventory 
*/


// Item is book?
//#include "Item.h"
#include "Inventory.h"	// has book.h
#include "Module.h"

class Report :
	public Module
{
private:
//	template <typename sorts>* arrayOfPointers[Inventory::bookCount];	// this probably wont be usable
	
	Inventory* invptr;

	// ask about making the Inventory::bookCount int public
public:
	//Report();						// no default constructor, needs inventory
	Report(Inventory&);				// books are private in inventory (contains array of book objects)
	~Report();

	int getUserInput();
	void processUserInput(int);		// if plain report, default sort by Author (if made), else Quantity

	void moduleMenu();

	template<typename TYPE>
	void sort(TYPE**/*, Book**/);	// 
// Book* isin: invptr->books[]		// template could sort an array of pointers along side books
										// --since the books still need to be sorted but the types are different
					 				// Age: int *ageptr[Inventory::booksPossible]
									// ageArr[i] = invptr->books[i].getAge();
									// need to put friend class Report in private of Inventory to allow this template sort
									// this would allow: (access too books array)
									// invptr->books[low] = invptr->books[counter];


	void reportList();				// output inventory list as is (to be called after a sort)
//	can call invptr->viewInventory() for default
//	or create a viewFullInventory() in inventory with all stats for default?
	void reportRetailValue();		// reportlist() modified with int totalRetailValue();
	void reportWholeSaleValue();	// reportlist() modified with int totalWholesaleValue();

	void sortByAge();				// char[8]
	// void sortByAuthor();			// string
	void sortByQuantity();			// int
	void sortByRetailValue();		// double
	void sortByWholesaleValue();	// double

	// int totalQuantity();			// int
	double totalRetailValue();		// double
	double totalWholesaleValue();	// double
};

/*
char[10],	string,	string,	string,		char[8],	int,		double,	double
isbn,		title,	author,	publisher,	date,		quantity,	cost,	saleprice
char[10],	string,	string,	string,		char[8],	int,		double,	double


This is here to ensure I don't miss anything

void reportList();
Inventory List	A list of information on all books in the inventory.

void sortByWholesaleValue();
int totalWholesaleValue();
void reportWholeSaleValue();
Inventory Wholesale Value	A list of the wholesale value of all books in the
			inventory and	the total wholesale value of the inventory.

void sortyByRetailValue();
int totalRetailValue();
Inventory Retail Value		A list of the retail value of all books in the inventory
				and the		total retail value of the inventory.

void sortByQuantity();
void reportList();
List by Quantity			A list of all books in the inventory sorted by quantity on hand.
The books with the greatest quantity on hand will be listed first.


void sortByWholesaleValue();
void reportList();
List by Cost			A list of all books in the inventory, sorted by wholesale cost.The
books with the greatest wholesale cost will be listed first.

void sortByAge();
void reportList();
List by Age				A list of all books in the inventory, sorted by purchase date.The
books that have been in the inventory longest will be listed first.
*/
