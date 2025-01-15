#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

// 생성자
HealthPotion::HealthPotion(const std::string& name, int price, int amount)
    : Item(name, price, amount) {
}

// Use 함수 구현 (체력 회복 효과)
void HealthPotion::Use(Character* character) {
    character->Health += 50;  // 예시로 체력 50 회복
    std::cout << Name << "을 사용하여 체력이 50만큼 회복되었습니다!\n";
}

// 장비 타입 반환
Equipment* HealthPotion::GetType() const {
    static Equipment temp("체력 포션", 50, 0, Equipment::EquipmentType::Consumable);
    return &temp;
}