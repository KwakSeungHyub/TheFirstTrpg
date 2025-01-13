#pragma once
#include "Item.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>

class Shop;

class Character {
public:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int AttackBoostAmount = 0;  // 포션으로 증가한 공격력 추적
    int Experience;
    int Gold;

    // 스마트 포인터를 사용한 인벤토리 (아이템과 개수)
    // Character 클래스의 Inventory 맵을 한글로 설정
    // std::unordered_map<std::string, int> Inventory;
    std::unordered_map<std::string, std::unique_ptr<Item>> Inventory; // 포인터로 변경

    Character(const std::string& name);
    void LevelUp();
    void GainExperience(int exp);
    void TakeDamage(int damage);
    void DisplayStatus() const;
    void VisitShop(Shop* shop);
    void ShowInventory() const;
    void AddItem(std::unique_ptr<Item> item) {
        const std::string& itemName = item->GetName();
        if (Inventory.find(itemName) == Inventory.end()) {
            Inventory[itemName] = std::move(item);  // 새 아이템 추가
        }
        else {
            // 이미 존재하는 아이템이 있다면, 수량을 증가시킴
            Inventory[itemName]->IncreaseAmount(item->GetAmount());
        }
    }
    void SellItemAtShop(Shop* shop);
    void AutoUseItems();  // 전투 중 자동 사용 기능

    void ResetAttackBoost();  // 공격력 초기화 함수 추가
};
