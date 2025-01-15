#include "AttackBoost.h"
#include "Character.h"
#include <iostream>

// 생성자
AttackBoost::AttackBoost(const std::string& name,int price,int amount)
    : Item(name,price,amount) {}
// Use 함수 구현 (공격력 증가 효과)
void AttackBoost::Use(Character* character)
{
    character->Attack += GetBonusStat() + 10;  // BonusStat은 기본값을 0으로 설정했지만, 자식 클래스에서 오버라이드할 수 있습니다.
    std::cout << Name << "을 사용하여 공격력이 10이 증가했습니다! 현재 공격력은 "<<character->Attack <<"입니다\n";
}

// 장비 타입 반환 (Equipment*로 반환)
Equipment* AttackBoost::GetType() const
{
    // Consumable 타입의 임시 Equipment 객체 반환
    static Equipment temp("AttackBoost", 50, 1, Equipment::EquipmentType::Consumable);
    return &temp;
}