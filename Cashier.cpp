//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
Cashier::Cashier(/*Inventory *inventory*/Inventory *invptr)
{
    inventory = invptr;
}
//prompt user to select an option, pass to internal menu
//this needs to return type int so we can go back to the base module
int Cashier::displayTopMenu()
{
    int choice = -1;
    while(choice != 0)
    {
    std::cout << "Please select an option below ..." << std::endl;
    std::cout << "[1] Add books to your shopping cart" << std::endl;
    std::cout << "[2] Remove books from your shopping cart" << std::endl;
    std::cout << "[3] View items in your shopping cart" << std::endl;
    std::cout << "[4] Proceed to checkout" << std::endl << std::endl;
    std::cout << "[5] View Inventory" << std::endl << std::endl;
    std::cout << "[0] Go back to main menu" << std::endl << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    displayInternalMenu(choice);
    }
    return choice;
}
void Cashier::displayInternalMenu(int choice)
{
    Book *currentBook = nullptr; //objects deleted in cart, so no need here
    currentBook = new Book;
    string title = "";
    int index = 0;    
    //save the pointer to old book object from getIndex
    //then copy information over to new book, pass new book
    switch (choice)
    {
        case 1:
            inventory->clearBuffer();
            std::cout << "Enter the title of the book from the inventory that you would like to add: ";
            std::getline(cin, title);
            index = inventory->findBookIndex(title);
            if (index != -1){
            currentBook = inventory->getBookByIndex(index);
            std::cout << "Enter the quantity of that book you'd like to add: ";
            std::cin >> quantity;
            shoppingCart.addToCart(currentBook, quantity);
            }
            else cout << "Could not find book in inventory" << endl;
            break;
        case 2:
            inventory->clearBuffer();
            std::cout << "Enter the title of the book from the inventory that you would like to remove: ";
            std::getline(cin, title);
            index = inventory->findBookIndex(title);
            currentBook = inventory->getBookByIndex(index);
            std::cout << "Enter the quantity of that book you'd like to remove: ";
            std::cin >> quantity;
            shoppingCart.removeFromCart(currentBook, quantity);
            break;
        case 3:
            cout << shoppingCart;
            break;
        case 4:
            checkout();
            break;
        case 5:
            inventory->viewInventory();
            break;
        case 0:
            std::cout << "Returning to main menu ..." << std::endl;
            break;
        default:
            std::cout << "Select a valid choice ... " << std::endl;
    }
}

void Cashier::setTax()
{
    tax = shoppingCart.getCartValue() * .065; //CA sales tax is 6.5%
}
void Cashier::setTotal()
{//get retail price of each book with tax, add all books cost
    total = shoppingCart.getCartValue() + getTax();
}
void Cashier::checkout()
{
    setTotal();
    setTax();
    for (int i = 0; i < shoppingCart.getNumItems(); i++)
    {
        if (shoppingCart.getCartInv()[i]->getStock() == 0)
            inventory->deleteBook(shoppingCart.getCartInv()[i]->getTitle());
            inventory->sortInventory();
    }
    printReceipt();
    //delete the cart in case they want to keep shopping
}

double Cashier::getTax() { return tax; }
double Cashier::getTotal() { return total; }

void Cashier::printReceipt()
{
    //once the other stuff is corrected fully this shouldn't be hard to update..
    std::cout << setw(46) << "Copy of receipt" << std::endl << std::endl;
    
    for (int i = 0; i < shoppingCart.getNumItems(); i++)
    {
        cout << shoppingCart.getCartInv()[i]->getTitle() << " : "  << shoppingCart.getQuantityofItem(i) << setw(31) << shoppingCart.getCartInv()[i]->getRetail() * shoppingCart.getQuantityofItem(i)  << std::endl;
    }
    cout << endl << endl;
    std::cout << setw(22) << "Subtotal" << setw(38) << shoppingCart.getCartValue() << endl;
    std::cout << std::endl;
    std::cout << setw(17) << "Tax" << setw(43) << getTax() << std::endl << std::endl;
    std::cout << setw(19) << "Total" << setw(41) << getTotal() << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "\tThanks for shopping at Serendipity Book Store, please come again!" << std::endl;
    
    //end program?
    std::cout << std::endl << std::endl;
    std::cout << "Returning to main menu ..." << std::endl;
}
