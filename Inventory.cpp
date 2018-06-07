//
//  Inventory.cpp
//  CIS22B_FinalProject
//
//  Created by Matan Broner on 6/6/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#include "Inventory.h"

Inventory::Inventory(ifstream &inputFile)
{
    cout << "Reading file up to 100 books..." <<endl;
    while(bookCount < booksPossible && !inputFile.eof())
    {
        books[bookCount] = new Book;
        inputFile >> books[bookCount];
        bookCount++;
    }
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


ifstream& operator>>(ifstream &inputStream, Book* b)
{
    cout << "Running this function" << endl;
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

Inventory::~Inventory()
{
    while (bookCount >= 0)
    {
        delete books[bookCount];
        bookCount--;
    }
}
