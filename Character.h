#pragma once
#include "Equipment.h"
#include "Shop.h"
#include <unordered_map>  // unordered_map 헤더 추가
#include <string>

class Character {
public:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int AttackBoostAmount = 0;  // 포션으로 증가한 공격력 추적
    int Experience;
    int MaxExperience;
    int Defense = 0; // 방어력(장비로만 올라감)
    int Gold;
   

    // 스마트 포인터를 사용하는 인벤토리: 아이템과 해당 수량을 저장
    std::unordered_map<std::string, std::unique_ptr<Item>> Inventory;

    Equipment* EquippedWeapon = nullptr;  // 장착된 무기
    Equipment* EquippedArmor = nullptr;   // 장착된 방어구

    // 생성자
    Character(const std::string& name);

    // 레벨업 메소드
    void LevelUp(int &mini, int& max);

    // 경험치 획득 메소드
    void GainExperience(int exp,int &mi, int &ma);

    // 데미지 받기 메소드
    void TakeDamage(int damage);

    // 캐릭터 상태 출력
    void DisplayStatus() const;

    // 상점 방문 메소드
    void VisitShop(Shop* shop);

    // 인벤토리 표시
    void ShowInventory() const;

    // 아이템 추가 메소드
    void AddItem(std::unique_ptr<Item> item);

    // 상점에서 아이템 판매 메소드
    void SellItemAtShop(Shop* shop);

    // 전투 중 자동 아이템 사용 메소드
    void AutoUseItems();

    // 공격력 초기화 메소드 (버프 제거 시)
    void ResetAttackBoost();

    // 무기 장착 메소드
    bool EquipWeapon(Equipment* newWeapon);

    // 방어구 장착 메소드
    bool EquipArmor(Equipment* newArmor);



};