#include <string>
#include "Cart.h"

Cart::Cart() {
    uniqueInCart = 0;
}

Cart::~Cart()
{
}

void Cart::addToCart(Book *book, int quantity) {
    
    // check if book is in shoppingCart already
    // if it is in cart, increment (item + item)
    // if it isn't, add to the end of the array
    // if shopping cart is too small, double array size
    
    
    // First: Check if the book is in shoppingCart
    // If yes, increment (item + item)
    Book *currBook = nullptr;
    // add the value to the cart first
    calcCartVal(book->getRetail(), quantity);
    
    for (int i = 0; i < uniqueInCart; i++) {
        currBook = shoppingCart[i];
        
        if (currBook == book && quantity < book->getStock() && quantity > 0)
        {
            quantities[i] += quantity;
            cout << quantities[i];
            book->setStock(book->getStock() - quantity);
            return;
        }
        else if (currBook == book && quantity == book->getStock())
        {
            book->setStock(0);
            quantities[i] += quantity;
        }
        else if (currBook == book && quantity > book->getStock())
        {
            if (book->getStock() == 0)
                cout << "There are 0 copies of this book on the shelf at the moment..." << endl;
            else
            {
            cout << "You are attempting to purchase more copies than are availible, adding all availible copies to your cart..." << endl;
            quantities[i] +=  book->getStock();
            book->setStock(0);
            }
        }
        else if (currBook == book && quantity == 0)
            cout << "Okay... purchasing an entire 0 books..." << endl;
    }
    
    // If no, check cart space
    if (uniqueInCart == 100) {
        cout << "Cart capacity reached..." << endl;
    }
    else
    {
    // Then add book to the end of the array
    shoppingCart[uniqueInCart] = book;
    quantities[uniqueInCart] = 0;
    if (quantity < book->getStock() && quantity > 0)
        quantities[uniqueInCart] = quantity;
    else if (quantity == book->getStock())
    {
        quantities[uniqueInCart] = quantity;
        book->setStock(0);
    }
    else if (quantity > book->getStock())
    {
        cout << "You are attempting to purchase more copies than are availible, adding all availible copies to your cart..." << endl;
        quantities[uniqueInCart] +=  book->getStock();
        book->setStock(0);
    }
    else if (quantity == 0)
        cout << "Okay... purchasing an entire 0 books..." << endl;
    
    uniqueInCart++;
    }
    
    // UI, TO BE WRITTEN SOMEWHERE ELSE:
    // display list of Items in Inventory by index + 1
    // user inputs number to be added
    // if quantity is more than 1, ask for quantity to be added
    
}

void Cart::removeFromCart(Book *book, int quantity)
{
    bool found = false;
    // check if book is in shoppingCart already
    // if it is in cart, decrement (item - item)
    // if it isn't, do nothing? Exception?
    
    Book *currBook = nullptr;
    for (int i = 0; i < uniqueInCart; i++)
    {
        currBook = shoppingCart[i];
        if (currBook == nullptr)
            shiftCart(i);
        if (currBook == book)
        {
            found = true;
            if (quantity == int(quantities[i]))
            {
                book->setStock(book->getStock() + quantities[i]);
                shoppingCart[i] = nullptr;
                quantities[i] = 0;
            }
            else if (quantity < quantities[i])
            {
                book->setStock(book->getStock() + quantity);
                quantities[i] -= quantity;
            }
            else if (quantity > quantities[i])
            {
                cout << "You don't have that many copies... removing book from cart completely." << endl;
                book->setStock(book->getStock() + quantities[i]);
                quantities[i] = 0;
                shoppingCart[i] = nullptr;
            }
            // shifts pointers in cart over
            if (quantities[i] == 0)
            {
                shiftCart(i);
            }
        }
            
            calcCartVal(book->getRetail(), (quantities[i] * -1));
    }
    if (found == false)
        cout << "Book not found in your cart..." << endl;
    return;
}

    
    // UI, TO BE WRITTEN SOMEWHERE ELSE:
    // display list of Items in shoppingCart by index + 1
    // user inputs number to be deleted
    // if quantity is more than 1, ask for quantity to be deleted
    //


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

int Cart::getNumItems(){return uniqueInCart;}
int Cart::getQuantityofItem(int i){return quantities[i];

}
ostream& operator<<(ostream& strm, Cart &c)
{
    strm << "     -- You Cart --     " << endl << endl;
    for (int i = 0; i < c.uniqueInCart; i++)
    {
        strm << i+1 << ". " << c.shoppingCart[i]->getTitle() << ":    " << c.quantities[i] << endl;
    }
    return strm;
}

void Cart:: shiftCart(int i)
{
    for (int k = i; k < uniqueInCart - 1; k++)
    {
        quantities[k] = quantities[k+1];
        shoppingCart[k] = shoppingCart[k + 1];
        shoppingCart[k + 1] = nullptr;
    }
    uniqueInCart--;
}

void Cart::cleanCart()
{
    for (int i = 0; i < uniqueInCart-1; i++)
    {
        shoppingCart[i] = nullptr;
    }
    uniqueInCart = 0;
}
