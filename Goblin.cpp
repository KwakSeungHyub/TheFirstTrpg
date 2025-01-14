#include "Goblin.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class GoblinSpear: public Item
{
public:
    GoblinSpear(): Item("고블린의 창",20) {}

    std::string GetName() const override
    {
        return Name;
    }

    void Use(class Character* character) override
    {
        std::cout << "고블린의 창을 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override
    {
        return 20;  // 고블린의 창 가격
    }

    Equipment* GetType() const override
    {
        static Equipment temp("고블린의 창",20,0,Equipment::EquipmentType::Misc);
        return &temp;
    }
};


Goblin::Goblin(int level)
    : Monster(level) {
    Name = "고블린";
    Health = 70 + (level * 12);
    Attack = 8 + (level * 3);
    Defense = 3 + (level * 2);
    InitializeLootTable();
}

void Goblin::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<GoblinSpear>());
}

std::unique_ptr<Item> Goblin::DropItem() {
    if(LootTable.empty()) {
        std::cout << Name << "는 전리품을 가지고 있지 않습니다.\n";
        return nullptr;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,LootTable.size() - 1);

    int index = dist(gen);
    std::cout << Name << "가 " << LootTable[index]->GetName() << "를 떨어트렸습니다!\n";
    return std::move(LootTable[index]);
}