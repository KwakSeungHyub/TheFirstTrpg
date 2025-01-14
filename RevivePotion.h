#pragma once
#include "Item.h"

class RevivePotion: public Item {
public:
    // 생성자
    RevivePotion(const std::string& name,int price,int amount = 1);

    void Use(Character* character) override;  // Use 함수 선언
    Equipment* GetType() const override;  // 장비 타입 반환 함수 선언
};