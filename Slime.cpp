#include "Slime.h"
#include "Item.h"
#include <iostream>
#include <random>

// 슬라임 체액 아이템 클래스 정의 (SlimeJelly 클래스)
class SlimeJelly : public Item {
public:
    SlimeJelly() : Item("슬라임 체액", 10) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(class Character* character) override {
        std::cout << "슬라임 체액을 사용했지만, 아무 일도 일어나지 않았습니다.\n";
    }

    int GetPrice() const override { return 10; }  // 슬라임 체액 가격
};

Slime::Slime(int level)
    : Monster(level) {
    Name = "슬라임";
    Health = 50 + (level * 10);
    Attack = 5 + (level * 2);
    Defense = 2 + (level * 2);
    InitializeLootTable();
}

void Slime::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<SlimeJelly>());
}

std::unique_ptr<Item> Slime::DropItem() {
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
