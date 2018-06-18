#pragma once
#include <string>
#include "Book.h"

class Cart {
private:
	Book ** shoppingCart; // pointer that will go to an array
	int cartSize;
	int uniqueInCart; // number of unique items in cart - for array sizing
	double cartValue; // total cost of the cart items

	void calcCartVal(double, int); // calculates the new cart value given a price and quantity
	void increaseCartSize(); // private function for making the cart bigger as needed

public:
	Cart(); // default constructor
	Cart(int); // constructor with custom cart size
	~Cart(); // remember to delete items in shoppingCart


	void addToCart(Book *); // should this take an Item object, or should this just be the UI part of add/removing? 
	void removeFromCart(Book *);

	double getCartValue();
};