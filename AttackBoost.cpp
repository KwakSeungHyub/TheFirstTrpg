#include "AttackBoost.h"
#include "Character.h"
#include <iostream>

AttackBoost::AttackBoost()
    : Item("공격력 포션", 50) {  // 부모 클래스에 한글 이름 전달
}

std::string AttackBoost::GetName() const {
    return Name;  // 부모 클래스에서 초기화된 Name을 반환
}

void AttackBoost::Use(Character* character) {
    character->Attack += 10;
    std::cout << character->Name << "의 공격력 10 증가!(스테이지 종료 후 초기화)\n";
}
