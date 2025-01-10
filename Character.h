// Character.h
#pragma once
#include "Item.h"
#include <string>
#include <vector>

class Character {
public:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int Experience;
    int Gold;
    std::vector<Item*> Inventory;

    Character(const std::string& name);
    void LevelUp();
    void GainExperience(int exp);
    void TakeDamage(int damage);
    void DisplayStatus() const;
    void VisitShop();
};