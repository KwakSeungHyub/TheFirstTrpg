#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    // 생성자
    HealthPotion(const std::string& name, int price, int amount = 1);

    // Use 함수 구현 (체력 회복 효과)
    virtual void Use(Character* character) override;

    // 장비 타입 반환 (Equipment*로 수정)
    Equipment* GetType() const override;
};
