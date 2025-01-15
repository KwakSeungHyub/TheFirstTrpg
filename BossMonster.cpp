// BossMonster.cpp
#include "BossMonster.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class DemonLordSword : public Item
{
public:
    DemonLordSword() : Item("마왕의 검", 1000) {}

    std::string GetName() const override
    {
        return Name;
    }

    void Use(class Character* character) override
    {
        std::cout << "마왕의 검을 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override
    {
        return 1000;  // 마왕의 검 가격
    }

    Equipment* GetType() const override
    {
        static Equipment temp("마왕의 검", 1000, 0, Equipment::EquipmentType::Misc);
        return &temp;
    }
};


// BossMonster 클래스 구현
BossMonster::BossMonster(int level)
    : Monster(level)
{
    Name = "마왕";
    Health = 500 + (level * 50);
    Attack = 50 + (level * 10);
    Defense = 40 + (level * 5);
    InitializeLootTable();
}

void BossMonster::InitializeLootTable()
{
    LootTable.clear();  // 이전 전리품 테이블 초기화
    LootTable.emplace_back(std::make_unique<DemonLordSword>());
}

std::unique_ptr<Item> BossMonster::DropItem()
{
    if (LootTable.empty())
    {
        std::cout << Name << "는 전리품을 가지고 있지 않습니다.\n";
        return nullptr;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, LootTable.size() - 1);

    int index = dist(gen);
    std::cout << Name << "가 " << LootTable[index]->GetName() << "를 떨어트렸습니다!\n";
    return std::move(LootTable[index]);
}