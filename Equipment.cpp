#include "item.h"
#include "Equipment.h"

Equipment::Equipment(const std::string& name,int price,int bonusStat,EquipmentType type)
    : Item(name,price),BonusStat(bonusStat),Type(type) {}

void Equipment::Use(class Character* character) 
{
    // 장비 사용에 관한건 캐릭터에 전부 구현
}

std::string Equipment::GetName() const 
{
    return Name;
}

int Equipment::GetBonusStat() const 
{
    return BonusStat;
}


int Equipment::GetPrice() const {
    return Price;
}

bool Equipment::IsEquipable() const 
{
    return true;  // 예시로 항상 장착 가능하도록 설정
}

Equipment* Equipment::GetType() const 
{
    // EquipmentType을 Equipment*로 변환하여 반환하는 예시
    return const_cast<Equipment*>(this);
}