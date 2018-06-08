#pragma once

#include <iostream>
#include <ctime>
#include <string>

class Item {
private:
	std::string ISBN;
	std::string title;
	std::string author;
	std::string publisher;
	int dateAdded; //YYYYMMDD
	int quantity;
	double wholesaleCost;
	double retailPrice;

public:
	Item();
	Item(int, std::string, std::string, std::string, int, int, double, double);
	Item(const Item &obj); // copy constructor
	~Item();

	int setPrice();
	void addBooks();
	void removeBooks();

	int getISBN();
	std::string getTitle();
	std::string getAuthor();
	std::string getPublisher();
	int getDateAdded();
	int getQuantity();
	double getCost();
	double getPrice();

	// not sure if we need these
	//friend bool operator==(const Item& item1, const Item& item2); // compare every member variable but the quantity
	//friend Item& operator+(const Item& item1, const Item& item2); // exception: items are not the same
	//friend Item& operator-(const Item& item1, const Item& item2); // exception: items are not the same
};

// note: overload input/output operators with iostream to read entire line of the file at a time