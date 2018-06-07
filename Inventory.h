
#ifndef Inventory_h
#define Inventory_h
#include "Book.h"
#include <fstream>
#include <string>
#include <stdlib.h>

ifstream& operator>>(ifstream&, Book*);

class Book;
class Inventory
{
private:
    const static int booksPossible = 100;
    Book* books[booksPossible];
    int bookCount = 0;
public:
    Inventory(ifstream&);
    void getUserInput();
    int proccessUserInput();
    bool isInStock();
    void printToFile(ofstream);
    Book* addBook();
    void deleteBook(string);
    void editBook(string);
    Book getBookInfo(string);
    void sortInventory();
    
    int findBookIndex(string);
    
    friend ifstream& operator>>(ifstream&, Book*);
    
    ~Inventory();
};

