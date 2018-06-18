// Cashier.h
#ifndef CASHIER_H
#define CASHIER_H

#include "Book.h"
#include "Inventory.h"
#include "Cart.h"
//#include "Item.h"

class Cashier
{
private:
	int quantity;
	double tax;
	double total;
	Book book;
	Inventory inventory;
	Cart shoppingCart;
public:
	//constructor here
	Cashier();
	Cashier(int, double, double);

	void displayTopMenu(Inventory); //to show first menu
	void displayInternalMenu(); //to show next menu for more interactions
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

#endif
