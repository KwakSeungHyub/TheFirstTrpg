#pragma once
#include <string>

class Item {

public:

	std::string name;
	int price;

	Item(const std::string& itemname, int itemprice) {}

	void displayItem() const;

};