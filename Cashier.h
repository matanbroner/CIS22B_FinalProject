#pragma once
// Cashier.h
#ifndef Cashier_h
#define Cashier_h

#include "Book.h"
#include "Inventory.h"
#include "Cart.h"

class Cashier : public Module
{
private:
	int quantity;
	double tax;
	double total;
	Book book;
	Inventory *inventory;
	Cart shoppingCart;
public:
	//constructor here
	Cashier(Module *);
	//Cashier(Inventory *);
	int displayTopMenu(); //to show first menu
	int displayInternalMenu(int); //to show next menu cart/checkout interactions
	void setQuantity(int);
	void setTax(double);
	void setTotal(double);
	void deleteFromInv();
	int getQuantity();
	double getTax();
	double getTotal();

	void checkout();
	void printReceipt();
};

#endif //Cashier_h
