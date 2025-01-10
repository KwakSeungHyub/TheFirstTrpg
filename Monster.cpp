#include "Monster.h"
#include <iostream>

Monster::Monster(const std::string& name, int health, int attack)
    : Name(name), Health(health), Attack(attack) {
}

void Monster::TakeDamage(int damage) {
    Health -= damage;
    if (Health < 0) Health = 0;
}

bool Monster::IsDefeated() const {
    return Health <= 0;
}

Item* Monster::DropItem() {
    std::cout << Name << " dropped an item!\n";
    return nullptr;
}
