#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include <iostream>
#include <memory>

Shop::Shop() {
    AvailableItems.emplace_back(std::make_unique<HealthPotion>());
    AvailableItems.emplace_back(std::make_unique<AttackBoost>());
    AvailableItems.emplace_back(std::make_unique<RevivePotion>());

    // 아이템 설명을 한글로 처리
    ItemDescriptions["체력 포션"] = "체력 50 회복.";
    ItemDescriptions["공격력 포션"] = "다음 전투에서 공격력이 10 증가.";
    ItemDescriptions["부활 포션"] = "캐릭터를 부활시키고 체력을 가득 채웁니다.";
}

// 아이템 목록 표시
void Shop::DisplayItems() const {
    std::cout << "판매 중인 아이템:\n";
    for (size_t i = 0; i < AvailableItems.size(); ++i) {
        std::cout << i + 1 << ". " << AvailableItems[i]->GetName() << " - "
            << (i == 0 ? 20 : 50) << " 골드\n";
    }
}

// 아이템 세부 설명
void Shop::DisplayItemDetails(int index) const {
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "잘못된 아이템 선택입니다.\n";
        return;
    }

    std::string itemName = AvailableItems[index]->GetName();
    std::cout << itemName << ": " << ItemDescriptions.at(itemName) << "\n";
}

// 아이템 구매 (스마트 포인터 적용)
void Shop::BuyItem(int index, Character* player) {
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

void Shop::SellItem(const std::string& itemName, Character* player) {
    // 1. 인벤토리에서 아이템을 찾습니다.
    if (player->Inventory.find(itemName) != player->Inventory.end() && player->Inventory[itemName] > 0) {
        // 아이템이 인벤토리에 있을 때, 아이템을 팔기
        std::unique_ptr<Item> item = nullptr;

        // 인벤토리에서 아이템 찾기
        for (auto& inventoryItem : player->Inventory) {
            if (inventoryItem.first == itemName && inventoryItem.second > 0) {
                // 아이템 클래스가 HealthPotion, AttackBoost 등일 경우 그에 맞는 객체를 생성
                if (itemName == "체력 포션") {
                    item = std::make_unique<HealthPotion>();
                }
                else if (itemName == "공격력 포션") {
                    item = std::make_unique<AttackBoost>();
                }
                else if (itemName == "부활 포션") {
                    item = std::make_unique<RevivePotion>();
                }
                break;
            }
        }

        if (item) {
             // 전리품 아이템일 경우, 가격을 따로 계산
            int sellPrice = item->Price;  // 아이템의 가격은 아이템 객체에서 가져옴

            player->Gold += sellPrice;
            player->Inventory[itemName]--;  // 아이템 개수 감소
            std::cout << itemName << "을(를) " << sellPrice << " 골드에 판매했습니다.\n";
        }
        else {
            std::cout << "아이템을 찾을 수 없습니다.\n";
        }
    }
    else {
        std::cout << "이 아이템은 가지고 있지 않습니다.\n";
    }
}


