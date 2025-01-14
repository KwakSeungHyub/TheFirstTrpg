#include "RevivePotion.h"
#include "Character.h"
#include <iostream>

// 생성자
RevivePotion::RevivePotion(const std::string& name, int price, int amount)
    : Item(name, price, amount) {
}

// Use 함수 구현 (캐릭터 부활 효과)
void RevivePotion::Use(Character* character) {
    if (character->Health <= 0) {
        character->Health = character -> MaxHealth / 2;  // 부활 시 최대 체력의 절반으로 설정
        std::cout << Name << "을 사용하여 캐릭터가 부활했습니다!\n";
    }
    else {
        std::cout << "이미 살아있는 캐릭터입니다.\n";
    }
}

// 장비 타입 반환
Equipment* RevivePotion::GetType() const {
    static Equipment temp("부활 포션", 50, 0, Equipment::EquipmentType::Consumable);
    return &temp;  // 예시로 소비성 아이템으로 설정
}
