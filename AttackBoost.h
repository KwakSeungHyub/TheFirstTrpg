#pragma once
#include "Item.h"

class AttackBoost : public Item {
public:
    AttackBoost();  //  기본 생성자 선언
    std::string GetName() const override;
    void Use(Character* character) override;
};
