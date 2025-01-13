#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    // 기본 생성자
    HealthPotion() : Item() {}
    // 생성자에서 Item 생성자 호출
    HealthPotion(const std::string& name, int price, int amount);
    std::string GetName() const override;
    void Use(Character* character) override;
};