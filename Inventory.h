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
#include <fstream>


class Book;
class Inventory
{
private:
    Book *books[];
    const static int booksPossible = 100;
public:
    Inventory(ifstream);
    void getUserInput();
    int proccessUserInput();
    bool isInStock();
    void printToFile(ofstream);
    Book* addBook();
    void deleteBook(string);
    void editBook(string);
    Book getBookInfo(string);
    void sortInventory();
};


#endif /* Inventory_h */
