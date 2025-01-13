#pragma once
#include "Item.h"

class AttackBoost : public Item {
public:
    AttackBoost();  // »ý¼ºÀÚ
    std::string GetName() const override;
    void Use(Character* character) override;
};
