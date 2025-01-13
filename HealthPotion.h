#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    HealthPotion();  // 기본 생성자 선언
    std::string GetName() const override;
    void Use(Character* character) override;
};