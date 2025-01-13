#pragma once
#include "Item.h"
#include <vector>
#include <map>
#include <memory>
#include "Character.h"

class Shop {
public:
    
    std::vector<std::unique_ptr<Item>> AvailableItems;
    std::map<std::string, std::string> ItemDescriptions;

    Shop();
    void DisplayItems() const;
    void DisplayItemDetails(int index) const;
    void BuyItem(int index, Character* player);
    void SellItem(const std::string& itemName, Character* player);
};
