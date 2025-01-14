#include "Troll.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class TrollClaw: public Item
{
public:
    TrollClaw(): Item("트롤의 발톱",30) {}

    std::string GetName() const override
    {
        return Name;
    }

    void Use(class Character* character) override
    {
        std::cout << "트롤의 발톱을 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override
    {
        return 30;  // 트롤의 발톱 가격
    }

    Equipment* GetType() const override
    {
        static Equipment temp("트롤의 발톱",30,0,Equipment::EquipmentType::Misc);
        return &temp;
    }
};

Troll::Troll(int level)
    : Monster(level) {
    Name = "트롤";
    Health = 100 + (level * 15);
    Attack = 10 + (level * 4);
    Defense = 5 + (level * 3);
    InitializeLootTable();
}

void Troll::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<TrollClaw>());
}

std::unique_ptr<Item> Troll::DropItem() {
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