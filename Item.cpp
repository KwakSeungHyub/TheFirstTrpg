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

// 드랍 테이블 구조체 : 아이템과 확률을 한 쌍으로 저장
struct DropEntry {
	std::unique_ptr<Item> item;	// 드랍 아이템
	int dropRate;				// 드랍 확률
};
