#include "AttackBoost.h"
#include "Character.h"
#include <iostream>


AttackBoost::AttackBoost(const std::string& name, int price, int amount)
    : Item(name, price, amount) {
    // 추가 초기화가 필요하다면 여기에 작성
}


std::string AttackBoost::GetName() const {
    return Name;  // 부모 클래스에서 초기화된 Name을 반환
}

void AttackBoost::Use(Character* character) {
    character->Attack += 10;
    std::cout << character->Name << "의 공격력 10 증가!(스테이지 종료 후 초기화)\n";
}
