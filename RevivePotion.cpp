#include "RevivePotion.h"
#include "Character.h"
#include <iostream>

RevivePotion::RevivePotion(const std::string& name, int price, int amount)
    : Item(name, price, amount) {}

std::string RevivePotion::GetName() const {
    return Name;  // 한글로 반환
}

void RevivePotion::Use(Character* character) {
    if (character->Health <= 0) {
        character->Health = character->MaxHealth / 2;  // 부활 후 체력 50% 회복
        std::cout << character->Name << " 부활 포션 사용으로 체력 50% 상태로 부활!\n";
    }
    else {
        std::cout << "죽음에 이르렀을 때만 사용 가능합니다.\n";
    }
}
