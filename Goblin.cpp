#include "Goblin.h"
#include "Item.h"
#include <iostream>
#include <random>

// 고블린의 귀 아이템 클래스 정의 (GoblinEar 클래스)
class GoblinEar : public Item {
public:
    GoblinEar() : Item("고블린의 귀", 15) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(class Character* character) override {
        std::cout << "고블린의 귀를 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override { return 15; }  // 고블린의 귀 가격
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
    LootTable.emplace_back(std::make_unique<GoblinEar>());
}

std::unique_ptr<Item> Goblin::DropItem() {
    if (LootTable.empty()) {
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
