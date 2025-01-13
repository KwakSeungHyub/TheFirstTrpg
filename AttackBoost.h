#pragma once
#include "Item.h"

class AttackBoost : public Item {
public:
    // 기본 생성자
    AttackBoost() : Item() {}
    // 생성자에서 Item 생성자 호출
    AttackBoost(const std::string& name, int price, int amount);
    // 이름과 가격만 전달, 수량은 기본값 1로 설정됨
    std::string GetName() const override;
    void Use(Character* character) override;
};
