//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
//Cashier::Cashier(Module *module)
//{
//	module = inventory;
//}
Cashier::Cashier(Inventory *inventory)
{
	this->inventory = inventory;
	//char viewInv;
	////allow user to browse inventory
	//std::cout << "Would  you like to view the inventory? (Y/N): " << std::endl;
	//std::cin >> viewInv;

	//std::cout << std::endl;
	//if (viewInv == 'Y' || viewInv == 'y')
	//{
	//	std::cout << std::endl << "Viewing inventory ..." << std::endl;
	//	inventory->viewInventory();
	//}
}
//prompt user to select an option, pass to internal menu
//this needs to return type int so we can go back to the base module
int Cashier::displayTopMenu()
{
	int choice = -1;
	std::cout << setw(20) << "-- Cashier --" << std::endl;
	std::cout << "[1] -- Add books to your shopping cart" << std::endl;
	std::cout << "[2] -- Remove books from your shopping cart" << std::endl;
	std::cout << "[3] -- View items in your shopping cart" << std::endl;
	std::cout << "[4] -- Proceed to checkout" << std::endl << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "[0] -- Go back to main menu" << std::endl << std::endl;
	std::cout << "Option: ";
	std::cin >> choice;

	while (choice < 0 || choice > 4)
	{
		std::cout << "Select a valid choice from the menu ..." << std::endl;
		std::cout << "Option: ";
		std::cin >> choice;
	}
	displayInternalMenu(choice);
	return NULL;
}
int Cashier::displayInternalMenu(int choice)
{
	//save the pointer to old book object from getIndex
	//then copy information over to new book, pass new book
	Book *currentBook = nullptr; //objects deleted in cart, so no need here
	currentBook = new Book;
	int index = 0;

	switch (choice)
	{
	case 1:
		//shoppingCart.increaseCartSize();
		std::cout << "Enter the index of the book that you would like to add: ";
		std::cin >> index;
		currentBook->setTitle(inventory->getBookByIndex(index)->getTitle());
		std::cout << "Enter the quantity of that book you'd like to add: ";
		std::cin >> quantity;
		currentBook->setStock(quantity);
		shoppingCart.addToCart(currentBook);
		displayTopMenu();
		break;
	case 2:
		std::cout << "Enter the index of the book from the inventory that you would like to remove: ";
		std::cin >> index;
		currentBook->setTitle(inventory->getBookByIndex(index)->getTitle());
		std::cout << "Enter the quantity of that book you'd like to remove: ";
		std::cin >> quantity;
		currentBook->setStock(quantity);
		shoppingCart.removeFromCart(currentBook);
		displayTopMenu();
		break;
	case 3:
		std::cout << "Here is your shopping cart ..." << std::endl;
		shoppingCart.getCartInv();
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
	return NULL;
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
