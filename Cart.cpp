#include <string>
#include "Cart.h"

Cart::Cart() {
	shoppingCart = new Book*[10]; // default size 10?
}

Cart::Cart(int size) {
	shoppingCart = new Book*[size];
	cartSize = size;
}

Cart::~Cart() {
	for (int i = 0; i < cartSize; i++) {
		if (shoppingCart[i] != nullptr) {
			delete shoppingCart[i]; //requires Book deleter
		}
	}

	delete[] shoppingCart;
}

void Cart::addToCart(Book *book) {

	// check if book is in shoppingCart already
	// if it is in cart, increment (item + item)
	// if it isn't, add to the end of the array
	// if shopping cart is too small, double array size


	// First: Check if the book is in shoppingCart
	// If yes, increment (item + item)
	Book *currBook = nullptr;

	// add the value to the cart first
	calcCartVal(book->getRetail(), book->getStock());

	for (int i = 0; i < cartSize; i++) {
		currBook = shoppingCart[i];

		if (*currBook == *book) {
			(*currBook).setStock((*currBook).getStock() + book->getStock());

			delete book; // purpose served, must delete here
			book = nullptr;
			return;
		}
	}

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

void Cart::removeFromCart(Book *book) {
	// check if book is in shoppingCart already
	// if it is in cart, decrement (item - item)
	// if it isn't, do nothing? Exception?

	Book *currBook = nullptr;
	for (int i = 0; i < uniqueInCart; i++) {
		currBook = shoppingCart[i];

		if (*currBook == *book) {
			currBook->setStock(currBook->getStock() - book->getStock());
			if (currBook->getStock() <= 0) {
				delete currBook;
				shoppingCart[i] = nullptr;

				// shifts pointers in cart over
				for (int k = i; k < uniqueInCart - 1; k++) {
					shoppingCart[k] = shoppingCart[k + 1];
					shoppingCart[k + 1] = nullptr;
				}
				uniqueInCart--;
			}

			calcCartVal(book->getRetail(), book->getStock() * -1);

			delete book;
			book = nullptr;
			return;
		}
	}

	throw "Book not in cart";

	// UI, TO BE WRITTEN SOMEWHERE ELSE:
	// display list of Items in shoppingCart by index + 1
	// user inputs number to be deleted
	// if quantity is more than 1, ask for quantity to be deleted
	// 

}

double Cart::getCartValue() {
	return cartValue;
}

Book ** Cart::getCartInv() {
	return shoppingCart;
}

// rather than scan the entire Book array, use this to update value as items are added
void Cart::calcCartVal(double price, int quantity) {
	cartValue += (price * quantity);
}

void Cart::increaseCartSize() {
	Book ** biggerCart;
	biggerCart = new Book*[cartSize * 2];

	// copy pointers from shoppingCart, set shoppingCart pointers to nullptr so when delete Cart is called the books arent deleted
	for (int i = 0; i < cartSize; i++) {
		biggerCart[i] = shoppingCart[i];
		shoppingCart[i] = nullptr;
	}

	delete[] shoppingCart;
	shoppingCart = biggerCart; // shoppingCart now points to the bigger array
	cartSize *= 2; // update size
}