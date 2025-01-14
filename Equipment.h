#pragma once
#include "Item.h"  // Item.h 포함

class Equipment : public Item 
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
        // Type에 대한 Getter
        EquipmentType GetEquimentType() const { return Type; } // EquipmentType 반환

        // Equipment 클래스 내부에서 CompareEquipmentType 함수 정의
        // static으로 정의된 함수로 비교를 단순화할 수 있습니다.
        static bool CompareEquipmentType(Equipment::EquipmentType lhs, Equipment::EquipmentType rhs) {
            return lhs == rhs;
        }



        Equipment(const std::string& name, int price, int bonusStat, EquipmentType type);

        // 메서드 오버라이드
        void Use(class Character* character) override;

        std::string GetName() const override;
        int GetBonusStat() const override;
        int GetPrice() const override;
        bool IsEquipable() const override;
    
        Equipment* GetType() const override;  // 반환 형식을 Equipment*로 유지

    private:
        int BonusStat;
        EquipmentType Type;
};
