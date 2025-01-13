#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include <iostream>
#include <memory>

Shop::Shop() 
{
    AvailableItems.emplace_back(std::make_unique<HealthPotion>());
    AvailableItems.emplace_back(std::make_unique<AttackBoost>());
    AvailableItems.emplace_back(std::make_unique<RevivePotion>());

    // 아이템 설명을 한글로 처리
    ItemDescriptions["체력 포션"] = "체력 50 회복.";
    ItemDescriptions["공격력 포션"] = "다음 전투에서 공격력이 10 증가.";
    ItemDescriptions["부활 포션"] = "캐릭터를 부활시키고 체력을 가득 채웁니다.";
}

// 아이템 목록 표시
void Shop::DisplayItems() const 
{
    std::cout << "판매 중인 아이템:\n";
    for (size_t i = 0; i < AvailableItems.size(); ++i) {
        std::cout << i + 1 << ". " << AvailableItems[i]->GetName() << " - "
            << (i == 0 ? 20 : 50) << " 골드\n";
    }
}

// 아이템 세부 설명
void Shop::DisplayItemDetails(int index) const 
{
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "잘못된 아이템 선택입니다.\n";
        return;
    }

    std::string itemName = AvailableItems[index]->GetName();
    std::cout << itemName << ": " << ItemDescriptions.at(itemName) << "\n";
}

// 아이템 구매 (스마트 포인터 적용)
void Shop::BuyItem(int index, Character* player) 
{
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "잘못된 아이템 선택입니다.\n";
        return;
    }

    int price = (index == 0 ? 20 : 50);
    if (player->Gold >= price) {
        player->Gold -= price;
        player->AddItem(std::move(AvailableItems[index]));
        AvailableItems.erase(AvailableItems.begin() + index);
        std::cout << "새 아이템을 구매했습니다!\n";
    }
    else {
        std::cout << "골드가 부족합니다.\n";
    }
}

void Shop::SellItem(const std::string& itemName, Character* player) 
{
    // 1. 인벤토리에서 아이템을 찾습니다.
    auto it = player->Inventory.find(itemName);
    if (it != player->Inventory.end() && it->second != 0) {
        // 아이템이 인벤토리에 있을 때, 아이템을 팔기
        std::unique_ptr<Item>& item = it->second;  // 인벤토리에서 아이템 가져오기

        // 가격을 아이템 객체에서 가져옴
        int sellPrice = item->GetPrice();  // GetPrice()는 각 아이템 클래스에서 정의되어 있어야 함

        // 골드 증가
        player->Gold += sellPrice;
        player->Inventory.erase(it);  // 해당 아이템을 인벤토리에서 삭제

        std::cout << itemName << "을(를) " << sellPrice << " 골드에 판매했습니다. 현재 보유 골드 :" <<player -> Gold <<"골드 \n";
    }
    else {
        std::cout << "이 아이템은 가지고 있지 않습니다.\n";
    }
}




