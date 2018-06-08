//
// Cashier.cpp
//

#include "Cashier.h"

// constructor
// Cashier::Cashier()
// {
//
// }

Cashier::interact() //user can add books to shopping cart then check out
{
  //red booklist from file
  //create instance of shopping cart object
  std::cout << "Selected the Cashier Module" << std::endl << std::endl;

  std::cout << "In this module you can select books to add to your shopping cart for purchase." << std::endl;
  std::cout << "Once you have all the desired books in your cart you can proceed to checkout."
  << std::endl;

  int choice = 0; //for user input, defaulted to 0 to proceed to while loop

  std::cout << "Please select an option below:" << std::endl;
  std::cout << "1. Add books to your shopping cart" << std::endl;
  std::cout << "2. Proceed to checkout" << std::endl;
  cin >> choice;

  //haven't tested the loop yet but the idea is to continue to ask the user for
  //input until they select either 1 or 2
  while (choice != 1 || choice != 2)
  {
    std::cout << "Please select to add to your cart or proceed to checkout." << std::endl;
    cin >> choice;
  }
  if (choice == 1)
    //add items to users shopping cart by reading book info from file

    //function to do this?

  else // if (choice == 2)
    //take user to checkout with their shopping


}
void Cashier::setQuantity(int quan)
{
  quantity = quan;
}
void Cashier::setTax(double t)
{
  tax = t;
}
void Cashier::setSubTotal(double sub)
{
  subTotal = sub;
}
void Cashier::getTotal()
{
  total = (subTotal * quantity) * tax;
}
int Cashier::getQuantity()
{
  return quantity;
}
double Cashier::getTax()
{
  return tax;
}
double Cashier::getSubTotal()
{
  return subTotal;
}
double Cashier::getTotal()
{
  return total;
}

void Cashier::printReceipt()
{
  std::cout << "\t\t Copy of receipt" << std::endl << std::endl;
  std::cout << "Book 1  \t\t" << " cost of book" /*read from book file? */ << std::endl;
  std::cout << "Book 2  \t\t" << " cost of book" /*read from book file? */ << std::endl << std::endl;
  std::cout << "Subtotal\t\t" << getSubTotal() /*cost of all books*/ << std::endl;
  std::cout << "Tax     \t\t" << getTax() << std::endl << std::endl;
  std::cout << "Total   \t\t" << getTotal() << std::endl;
}
