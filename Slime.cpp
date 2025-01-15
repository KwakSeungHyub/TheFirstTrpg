#include "Slime.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

// 슬라임 체액 아이템 클래스 정의 (SlimeJelly 클래스)
class SlimeFluid : public Item
{
public:
    SlimeFluid() : Item("슬라임 체액", 15) {}

    std::string GetName() const override
    {
        return Name;
    }

    void Use(class Character* character) override
    {
        std::cout << "슬라임 체액을 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override {
        return 45;  // 슬라임 체액 가격
    }

    Equipment* GetType() const override
    {
        static Equipment temp("슬라임 체액", 15, 0, Equipment::EquipmentType::Misc);
        return &temp;
    }
};



Slime::Slime(int level) : Monster(level)
{
    Name = "슬라임";
    MaxHealth = 50 + (level * 10);
    Health = MaxHealth;
    Attack = 5 + (level * 2);
    Defense = 2 + (level * 2);
    Experience = 95 + (level * 5);
    InitializeLootTable();
}

void Slime::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<SlimeFluid>());
}

std::unique_ptr<Item> Slime::DropItem()
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