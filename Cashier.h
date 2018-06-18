#pragma once
// Cashier.h
#ifndef Cashier_h
#define Cashier_h

#include "Book.h"
#include "Inventory.h"
#include "Cart.h"

class Cashier
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
	Cashier(Inventory *);
	Cashier(int, double, double);

	void displayTopMenu(); //to show first menu
	void displayInternalMenu(int); //to show next menu for more interactions
	void setQuantity(int);
	void setTax(double);
	void setTotal(Cart);
	void deleteFromInv(Book);
	int getQuantity();
	double getTax();
	double getTotal();

	void viewCart(Cart);
	void checkout();
	void printReceipt();
};

#endif //Cashier_h
