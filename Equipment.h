#pragma once
#include "Item.h"  // Item.h 포함

class Equipment: public Item
{
public:
    enum class EquipmentType
    {
        Weapon,
        Armor,
        Accessory,
        Consumable,
        Misc
    };

    Equipment(const std::string& name,int price,int bonusStat,EquipmentType type);

    // 메서드 오버라이드
    void Use(class Character* character) override;

    std::string GetName() const override;
    int GetBonusStat() const override;
    int GetPrice() const override;
    bool IsEquipable() const override;

    Equipment::EquipmentType GetEquimentType() const;

    Equipment* GetType() const override;  // 반환 형식을 Equipment*로 유지

    std::string GetTypeText() const;

    static bool CompareEquipmentType(EquipmentType lhs,EquipmentType rhs);

private:
    int BonusStat;
    EquipmentType Type;
};
