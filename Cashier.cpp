//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
Cashier::Cashier(/*Inventory *inventory*/Module *module)
{
	char viewInv;

	std::cout << "Selected the Cashier Module" << std::endl << std::endl;

	std::cout << "In this module you can select books to add to your shopping cart for purchase."
		<< std::endl;
	std::cout << "Once you have all the desired books in your cart you can proceed to checkout."
		<< std::endl << std::endl;

	//allow user to browse inventory
	std::cout << "Would  you like to view the inventory? (Y/N): " << std::endl;
	std::cin >> viewInv;

	std::cout << std::endl;
	if (viewInv == 'Y' || viewInv == 'y')
	{
		std::cout << std::endl << "Viewing inventory ..." << std::endl;
		inventory->viewInventory();
	}
}
//prompt user to select an option, pass to internal menu
//this needs to return type int so we can go back to the base module
void Cashier::displayTopMenu()
{
	int choice = -1;
	std::cout << "Please select an option below ..." << std::endl;
	std::cout << "[1] Add books to your shopping cart" << std::endl;
	std::cout << "[2] Remove books from your shopping cart" << std::endl;
	std::cout << "[3] View items in your shopping cart" << std::endl;
	std::cout << "[4] Proceed to checkout" << std::endl << std::endl;
	std::cout << "[0] Go back to main menu" << std::endl << std::endl;
	std::cout << "Choice: ";
	std::cin >> choice;

	while (choice < 0 || choice > 4)
	{
		std::cout << "Select a valid choice from the menu ..." << std::endl;
		std::cin >> choice;
	}
	displayInternalMenu(choice);
}
void Cashier::displayInternalMenu(int choice)
{
	Book *currentBook = nullptr; //objects deleted in cart, so no need here
	currentBook = new Book;
	int index = 0;
	currentBook = inventory->getBookByIndex(index);

	//save the pointer to old book object from getIndex
	//then copy information over to new book, pass new book
	switch (choice)
	{
	case 1:
		std::cout << "Enter the index of the book from the inventory that you would like to add: ";
		std::cin >> index;
		std::cout << "Enter the quantity of that book you'd like to add: ";
		std::cin >> quantity;
		shoppingCart.addToCart(currentBook);
		displayTopMenu();
		break;
	case 2:
		std::cout << "Enter the index of the book from the inventory that you would like to remove: ";
		std::cin >> index;
		std::cout << "Enter the quantity of that book you'd like to remove: ";
		std::cin >> quantity;
		shoppingCart.removeFromCart(currentBook);
		displayTopMenu();
		break;
	case 3:
		std::cout << "Here is your shopping cart ..." << std::endl;
		currentBook = *shoppingCart.getCartInv();
		std::cout << currentBook;
		displayTopMenu();
		break;
	case 4:
		checkout();
		break;
	case 0:
		std::cout << "Returning to main menu ..." << std::endl;
		break;
	default:
		std::cout << "Select a valid choice ... " << std::endl;
		displayTopMenu();
	}
}
void Cashier::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void Cashier::setTax(double tax)
{
	tax = total * .065; //CA sales tax is 6.5%
	this->tax = tax;
}
void Cashier::setTotal(double total)
{//get retail price of each book with tax, add all books cost
	this->total = total;
	total = shoppingCart.getCartValue() + tax;
}
void Cashier::deleteFromInv()
{
	string title = book.getTitle();
	inventory->deleteBook(title);
}
void Cashier::checkout()
{
	string title = book.getTitle();
	//use the findBookIndex from inventory to find the books we're grabbing
	inventory->findBookIndex(title);

	//remove whatever books they purchase from inventory
	while (inventory->isInStock(title))
	{
		if (book.getStock() == 1)
			deleteFromInv();
		else if (book.getStock() > 1)
			book.operator--(quantity);
	}
	printReceipt();
	//delete the cart in case they want to keep shopping
}
int Cashier::getQuantity() { return quantity; }
double Cashier::getTax() { return tax; }
double Cashier::getTotal() { return total; }

void Cashier::printReceipt()
{
	//once the other stuff is corrected fully this shouldn't be hard to update..
	std::cout << setw(46) << "Copy of receipt" << std::endl << std::endl;

	std::cout << setw(29) << "Book title here" << setw(31) << book.getRetail() << std::endl;
	std::cout << setw(29) << "Book title here" << setw(31) << book.getRetail() << std::endl << std::endl;
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
