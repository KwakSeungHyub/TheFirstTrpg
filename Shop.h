#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Item.h"

class Shop
{
private:
    std::vector<std::unique_ptr<Item>> AvailableItems;
    std::unordered_map<std::string, std::string> ItemDescriptions;

public:
    Shop();
    // 아이템 목록
    void DisplayItems() const;
    // 아이템 목록 + 설명
    void DisplayItemDetails(int index) const;
    // 아이템 구매
    void BuyItem(int index, Character* player);
    // 아이템 판매
    void SellItem(const std::string& itemName, Character* player);

    void PurchaseEquipment();
};