#include <string>
#include "Item.h"
#include <iostream>
#include <memory>

class Item {

public:

	std::string name;
	int price;

	Item(const std::string& itemname, int itemprice) : name(itemname), price(itemprice) {}

	void displayItem() const {
		std::cout << "Item: " << name << ", Price: " << price << std::endl;
	}
	

};

// ��� ���̺� ����ü : �����۰� Ȯ���� �� ������ ����
struct DropEntry {
	std::unique_ptr<Item> item;	// ��� ������
	int dropRate;				// ��� Ȯ��
};
