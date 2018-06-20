#pragma once
// Cashier.h
#ifndef Cashier_h
#define Cashier_h

#include "Book.h"
#include "Inventory.h"
#include "Cart.h"

using namespace std;
class Cashier : public Module
{
private:
	int quantity;
	double tax;
	double total;
	Book book;
	Inventory* inventory;
	Cart shoppingCart;
public:
	Cashier(Inventory *);

	int displayTopMenu(); //to show first menu
	void displayInternalMenu(int); //to show next menu for more interactions
	void setTax();
	void setTotal();
	double getTax();
	double getTotal();

	void checkout();
	void printReceipt();
};

#endif //Cashier_h
