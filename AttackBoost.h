#pragma once
#include "Item.h"

class AttackBoost : public Item {
public:
    std::string GetName() const override;
    void Use(Character* character) override;
};