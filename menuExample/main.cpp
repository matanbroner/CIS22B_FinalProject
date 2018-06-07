// main.cpp

//#include "cashier.h"
//#include "inventory.h"
//#include "reports.h"
//#include "item.h"
//#include "cart.h"
//#include etc.
#include "functions.h"

int main()
{
	//cashier *cashier = new cashier;	
	//inventory *inventory = new inventory;
	//reports *report = new report;

	mainMenu(/*references to cashier, inventory, report to call menus*/);	// mainMenu that catches non int and input out of range

	//delete cashier;	
	//delete inventory;
	//delete report;
	return EXIT_SUCCESS;
}
