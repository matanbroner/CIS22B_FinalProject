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
    ifstream inputFile;
    inputFile.open(filename.c_str()); // pre-v.11 c++ requires c-string file name
    
    if (inputFile){
        while(bookCount < booksPossible && !inputFile.eof())
        {
            books[bookCount] = new Book;
            inputFile >> books[bookCount];
            bookCount++;
        }
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
    return pos;
}

bool Inventory::isInStock(string search)
{
    int pos = findBookIndex(search);
    if (books[pos]->getStock() >= 1)
        return true;
    else return false;
}

void Inventory::displayInternalMenu(int choice)
{
    clearBuffer();
    string buff = "";
  switch (choice)
    {
        case 1:
            viewInventory();
            displayTopMenu();
            break;
        case 2:
            addBook();
            displayTopMenu();
            break;
        case 3:
            cout << "Title for info: ";
            getline(cin, buff);
            getBookInfo(buff);
            displayTopMenu();
            break;
        case 4:
            cout << "Title for deletion: ";
            cin >> buff;
            deleteBook(buff);
            displayTopMenu();
            break;
        case 5:
            cout << "You have " << bookCount << " books in your Inventory" << endl;
            displayTopMenu();
            break;
        case 6:
            cout << "Title to edit: ";
            getline(cin, buff);
            editBook(buff);
            displayTopMenu();
            break;
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
        default:
            cout << "Something went wrong... " << endl;
    }
}

void Inventory::displayTopMenu()
{
    int choice = -1;
    cout << endl << setw(20) << "-- Inventory --" << endl << endl;
    cout << "[1] -- View a page in Inventory" << endl;
    cout << "[2] -- Add a book to Inventory" << endl;
    cout << "[3] -- Get info about a book in Inventory" << endl;
    cout << "[4] -- Delete a book from Inventory" << endl;
    cout << "[5] -- Get number of books in Inventory" << endl;
    cout << "[6] -- Edit a book's record" << endl;
    cout << endl << endl;
    cout << "[0] -- Return to previous page" << endl << endl;
    cout << "Option: ";
    
    cin >> choice;
    while (choice < 0 || choice > 6 || cin.fail())
    {
        cout << "** invalid response **" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
    displayInternalMenu(choice);
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
    try{
    int pos = findBookIndex(title);
    if (pos == -1)
        throw -1;
    else{
    for (int i = pos; i < bookCount; i++)
        books[i] = books[i+1];
    books[bookCount] = nullptr;
    bookCount--;
    cout << "Book has been deleted!" << endl;
    sortInventory();
    }
    }
    catch(...)
    {
        cout << "Book not in inventory..." << endl;
    }
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
    
    cout << "Page " << pages << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << left << setw(27) << "Title" << setw(20) << "Author" << setw(15) << "Publisher" << setw(15) << "Stock" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    
    if (10 * pages > bookCount) // bookc count is not divisible by 10 and user chose last page
    {
        int diff = bookCount - (10 * (pages-1));
        for (int i = bookCount - diff; i < bookCount; i++)
        {
            cout << left << setw(25) << books[i]->getTitle() << "   ";
            cout << setw(15) << books[i]->getAuthor() << "   ";
            cout << setw(15) <<  books[i]->getPub() << "   ";
            cout << books[i]->getStock() << endl;
        }
    }
    
    else // normal page display if user chose any page before last
    {
        for (int i = 10; i >= 1; i--)
        {
            cout << left << setw(25) << books[(10 * pages) - i]->getTitle() << "   ";
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
        string buff;
        int numBuff;
        double doubBuff;
        books[bookCount] = new Book;
        cout << "ISBN: ";
        while(getline(cin,buff) && buff.size() != 6)
        {
            books[bookCount]->verifyISBN(buff);
            cout << "Enter valid ISBN!" << endl;
            buff = "0";
        }
        books[bookCount]->setISBN(buff);
        
        cout << "Title: ";
        getline(cin, buff);
        books[bookCount]->setTitle(buff);
        
        cout << "Author: ";
        getline(cin, buff);
        books[bookCount]->setAuthor(buff);
        
        cout << "Publisher: ";
        getline(cin, buff);
        books[bookCount]->setPub(buff);
        
        cout << "Date Published (YYYYMMDD): ";
        while(getline(cin,buff) && buff.size() != 8)
        {
            cout << "Enter a valid date!" << endl;
        }
        books[bookCount]->setDate(buff);
        
        cout << "Stock: ";
        while(cin >> numBuff && numBuff <= 0)
            cout << "Invalid stock!" << endl;
        books[bookCount]->setStock(numBuff);
        
        cout << "Retail Price: $";
        while(cin >> doubBuff && doubBuff < 0.01)
            cout << "Invalid price!" << endl;
        books[bookCount]->setRT(doubBuff);
        
        cout << "Wholesale Price: $";
        while(cin >> doubBuff && doubBuff < 0.01)
            cout << "Invalid price!" << endl;
        books[bookCount]->setWS(doubBuff);
        bookCount++;
        
        clearBuffer();
    }
    else cout << "Book capacity reached, cannot add more books currently!" << endl;
    
}

void Inventory::addBook(string t)
{
    if (bookCount < booksPossible)
    {
        string buff;
        int numBuff;
        double doubBuff;
        books[bookCount] = new Book;
        cout << "ISBN: ";
        while(getline(cin,buff) && buff.size() != 6)
        {
            books[bookCount]->verifyISBN(buff);
            cout << "Enter valid ISBN!" << endl;
        }
        books[bookCount]->setISBN(buff);
        
        books[bookCount]->setTitle(t);
        
        cout << "Author: ";
        getline(cin, buff);
        books[bookCount]->setAuthor(buff);
        
        cout << "Publisher: ";
        getline(cin, buff);
        books[bookCount]->setPub(buff);
        
        cout << "Date Published (YYYYMMDD): ";
        while(getline(cin,buff) && buff.size() != 8)
        {
            cout << "Enter a valid date!" << endl;
        }
        books[bookCount]->setDate(buff);
        
        cout << "Stock: ";
        while(cin >> numBuff && numBuff <= 0)
            cout << "Invalid stock!" << endl;
        books[bookCount]->setStock(numBuff);
        
        cout << "Retail Price: $";
        while(cin >> doubBuff && doubBuff < 0.01)
            cout << "Invalid price!" << endl;
        books[bookCount]->setRT(doubBuff);
        
        cout << "Wholesale Price: $";
        while(cin >> doubBuff && doubBuff < 0.01)
            cout << "Invalid price!" << endl;
        books[bookCount]->setWS(doubBuff);
        books[bookCount]->correctPrices();
        
        bookCount++;
        
        cout << "Your #" << bookCount << " has been added!" << endl;
        sortInventory();
        
        clearBuffer();
    }
    else cout << "Book capacity reached, cannot add more books currently!" << endl;
    
}

void Inventory::getBookInfo(string title)
{
    try
    {
    int pos = findBookIndex(title);
    if (pos == -1)
        throw -1;
    else
        cout << books[pos];
    }
    catch(...)
    {
        cout << "Can't find book, would you like to add it to your inventory? (YES/NO)" << endl;
        string answer = "buff";
        while (getline(cin,answer) && answer != "YES" && answer != "NO")
            cout << "**invalid response**" << endl;
        if (answer == "YES")
            addBook(title);
        else cout << "Okay, not adding " << title << " to inventory" << endl;
        
    }
}

void Inventory::editBook(string title)
{
    string buff;
    int choice = 0, numBuff;
    double doubBuff;
    int index = findBookIndex(title);
    if (index != -1)
    {
        cout << "1. Edit ISBN" << endl;
        cout << "2. Edit title" << endl;
        cout << "3. Edit author" << endl;
        cout << "4. Edit publisher" << endl;
        cout << "5. Edit stock" << endl;
        cout << "6. Edit publish date" << endl;
        cout << "7. Edit retail price" << endl;
        cout << "8. Edit wholesale price" << endl << endl;
        cout << "0. Return to previous menu" << endl;
        cin >> choice;
        
        switch(choice)
        {
            case 1:
                clearBuffer();
                while(getline(cin,buff) && buff.size() != 6)
                {
                    books[index]->verifyISBN(buff);
                    cout << "Enter valid ISBN!" << endl;
                }
                books[index]->setISBN(buff);
                break;
            case 2:
                clearBuffer();
                cout << "Title: ";
                getline(cin, buff);
                books[index]->setTitle(buff);
                cout << "Title changed!" << endl;
                sortInventory();
                break;
            case 3:
                clearBuffer();
                cout << "Author: ";
                getline(cin, buff);
                books[index]->setAuthor(buff);
                cout << "Author changed!" << endl;
                break;
            case 4:
                clearBuffer();
                cout << "Publisher: ";
                getline(cin, buff);
                books[index]->setPub(buff);
                cout << "Publisher changed!" << endl;
                break;
            case 5:
                clearBuffer();
                cout << "Stock: ";
                while(cin >> numBuff && numBuff <= 0)
                    cout << "Invalid stock!" << endl;
                books[index]->setStock(numBuff);
                cout << "Stock changed!" << endl;
                break;
            case 6:
                clearBuffer();
                cout << "Date Published (YYYYMMDD): ";
                while(getline(cin,buff) && buff.size() != 8)
                {
                    cout << "Enter a valid date!" << endl;
                }
                books[index]->setDate(buff);
                cout << "Date changed!" << endl;
                break;
            case 7:
                clearBuffer();
                cout << "Retail Price: $";
                while(cin >> doubBuff && doubBuff < 0.01)
                    cout << "Invalid price!" << endl;
                books[index]->setRT(doubBuff);
                books[index]->correctPrices();
                cout << "Retail Price changed!" << endl;
                break;
            case 8:
                clearBuffer();
                cout << "Wholesale Price: $";
                while(cin >> doubBuff && doubBuff < 0.01)
                    cout << "Invalid price!" << endl;
                books[index]->setWS(doubBuff);
                books[index]->correctPrices();
                cout << "Wholesale Price changed!" << endl;
                break;
            case 0:
                displayTopMenu();
                break;
            default:
                cout << "invalid choice -- returning to main menu" << endl;
                displayTopMenu();
        }
        
    }
    else
    {
        cout << "Book not found... returning to main menu" << endl;
        displayTopMenu();
    }

}

ifstream& operator>>(ifstream &inputStream, Book* b)
{
    string buff = "";
    int buffNum = 0;
    double buffDouble = 0;
    
    getline(inputStream, buff, '\t'); // ISBN
    b->setISBN(buff);
    
    getline(inputStream, buff, '\t'); // title
    b->setTitle(buff);
    
    getline(inputStream, buff, '\t'); // author
    b->setAuthor(buff);
    
    getline(inputStream, buff, '\t'); // publisher
    b->setPub(buff);
    
    
    getline(inputStream, buff, '\t'); // clear tab buffer
    b->setDate(buff);
    
    inputStream >> buffNum; // stock
    b->setStock(buffNum);
    
    inputStream >> buffDouble; // retail price
    b->setRT(buffDouble);
    
    inputStream >> buffDouble; // wholesale price
    b->setWS(buffDouble);
    
    return inputStream;
}

void Inventory::printToFile()
{
    ofstream outputFile;
    outputFile.open(filename);
    for (int i = 0; i < bookCount; i++)
    {
        outputFile << books[i]->getISBN() << '\t';
        outputFile << books[i]->getTitle() << '\t';
        outputFile << books[i]->getPub() << '\t';
        outputFile << books[i]->getDate() << '\t';
        outputFile << books[i]->getStock() << '\t';
        outputFile << books[i]->getRetail() << '\t';
        outputFile << books[i]->getWholesale() << '\n';
    }
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

void Inventory::clearBuffer()
{
    cin.clear();
    cin.ignore(256,'\n');
}

int Inventory::getBookCount()
{
    return this->bookCount;
}

Inventory::~Inventory()
{
    cout << "Saving your inventory file..." << endl;
    printToFile();
    bookCount--; // Move availible book index down by 1
    while (bookCount >= 0)
    {
        delete books[bookCount];
        bookCount--;
    }
}

