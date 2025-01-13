#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

HealthPotion::HealthPotion()
    : Item("체력 포션", 20) {
}

std::string HealthPotion::GetName() const {
    return Name;  // 상속받은 Name 멤버 변수를 반환
}

void HealthPotion::Use(Character* character) {
    character->Health += 50;
    if (character->Health > character->MaxHealth) {
        character->Health = character->MaxHealth;
    }
    std::cout << "체력 포션 사용을 통해 체력 50 회복!\n";
}
