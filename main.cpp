//
//  main.cpp
//  CIS22B_FinalProject
//
//  Created by Matan Broner on 6/5/18.
//	Edited by Timo Bitterli on 6/19/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#include <iostream>
#include "Inventory.h"
#include "Inventory.h"
#include "Report.h"
#include "Module.h"
#include "Cashier.h"

int main(int argc, const char * argv[]) {
	int choice = 0;
	Module *modules[4];
	modules[0] = new Module;

	Inventory *inventoryModuleptr;
	inventoryModuleptr = new Inventory("./datafile.txt");

	modules[1] = inventoryModuleptr;
	modules[2] = new Cashier(inventoryModuleptr);
	modules[3] = new Report(inventoryModuleptr);

	do
	{
		choice = int(modules[0]->displayTopMenu());
		switch (choice)
		{
		case 0:
			cout << "\nThank you for using Serendipity Bookstore's Service,\nHave a Nice Day!\n" << endl;
			break;
		case 1:
			modules[2]->displayTopMenu();
			break; // cashier
		case 2:
			modules[1]->displayTopMenu();
			break;
		case 3:
			modules[3]->displayTopMenu();
			break; // reports
		default:
			cout << "Not valid input..." << endl;
			break;
		}
	} while (choice != 0);

	for (int i = 0; i < 4; i++)
		delete modules[i];

	return 0;
}
