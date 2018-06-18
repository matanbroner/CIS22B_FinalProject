//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
Cashier::Cashier()
{
	std::cout << "Cashier module constructor ..." << std::endl;
}

Cashier::Cashier(int quantity, double tax, double total)
{
	this->quantity = quantity;
	this->tax = tax;
	this->total = total;
}

//user can add books to shopping cart then check out
void Cashier::displayTopMenu(Inventory inventory)
{
	char viewInv;
	string title;

	//read booklist from file
	//create instance of shopping cart object
	std::cout << "Selected the Cashier Module" << std::endl << std::endl;

	std::cout << "In this module you can select books to add to your shopping cart for purchase." 
		<< std::endl;
	std::cout << "Once you have all the desired books in your cart you can proceed to checkout."
		<< std::endl << std::endl;

	//allow user to browse inventory
	std::cout << "Would  you like to view the inventory? (Y/N): " << std::endl;
	std::cin >> viewInv;
	if (viewInv == 'Y' || viewInv == 'y')
	{
		inventory.viewInventory();
	}

	int choice = -1; //choice will read invalid so user can select from menu below

	std::cout << "Please select an option below ..." << std::endl;
	std::cout << "1. Add books to your shopping cart" << std::endl;
	std::cout << "2. Remove books from your shopping cart" << std::endl;
	std::cout << "3. View items in your shopping cart" << std::endl;
	std::cout << "4. Proceed to checkout" << std::endl;
	std::cout << "0. Go back to main menu" << std::endl << std::endl;
	std::cout << "Enter your choice: ";
	cin >> choice;

	return choice;
}

//end displayTopMenu -- send to displayInternalMenu
void Cashier::displayInternalMenu()
{
	displayTopMenu();
	char input = 'y'; //to start while loops
	while (choice != 1 || choice != 2 || choice != 3 || choice != 4 || choice != 0)
	{
		std::cout << "Please select to add to your cart or proceed to checkout." << std::endl;
		cin >> choice;
	}
	if (choice == 1) //add items to users shopping cart
	{
		while (input = 'Y' || input = 'y')
		{
			std::cout << "Enter the title of the book you would like to add: ";
			std::cin >> title;
			std::cout << "Enter the quantity of " << title << " you'd like to add: ";
			std::cin >> quantity;
			std::cout << std::endl << std::endl;
			std::cout << "Do you have more books to add? (Y/N): ";
			std::cin >> input;
		}
		//function to add the book + quantity of it to shopping cart
		std::cout << "Adding book(s) and quantity to shopping cart ..." << std::endl;
	}
	else if (choice == 2) //remove item from users shopping cart
	{
		while (input = 'Y' || input = 'y')
		{
			std::cout << "Enter the title of the book you would like to remove: ";
			std::cin >> title;
			std::cout << "Enter the quantity of " << title << " you'd like to remove: ";
			std::cin >> quantity;
			std::cout << std::endl << std::endl;
			std::cout << "Do you have more books to remove? (Y/N): ";
			std::cin >> input;
		}
		//function to remove the book + quantity of it to shopping cart
		std::cout << "Removing book(s) and quantity to shopping cart ..." << std::endl;
	}
	else if (choice == 3) //let user view their shopping cart
	{
		std::cout << "Here is your shopping cart ..." << std::endl;
	}
	else if (choice == 4) //take user to checkout with their shopping
		checkout();
	else //if choice == 0, return to main menu?
	{
		std::cout << "Returning to main menu ..." << std::endl;
	}
}
void Cashier::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void Cashier::setTax(double tax)
{
	this->tax = tax;
}
void Cashier::setTotal(Cart cart)
{
	double total = cart.getCartValue() + tax;
	//get retail price of each book with tax, add all books cost
}
void Cashier::deleteFromInv(Book b)
{
	string title = b.getTitle();
	Inventory.deleteBook(title);
}
void Cashier::viewCart(Cart cart)
{
	//function to show shopping cart?
}
void Cashier::checkout()
{
	//use the getBookInfo from inventory to find the books we're grabbing
	Inventory.getBookInfo();
	//remove whatever books they purchase from inventory
	deleteFromInv(inventory, book);
	printReceipt();
}
int Cashier::getQuantity(){ return quantity; }
double Cashier::getTax() { return tax; }
double Cashier::getTotal() { return total; }

void Cashier::printReceipt()
{
	//once the other stuff is corrected fully this shouldn't be hard to update..
	std::cout << "\t\t Copy of receipt" << std::endl << std::endl;
	std::cout << "Book 1  \t\t" << book.getRetail() << std::endl;
	std::cout << "Book 2  \t\t" << book.getRetail() << std::endl << std::endl;
	std::cout << "Subtotal\t\t" << shoppingCart.getCartValue() << endl;
	std::cout << std::endl;
	std::cout << "Tax     \t\t" << getTax() << std::endl << std::endl;
	std::cout << "Total   \t\t" << getTotal() << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t\tThanks for shopping at Serendipity Book Store, please come again!" << std::endl;
}
