#include "Orc.h"
#include "Item.h"
#include <iostream>
#include <random>

// 오크의 발톱 아이템 클래스 정의 (OrcClaw 클래스)
class OrcClaw : public Item {
public:
    OrcClaw() : Item("오크의 발톱", 25) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(class Character* character) override {
        std::cout << "오크의 발톱을 팔아 골드를 얻었습니다.\n";
    }

    int GetPrice() const override { return 25; }  // 오크의 발톱 가격
};

Orc::Orc(int level)
    : Monster(level) {
    Name = "오크";
    Health = 120 + (level * 18);
    Attack = 12 + (level * 5);
    Defense = 8 + (level * 4);
    InitializeLootTable();
}

void Orc::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<OrcClaw>());
}

std::unique_ptr<Item> Orc::DropItem() {
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
