//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
Cashier::Cashier(Inventory *inventory)
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

//Cashier::Cashier(int quantity, double tax, double total)
//{
//	this->quantity = quantity;
//	this->tax = tax;
//	this->total = total;
//}

//prompt user to select an option, pass to internal menu
void Cashier::displayTopMenu()
{
	int choice = -1;
	std::cout << "Please select an option below ..." << std::endl;
	std::cout << "[1] Add books to your shopping cart" << std::endl;
	std::cout << "[2] Remove books from your shopping cart" << std::endl;
	std::cout << "[3] View items in your shopping cart" << std::endl;
	std::cout << "[4] Proceed to checkout" << std::endl;
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
	//Book *currentBook = nullptr;
	string title = book.getTitle();
	cin.ignore();
	switch (choice)
	{
	case 1:
		std::cout << "Enter the title of the book you would like to add: ";
		getline(cin, title);
		std::cout << "Enter the quantity of " << title << " you'd like to add: ";
		std::cin >> quantity;
		//shoppingCart.addToCart(currentBook);
		//shoppingCart.getCartValue();
		displayTopMenu();
		break;
	case 2:
		std::cout << "Enter the title of the book you would like to remove: ";
		std::cin >> title;
		std::cout << "Enter the quantity of " << title << " you'd like to remove: ";
		std::cin >> quantity;
		//shoppingCart.removeFromCart(currentBook);
		displayTopMenu();
		break;
	case 3:
		std::cout << "Here is your shopping cart ..." << std::endl;
		//viewCart(shoppingCart);
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
	//delete currentBook;
}
void Cashier::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void Cashier::setTax(double tax)
{
	this->tax = tax;
	//this will be a constant?
}
void Cashier::setTotal()
{
	double total = shoppingCart.getCartValue() + tax;
	//get retail price of each book with tax, add all books cost
}
void Cashier::deleteFromInv()
{
	string title = book.getTitle();
	inventory->deleteBook(title);
}
void Cashier::viewCart()
{
	//function to show shopping cart?
}
void Cashier::checkout()
{
	//use the getBookInfo from inventory to find the books we're grabbing
	inventory->getBookInfo(book.getTitle());

	//remove whatever books they purchase from inventory
	deleteFromInv();
	printReceipt();
}
int Cashier::getQuantity() { return quantity; }
double Cashier::getTax() { return tax; }
double Cashier::getTotal() { return total; }

void Cashier::printReceipt()
{
	//once the other stuff is corrected fully this shouldn't be hard to update..
	std::cout << setw(46) << "Copy of receipt" << std::endl << std::endl;

	std::cout << setw(29) << "Book title here" << setw(31) << /*book.getRetail()*/ "10.99" << std::endl;
	std::cout << setw(29) << "Book title here" << setw(31) << /*book.getRetail()*/ "9.99" << std::endl << std::endl;
	std::cout << setw(22) << "Subtotal" << setw(38) << /*shoppingCart.getCartValue()*/ "20.98" << endl;
	std::cout << std::endl;
	std::cout << setw(17) << "Tax" << setw(43) << /*getTax() */ "5.00" << std::endl << std::endl;
	std::cout << setw(19) << "Total" << setw(41) << /*getTotal()*/ "25.95" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\tThanks for shopping at Serendipity Book Store, please come again!" << std::endl;

	//end program?
	std::cout << std::endl << std::endl;
	std::cout << "Returning to main menu ..." << std::endl;
}
