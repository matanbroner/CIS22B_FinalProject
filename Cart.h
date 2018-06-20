#pragma once
#include <string>
#include "Book.h"

class Cart;
ostream& operator<<(ostream&, Cart&);
class Cart {
private:
    Book *shoppingCart[100]; // pointer that will go to an array
    int cartSize;
    int uniqueInCart; // number of unique items in cart - for array sizing
    double cartValue = 0; // total cost of the cart items
    int quantities[100];
    
    void calcCartVal(double, int); // calculates the new cart value given a price and quantity
    
public:
    Cart(); // default constructor
    Cart(int); // constructor with custom cart size
    ~Cart(); // remember to delete items in shoppingCart
    
    void addToCart(Book *, int);
    void removeFromCart(Book *, int);
    
    Book** getCartInv();
    
    double getCartValue();
    int getNumItems();
    int getQuantityofItem(int);
    void shiftCart(int);
    void cleanCart();
    
    friend ostream& operator<<(ostream&, Cart&);
};
