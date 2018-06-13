//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
Cashier::Cashier()
{
	std::cout << "Welcome to the Cashier module... " << std::endl;
}

void Cashier::interact(Inventory inv) //user can add books to shopping cart then check out
{
	char viewInv;
	//red booklist from file
	//create instance of shopping cart object
	std::cout << "Selected the Cashier Module" << std::endl << std::endl;

	std::cout << "In this module you can select books to add to your shopping cart for purchase." << std::endl;
	std::cout << "Once you have all the desired books in your cart you can proceed to checkout."
	<< std::endl;

	//allow user to browse inventory
	std::cout << "Would  you like to view the inventory? (Y/N): " << std::endl;
	std::cin >> viewInv;
	while (viewInv == 'Y' || viewInv == 'y')
	{
		inv.viewInventory();
	}

	int choice = 0; //for user input, defaulted to 0 to proceed to while loop

	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Add books to your shopping cart" << std::endl;
	std::cout << "2. Remove books from your shopping cart" << std::endl;
	std::cout << "3. Proceed to checkout" << std::endl;
	cin >> choice;

	//haven't tested the loop yet but the idea is to continue to ask the user for
	//input until they select either 1 or 2
	while (choice != 1 || choice != 2 || choice !=3)
	{
	std::cout << "Please select to add to your cart or proceed to checkout." << std::endl;
	cin >> choice;
	}
	if (choice == 1)
		//add items to users shopping cart
	{
		books.addItem();
	}
	else if (choice == 2)
		//remove item from users shopping cart 
	{
		books.removeItem();
	}
	else // if (choice == 3)
		//take user to checkout with their shopping
		books.checkout();
}
void Cashier::setQuantity(int quan)
{
	quantity = quan;
}
void Cashier::setTax(double t)
{
	tax = t;
}
void Cashier::setTotal()
{
	//get retail price of each book with tax, add all books cost
	while (books.addItem())
	{
		total += (books.getRetail() * quantity) + tax;
	}
}
void Cashier::deleteFromInv(Inventory inventory)
{
	inventory.deleteBook(books);
}
void Cashier::checkout();
{
	
}
int Cashier::getQuantity()
{
	return quantity;
}
double Cashier::getTax()
{
	return tax;
}
double Cashier::getTotal()
{
	return total;
}

void Cashier::printReceipt()
{
  std::cout << "\t\t Copy of receipt" << std::endl << std::endl;
  std::cout << "Book 1  \t\t" << " cost of book" << books.getRetail() << std::endl;
  std::cout << "Book 2  \t\t" << " cost of book" << books.getRetail() << std::endl << std::endl;
  std::cout << "Subtotal\t\t" << books.getTotal() << endl;
  << std::endl;
  std::cout << "Tax     \t\t" << getTax() << std::endl << std::endl;
  std::cout << "Total   \t\t" << getTotal() << std::endl;
}
