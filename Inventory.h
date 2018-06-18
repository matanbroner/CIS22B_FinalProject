//
//  Inventory.h
//  CIS22B_FinalProject
//
//  Created by Matan Broner on 6/5/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef Inventory_h
#define Inventory_h
#include "Book.h"
#include "Module.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

ifstream& operator>>(ifstream&, Book*);
ostream& operator<<(ostream& ,Book*);

class Book;
class Inventory
{
private:
    string filename = "";
    const static int booksPossible = 100;
    Book* books[booksPossible];
    int bookCount = 0;
public:
    Inventory(string);
    void displayTopMenu();
    bool isInStock(string);
    void printToFile();
    void addBook();
    void addBook(string);
    void deleteBook(string);
    void editBook(string);
    void getBookInfo(string);
    void sortInventory();
    void viewInventory();
    void displayInternalMenu(int);
    
    int findBookIndex(string);
    
    friend ifstream& operator>>(ifstream&, Book*);
    friend ostream& operator<<(ostream& ,Book*);
    void clearBuffer();
    
    ~Inventory();
};


#endif /* Inventory_h */
