// Monster.h
#pragma once
#include "Item.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <random>

class Monster {
public:
    std::string Name;
    int Health;
    int Attack;
    int Defense;
    int Level;
    std::vector<std::unique_ptr<Item>> LootTable; // 전리품 테이블

    // 기본 생성자
    Monster() : Name("Unknown"), Health(100), Attack(10), Defense(5), Level(1) {}

    // 레벨 기반 생성자
    Monster(int level) : Name("Unknown"), Health(100 + level * 10), Attack(10 + level * 2), Defense(5 + level), Level(level) {}

    // 이름, 체력, 공격력, 방어력 기반 생성자
    Monster(const std::string& name, int health, int attack, int defense)
        : Name(name), Health(health), Attack(attack), Defense(defense), Level(1) {
    }

    // 피해를 받으면 체력 감소
    void TakeDamage(int damage) {
        Health -= damage;
        std::cout << Name << "가 " << damage << "의 피해를 입었습니다!\n";
        if (Health < 0) {
            Health = 0;
        }
    }

    // 몬스터가 패배했는지 확인
    bool IsDefeated() const {
        return Health <= 0;
    }

    // 기본 구현을 제공
    virtual void InitializeLootTable() {
        // 기본 구현은 비어있는 전리품 테이블
        LootTable.clear();
    }

    virtual std::unique_ptr<Item> DropItem() {
        if (LootTable.empty()) {
            std::cout << Name << "는 전리품을 가지고 있지 않습니다.\n";
            return nullptr;
        }

        // 랜덤으로 전리품을 떨어뜨림
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, LootTable.size() - 1);

        int index = dist(gen);
        std::cout << Name << "가 " << LootTable[index]->GetName() << "를 떨어뜨렸습니다!\n";
        return std::move(LootTable[index]);
    }

    virtual ~Monster() = default;
};
