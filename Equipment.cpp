#include "Equipment.h"

Equipment::Equipment(const std::string& name,int price,int bonusStat,EquipmentType type)
    : Item(name,price),BonusStat(bonusStat),Type(type) {}

void Equipment::Use(Character* character)
{
    // 장비 사용 시 처리할 로직
    // 예: 체력 증가, 공격력 증가 등
}

std::string Equipment::GetName() const
{
    return Name;  // Equipment의 이름 반환
}

int Equipment::GetBonusStat() const
{
    return BonusStat;  // 장비의 보너스 스탯 반환
}

int Equipment::GetPrice() const
{
    return Price;  // 장비의 가격 반환
}

bool Equipment::IsEquipable() const
{
    return true;  // 장비는 착용 가능하므로 true 반환
}

Equipment::EquipmentType Equipment::GetEquimentType() const
{
    return Type;
}

std::string Equipment::GetTypeText() const
{
    switch(Type)
    {
    case EquipmentType::Weapon:
    return "Weapon";
    case EquipmentType::Armor:
    return "Armor";
    case EquipmentType::Accessory:
    return "Accessory";
    case EquipmentType::Consumable:
    return "Consumable";
    case EquipmentType::Misc:
    return "Misc";
    default:
    return "Unknown";
    }
}

Equipment* Equipment::GetType() const
{
    return const_cast<Equipment*>(this);  // 현재 객체의 주소 반환
}

bool Equipment::CompareEquipmentType(Equipment::EquipmentType lhs,Equipment::EquipmentType rhs)
{
    return lhs == rhs;
}
