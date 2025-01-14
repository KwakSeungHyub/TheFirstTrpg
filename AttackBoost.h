
#pragma once
#include "Item.h"
#include "Equipment.h"

class AttackBoost: public Item 
{
public:
    // 생성자
    AttackBoost(const std::string& name,int price,int amount = 1) {};

    // Use 함수 구현 (공격력 증가 효과)
    void Use(Character* character) override;

    // 장비 타입 반환 (Equipment*로 수정)
    Equipment* GetType() const override;
};
