// Cashier.h
#ifndef CASHIER_H
#define CASHIER_H

#include "Book.h"
#include "Inventory.h"

class Cashier
{
private:
  int quantity;
  double tax;
  double subTotal;
  double total;
public:
  //constructor here
  //Cashier();
  void setQuantity(int);
  void setTax(double);
  void setSubTotal(double);
  void setTotal():
  int getQuantity();
  double getTax();
  double getSubTotal();
  double getTotal();

  void interact();
  void printReceipt();

  //will work on these Fri night/Saturday
  //void checkout();
  //void addToCart();

};


#endif
