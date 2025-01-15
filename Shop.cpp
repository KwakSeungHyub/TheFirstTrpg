#include "Shop.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include "Equipment.h"
#include <iostream>
#include <memory>

Shop::Shop()
{
    AvailableItems.emplace_back(std::make_unique<HealthPotion>("체력 포션", 20, 1)); // 1 추가
    AvailableItems.emplace_back(std::make_unique<AttackBoost>("공격력 포션", 50, 1)); // 1 추가
    AvailableItems.emplace_back(std::make_unique<RevivePotion>("부활 포션", 100, 1)); // 1 추가

    AvailableItems.emplace_back(std::make_unique<Equipment>("목검", 100, 3, Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("나무갑옷", 100, 5, Equipment::EquipmentType::Armor));
    AvailableItems.emplace_back(std::make_unique<Equipment>("구리검", 200, 5, Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("구리갑옷", 200, 7, Equipment::EquipmentType::Armor));

    ItemDescriptions["체력 포션"] = "체력을 회복합니다.";
    ItemDescriptions["공격력 포션"] = "공격력을 일시적으로 증가시킵니다.";
    ItemDescriptions["부활 포션"] = "사망 시 사용되어 체력을 회복합니다.";
    ItemDescriptions["목검"] = "공격력을 3 증가시키는 무기.";
    ItemDescriptions["나무갑옷"] = "방어력을 5 증가시키는 방어구.";
    ItemDescriptions["구리검"] = "공격력을 5 증가시키는 무기.";
    ItemDescriptions["구리갑옷"] = "방어력을 7 증가시키는 방어구.";
}

void Shop::DisplayItems() const
{
    std::cout << "상점 판매 아이템 목록:\n";
    for (size_t i = 0; i < AvailableItems.size(); ++i)
    {
        std::cout << i + 1 << ". " << AvailableItems[i]->GetName() << " - "
            << AvailableItems[i]->GetPrice() << " 골드\n";
    }
}

void Shop::BuyItem(int index, Character* player) {
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "잘못된 선택입니다.\n";
        return;
    }

    int price = AvailableItems[index]->GetPrice();
    if (player->Gold >= price) {
        player->Gold -= price;
        player->AddItem(std::move(AvailableItems[index]));
        AvailableItems.erase(AvailableItems.begin() + index);
        std::cout << "구매 완료!\n";
    }
    else {
        std::cout << "골드가 부족합니다.\n";
    }
}
// 아이템 판매
void Shop::SellItem(const std::string& itemName, Character* player)
{
    auto it = player->Inventory.find(itemName);
    if (it != player->Inventory.end() && it->second->GetAmount() > 0) {
        int sellPrice = it->second->GetPrice() / 2;
        player->Gold += sellPrice;
        it->second->DecreaseAmount(1);
        std::cout << itemName << "을(를) " << sellPrice << " 골드에 판매했습니다.\n";
    }
    else {
        std::cout << "이 아이템을 가지고 있지 않습니다.\n";
    }
}
// 아이템 상세 설명용 메서드(index 기준)
void Shop::DisplayItemDetails(int index) const
{
    if (index < 0 || index >= AvailableItems.size())
    {
        std::cout << "잘못된 아이템 선택입니다.\n";
        return;
    }

    const std::string& itemName = AvailableItems[index]->GetName();
    auto it = ItemDescriptions.find(itemName);
    if (it != ItemDescriptions.end())
    {
        std::cout << itemName << ": " << it->second << "\n";
    }
    else
    {
        std::cout << itemName << ": 설명이 없습니다.\n";
    }
}