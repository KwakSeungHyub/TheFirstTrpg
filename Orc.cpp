#include "Orc.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class OrcAxe : public Item
{
public:
    OrcAxe() : Item("오크의 도끼", 25) {}

    std::string GetName() const override
    {
        return Name;
    }

    void Use(class Character* character) override
    {
        std::cout << "오크의 도끼를 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override
    {
        return 25;  // 오크의 도끼 가격
    }

    Equipment* GetType() const override
    {
        static Equipment temp("오크의 도끼", 25, 0, Equipment::EquipmentType::Misc);
        return &temp;
    }
};

Orc::Orc(int level) : Monster(level)
{
    Name = "오크";
    MaxHealth = 120 + (level * 18);
    Health = MaxHealth;
    Attack = 12 + (level * 5);
    Defense = 8 + (level * 4);
    InitializeLootTable();
}

void Orc::InitializeLootTable()
{
    LootTable.emplace_back(std::make_unique<OrcAxe>());
}

std::unique_ptr<Item> Orc::DropItem()
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