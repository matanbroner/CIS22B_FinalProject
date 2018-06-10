//
//  Inventory.cpp
//  CIS22B_FinalProject
//
//  Created by Matan Broner on 6/6/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//
#include "Inventory.h"

Inventory::Inventory(string filename)
{
    this->filename = filename;
    cout << filename << endl;
    ifstream inputFile;
    inputFile.open(filename.c_str()); // pre-v.11 c++ requires c-string file name
    
    if (inputFile){
    while(bookCount < booksPossible && !inputFile.eof())
    {
        books[bookCount] = new Book;
        inputFile >> books[bookCount];
        bookCount++;
    }
    // eof reads one extra time after end of file is reached
        bookCount--;
        sortInventory();
        
        cout << "You have " << bookCount << " books" << endl;
        
        //addBook();
        cout << "You have " << bookCount << " books" << endl;
        viewInventory();
    }
    inputFile.close();
}


int Inventory::findBookIndex(string search)
{
    cout << "Search..." << endl;
    int pos = -1;
    for (int i = 0; i < bookCount; i++)
        if (books[i]->getTitle() == search)
            pos = i;
    if (pos == -1)
        cout << "Not Found!" << endl;
    return pos;
}

bool Inventory::isInStock(string search)
{
    int pos = findBookIndex(search);
    if (books[pos]->getStock() >= 1)
        return true;
    else return false;
}

void Inventory::displayInternalMenu()
{
        cout << "Inventory Manipulation Menu" << endl;
        cout << "1. View Inventory" << endl;
        cout << "2. Manipulate Book Info" << endl;
        cout << "3. Add Book" << endl;
        cout << "4. Delete Book" << endl;
    
        //processUserInput(getUserInput());
}

int Inventory::getUserInput()
{
    int UI = 0;
    cin >> UI;
    
    return UI;
}

void Inventory::sortInventory()
{
    int startPos, minIndex;
    Book* minValue;
    
    for (startPos = 0; startPos < (bookCount - 1); startPos++)
    {
        minIndex = startPos;
        minValue = books[startPos];
        for (int index  = startPos + 1; index < bookCount; index++)
        {
            if (books[index]->getTitle() < minValue->getTitle())
            {
                minValue = books[index];
                minIndex = index;
            }
       }
        books[minIndex] = books[startPos];
        books[startPos] = minValue;
    }
}

void Inventory::deleteBook(string title)
{
    int pos = findBookIndex(title);
    for (int i = pos; i < bookCount; i++)
        books[i] = books[i+1];
    books[bookCount] = nullptr;
    bookCount--;
}

void Inventory::viewInventory()
{
    int pages = 0;
    if (bookCount % 10 == 0) // book count is divisible by 10
        pages = bookCount / 10;
    else pages  = (bookCount / 10) + 1; // add extra page for remainder
    
    cout << "There are " << pages << " in your Inventory." << endl;
    cout << "View Page: ";
    cin >> pages;
    
    cout << setw(30) << "Page " << pages << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << left <<setw(25) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(5) << "Stock" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    if (10 * pages > bookCount) // bookc count is not divisible by 10 and user chose last page
    {
        int diff = bookCount - (10 * (pages-1));
        for (int i = bookCount - diff; i < bookCount; i++)
        {
            cout << setw(25) << left << books[i]->getTitle() << "   ";
            cout << setw(15) << books[i]->getAuthor() << "   ";
            cout << setw(15) <<  books[i]->getPub() << "   ";
            cout << books[i]->getStock() << endl;
        }
    }
    
    else // normal page display if user chose any page before last
    {
        for (int i = 10; i >= 1; i--)
        {
            cout << setw(25) << left << books[(10 * pages) - i]->getTitle() << "   ";
            cout << setw(15) << books[(10 * pages) - i]->getAuthor() << "   ";
            cout << setw(15) <<  books[(10 * pages) - i]->getPub() << "   ";
            cout << books[(10 * pages) - i]->getStock() << endl;
        }
    }
}

void Inventory::addBook()
{
    if (bookCount < booksPossible)
    {
        bookCount++;
        string buff;
        int numBuff;
        double doubBuff;
        books[bookCount] = new Book;
        cout << "ISBN: ";
        while(getline(cin,buff) && buff.size() != 6)
            cout << "Enter valid ISBN!" << endl;
        books[bookCount]->setISBN(buff);
        books[bookCount]->verifyISBN();
    
        cout << "Title: ";
        getline(cin, buff);
        books[bookCount]->setTitle(buff);
    
        cout << "Author: ";
        getline(cin, buff);
        books[bookCount]->setAuthor(buff);
    
        cout << "Publisher: ";
        getline(cin, buff);
        books[bookCount]->setAuthor(buff);
        
        cout << "Date Published (YYYYMMDD): ";
        while(getline(cin,buff) && buff.size() != 8)
        {
            cout << "Enter a valid date!" << endl;
        }
        books[bookCount]->setDate(buff);
    
        cout << "Stock: ";
        while(cin >> numBuff && numBuff <= 0)
            cout << "Invalid stock!" << endl;
        
        cout << "Retail Price: $";
        while(cin >> doubBuff && doubBuff < 0.01)
            cout << "Invalid price!" << endl;
        books[bookCount]->setRT(doubBuff);
        
        cout << "Wholesale Price: $";
        while(cin >> doubBuff && doubBuff < 0.01)
            cout << "Invalid price!" << endl;
        books[bookCount]->setWS(doubBuff);
        
        getline(cin, buff);
    }
    else cout << "Book capacity reached, cannot add more books currently!" << endl;
    
}

void Inventory::getBookInfo(string title)
{
    int pos = findBookIndex(title);
    cout << books[pos];
}

ifstream& operator>>(ifstream &inputStream, Book* b)
{
    string buff = "";
    char *buffArr;
    int buffNum = 0;
    double buffDouble = 0;
    
    buffArr = new char[5]; // dynamic array to hold ISBN chars
    inputStream >> buff; // read ISBN as a string
    for (int i = 0; i < 6; i++){
        buffArr[i] = buff[i]; // seperate chars in ISBN
    }
    getline(inputStream, buff, '\t'); //clear tab buffer
    b->setISBN(buffArr);
    delete buffArr;
    
    getline(inputStream, buff, '\t'); // title
    b->setTitle(buff);
    
    getline(inputStream, buff, '\t'); // author
    b->setAuthor(buff);
    
    getline(inputStream, buff, '\t'); // publisher
    b->setPub(buff);
    
    buffArr = new char[8]; // dynamic array to hold date chars
    inputStream >> buff;
    for (int i = 0; i < 8; i++){
        buffArr[i] = buff[i];
    }
    getline(inputStream, buff, '\t'); // clear tab buffer
    b->setDate(buffArr);
    delete buffArr;
    
    inputStream >> buffNum; // stock
    b->setStock(buffNum);
    
    inputStream >> buffDouble; // retail price
    b->setRT(buffDouble);
    
    inputStream >> buffDouble; // wholesale price
    b->setWS(buffDouble);

    return inputStream;
}

ostream& operator<<(ostream& strm, Book* x)
{
    cout << "ISBN: " << x->getISBN() << endl;
    cout << "Title: " << x->getTitle() << endl;
    cout << "Author: " << x->getAuthor() << endl;
    cout << "Publisher: " << x->getPub() << endl;
    cout << "Date Published: " << x->getDate() << endl;
    cout << "Stock: " << x->getStock() << endl;
    cout << "Retail Price: " << x->getRetail() << endl;
    cout << "Wholesale Price: " << x->getWholesale() << endl;
    
    return strm;
}
Inventory::~Inventory()
{
    while (bookCount >= 0)
    {
        delete books[bookCount];
        bookCount--;
    }
}
