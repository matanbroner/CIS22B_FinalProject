#include <string>
#include "Cart.h"

Cart::Cart() {
	shoppingCart = new Item[10]; // default size 10?
}

Cart::Cart(int size) {
	shoppingCart = new Item[size]; 
	cartSize = size;
}

Cart::~Cart() {
	// TO DO: Item delete
	delete[] shoppingCart;
}

void Cart::addToCart(Item book) {
	
	// check if book is in shoppingCart already
	// if it is in cart, increment (item + item)
	// if it isn't, add to the end of the array
	// if shopping cart is too small, double array size

	// need: comparison, addition operator overload for Items
	

	// First: Check if the book is in shoppingCart
	// If yes, increment (item + item)

	// If no, check cart space
	if (uniqueInCart == cartSize) {
		increaseCartSize();
	}

	// Then add book to the end of the array
	shoppingCart[uniqueInCart] = book;
	uniqueInCart++;




	// UI, TO BE WRITTEN SOMEWHERE ELSE:
	// display list of Items in Inventory by index + 1
	// user inputs number to be added
	// if quantity is more than 1, ask for quantity to be added

}

void Cart::removeFromCart(Item book) {
	// check if book is in shoppingCart already
	// if it is in cart, decrement (item - item)
	// if it isn't, do nothing? Exception?



	// UI, TO BE WRITTEN SOMEWHERE ELSE:
	// display list of Items in shoppingCart by index + 1
	// user inputs number to be deleted
	// if quantity is more than 1, ask for quantity to be deleted
	// 

}

double Cart::getCartValue() {
	return cartValue;
}


// rather than scan the entire Item array, use this to update value as items are added
void Cart::calcCartVal(double price, int quantity) {
	cartValue += (price * quantity);
}

void Cart::increaseCartSize() {
	Item* biggerCart = new Item[cartSize * 2];

	// copy over things from shoppingCart
	for (int i = 0; i < cartSize; i++) {
		biggerCart[i] = shoppingCart[i]; // TODO: Item copy constructor
	}

	delete[] shoppingCart;
	shoppingCart = biggerCart; // shoppingCart now points to the bigger array
	cartSize *= 2; // update size

	// Thoughts:
	// issue: increaseCartSize will be slow because it reconstructs all the Items
	// possible solution: shoppingCart holds pointers to Items 
	// no - because then deleting the shoppingCart won't delete the Items, which we ultimately want
	// in order to delete all Items at the very end of the program

	// solution: leave it as is. Use copy constructor for Item
}