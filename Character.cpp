#include "Character.h"
#include <iostream>

Character::Character(const std::string& name)
    : Name(name), Level(1), Health(100), MaxHealth(100), Attack(10), Experience(0), Gold(50) {
}

void Character::LevelUp() {
    Level++;
    MaxHealth += 20;
    Health = MaxHealth;
    Attack += 5;
    std::cout << Name << " leveled up to level " << Level << "!\n";
}

void Character::GainExperience(int exp) {
    Experience += exp;
    if (Experience >= Level * 100) {
        LevelUp();
    }
}

void Character::TakeDamage(int damage) {
    Health -= damage;
    if (Health < 0) Health = 0;
}

void Character::DisplayStatus() const {
    std::cout << "Character: " << Name << ", Level: " << Level
        << ", Health: " << Health << "/" << MaxHealth << ", Gold: " << Gold << "\n";
}

void Character::VisitShop() {
    std::cout << Name << " visits the shop.\n";
}
