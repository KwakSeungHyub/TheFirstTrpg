#pragma once
#include "Item.h"
#include "Character.h"
#include <vector>

class Shop {
public:
    std::vector<Item*> AvailableItems;
    Shop();
    void DisplayItems() const;
    void BuyItem(int index, Character* player);
    void SellItem(int index, Character* player);
};