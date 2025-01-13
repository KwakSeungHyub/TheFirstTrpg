#pragma once
#include "Item.h"

class RevivePotion : public Item {
public:
    // 기본 생성자
    RevivePotion() : Item() {}
    // 생성자에서 Item 생성자 호출
    RevivePotion(const std::string& name, int price, int amount);
    std::string GetName() const override;
    void Use(Character* character) override;
};
