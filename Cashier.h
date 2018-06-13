// Cashier.h
#ifndef CASHIER_H
#define CASHIER_H

#include "Book.h"
#include "Inventory.h"
#include "Cart.h"
#include "Item.h"

class Cashier
{
private:
	int quantity;
	const static int count = 0; // is this right? to keep track of items in cart
	double tax;
	double total;
	Book* books[count];
	Item items;
	Inventory inventory;
	Cart shoppingCart;
public:
	//constructor here
	Cashier();
	void interact(Inventory);
	void setQuantity(int);
	void setTax(double);
	void setTotal();
	void deleteFromInv(Inventory);

	int getQuantity();
	double getTax();
	double getTotal();

	void checkout();
	void printReceipt();
};

#endif
