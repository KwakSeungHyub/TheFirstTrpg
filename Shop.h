#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Item.h"


class Shop {
private:
    std::vector<std::unique_ptr<Item>> AvailableItems;
    std::unordered_map<std::string, std::string> ItemDescriptions;

public:
    Shop();
    void DisplayItems() const;
    void DisplayItemDetails(int index) const;
    void BuyItem(int index, Character* player);
    void SellItem(const std::string& itemName, Character* player);
};
