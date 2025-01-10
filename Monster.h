// Monster.h
#pragma once
#include "Item.h"
#include <string>

class Monster {
public:
    std::string Name;
    int Health;
    int Attack;

    Monster(const std::string& name, int health, int attack);
    void TakeDamage(int damage);
    bool IsDefeated() const;
    Item* DropItem();
};