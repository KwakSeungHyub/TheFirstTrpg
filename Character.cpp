#include "Character.h"
#include "Shop.h"
#include "HealthPotion.h"
#include "RevivePotion.h"
#include <iostream>
#include "AttackBoost.h"

Character::Character(const std::string& name)
    : Name(name), Level(1), Health(100), MaxHealth(100), Attack(10), Experience(0), Gold(100), AttackBoostAmount(0), Defense(0) ,MaxExperience(100){}

// 레벨업 기능
void Character::LevelUp() 
{
    Level++;
    MaxHealth += 20;
    MaxExperience += 30;
    Attack += 5;
    Health = MaxHealth;
    std::cout << "레벨 업! 현재 레벨: " << Level << "!\n";
}

// 경험치 획득 및 레벨업 체크
void Character::GainExperience(int exp) 
{
    Experience += exp;
    std::cout << exp << " 경험치를 획득했습니다.\n";
    if(Experience >= Level * 100) 
    {
        Experience -= Level * 100;
        LevelUp();
    }
}

// 데미지 받기
void Character::TakeDamage(int damage) 
{
    int effectiveDamage = (damage > AttackBoostAmount) ? (damage - AttackBoostAmount) : 0;
    Health -= effectiveDamage;
    if(Health < 0) Health = 0;
    std::cout << Name << "이(가) " << effectiveDamage << " 피해를 입었습니다.\n";
    AutoUseItems();
    if(Health <= 0) 
    {
        std::cout << "당신은 패배했습니다.\n";
    }
}

// 캐릭터 상태 출력
void Character::DisplayStatus() const 
{
    std::cout << "이름: " << Name << ", 레벨: " << Level
        << ", 체력: " << Health << "/" << MaxHealth
        << ", 공격력: " << Attack
        << ", 골드: " << Gold << "\n";
}

// 상점 방문
void Character::VisitShop(Shop* shop) 
{
    int choice;
    do 
    {
        std::cout << "상점에 방문하셨습니다.\n";
        shop->DisplayItems();  // 상점 아이템 목록 표시
        std::cout << "1. 아이템 구매\n2. 아이템 판매\n3. 상점 떠나기\n";
        std::cout << "원하는 동작을 선택하세요: ";
        std::cin >> choice;

        if(choice == 1) 
        {
            int itemIndex;
            std::cout << "구매할 아이템 번호를 선택하세요: ";
            std::cin >> itemIndex;
            shop->BuyItem(itemIndex - 1,this);
        } 
        else if(choice == 2) 
        {
            SellItemAtShop(shop);
        } 
        else if(choice == 3) 
        {
            std::cout << "상점을 떠납니다.\n";
        } 
        else 
        {
            std::cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }
    } while(choice != 3);
}

// 인벤토리 표시
void Character::ShowInventory() const 
{
    std::cout << "인벤토리:\n";
    if(Inventory.empty()) 
    {
        std::cout << "인벤토리가 비어 있습니다.\n";
    } else 
    {
        for(const auto& item : Inventory) 
        {
            std::cout << item.first << ": " << item.second->GetAmount() << " 개\n";
        }
    }
}

// 아이템 추가
void Character::AddItem(std::unique_ptr<Item> item) 
{
    const std::string& itemName = item->GetName();
    if(Inventory.find(itemName) == Inventory.end()) 
    {
        Inventory[itemName] = std::move(item);  // 새 아이템 추가
    } 
    else 
    {
        Inventory[itemName]->IncreaseAmount(item->GetAmount());  // 기존 아이템 수량 증가
    }
}

// 상점에서 아이템 판매
void Character::SellItemAtShop(Shop* shop) 
{
    ShowInventory();
    std::cout << "판매할 아이템의 이름을 입력하세요: ";
    std::string itemName;
    std::cin >> itemName;

    auto it = Inventory.find(itemName);
    if(it != Inventory.end() && it->second->GetAmount() > 0) 
    {
        shop->SellItem(itemName,this);
    } else 
    {
        std::cout << "이 아이템을 가지고 있지 않습니다.\n";
    }
}


// 자동 아이템 사용 (전투 중)
void Character::AutoUseItems() 
{
        // 체력 포션 사용
        auto healthPotion = Inventory.find("체력 포션");
        if(Health <= MaxHealth / 2 && healthPotion != Inventory.end() && healthPotion->second->GetAmount() > 0) 
        {
                std::cout << "자동으로 체력 포션을 사용합니다!\n";
                healthPotion->second->Use(this);
                healthPotion->second->DecreaseAmount(1);
                if(healthPotion->second->GetAmount() == 0) 
                {
                    Inventory.erase(healthPotion);
                }
        }

        // 부활 포션 사용
        auto revivePotion = Inventory.find("부활 포션");
        if(Health <= 0 && revivePotion != Inventory.end() && revivePotion->second->GetAmount() > 0) 
        {
                std::cout << "자동으로 부활 포션을 사용합니다!\n";
                revivePotion->second->Use(this);
                revivePotion->second->DecreaseAmount(1);
                if(revivePotion->second->GetAmount() == 0) 
                {
                    Inventory.erase(revivePotion);
                }
                Health = MaxHealth;
        }

        // 공격력 포션 사용
        auto attackBoostPotion = Inventory.find("공격력 포션");
        if(attackBoostPotion != Inventory.end() && attackBoostPotion->second->GetAmount() > 0) 
        {
                std::cout << "자동으로 공격력 포션을 사용합니다!\n";
                attackBoostPotion->second->Use(this);
                attackBoostPotion->second->DecreaseAmount(1);
                if(attackBoostPotion->second->GetAmount() == 0) 
                {
                    Inventory.erase(attackBoostPotion);
                }
                AttackBoostAmount = 10;
                Attack += AttackBoostAmount;
        }
        // 자동으로 최적의 무기와 방어구 장착
        AutoEquipItems();
}


// 공격력 초기화
void Character::ResetAttackBoost()
{
    Attack -= AttackBoostAmount;
    AttackBoostAmount = 0;
    std::cout << "전투가 끝났습니다. 공격력이 초기화되었습니다. 현재 공격력: " << Attack << "\n";
}

void Character::EquipWeapon(Equipment* weapon) 
{
    if(weapon && weapon->GetEquimentType() == Equipment::EquipmentType::Weapon)
    {
        // 이전 무기 제거
        if(EquippedWeapon) 
        {
            Attack -= EquippedWeapon->GetBonusStat(); // 기존 무기 효과를 빼는 부분
        }
        // 새 무기 장착
        EquippedWeapon = weapon;
        Attack += weapon->GetBonusStat(); // 새 무기 추가 효과

        // 포인터 상태 점검
        std::cout << "새로운 무기 장착: " << (EquippedWeapon ? EquippedWeapon->GetName() : "없음") << "\n";
    }
}

void Character::EquipArmor(Equipment* armor) {
    if(armor && armor -> GetEquimentType() == Equipment::EquipmentType::Armor) 
        {
            // 이전에 장착한 방어구가 있다면 해당 방어구 효과를 뺀다.
            if(EquippedArmor != nullptr) {
                Defense -= EquippedArmor->GetBonusStat();
        }

        // 새로운 방어구를 장착하고, 방어력 증가
        EquippedArmor = armor;
        Defense += armor->GetBonusStat();  // 방어구의 방어력 추가

        // 포인터 상태 점검
        std::cout << "새로운 방어구 장착: " << (EquippedArmor ? EquippedArmor->GetName() : "없음") << "\n";
    } else {
        std::cout << "장착할 수 있는 방어구가 아닙니다.\n";
    }
}






void Character::AutoEquipItems() {
    Equipment* bestWeapon = nullptr;
    Equipment* bestArmor = nullptr;

    // 인벤토리에서 가장 좋은 무기와 방어구를 찾음
    for(const auto& item : Inventory) {
        const auto& itemPtr = item.second;

        // 아이템이 Equipment 타입일 경우만 처리
        Equipment* equipmentItem = dynamic_cast<Equipment*>(itemPtr.get());
        if(!equipmentItem) {
            continue;  // Equipment가 아니면 건너뛰기
        }

        // equipmentItem->GetType()은 EquipmentType을 반환하므로,
        // 바로 CompareEquipmentType에 넘겨주면 됩니다.
        // AutoEquipItems 함수에서 비교
        // 무기 비교
        if(equipmentItem->GetEquimentType() == Equipment::EquipmentType::Weapon) {
            if(!bestWeapon || equipmentItem->GetBonusStat() > bestWeapon->GetBonusStat()) {
                bestWeapon = equipmentItem;
            }
        }

        // 방어구 비교
        if(equipmentItem->GetEquimentType() == Equipment::EquipmentType::Armor) {
            if(!bestArmor || equipmentItem->GetBonusStat() > bestArmor->GetBonusStat()) {
                bestArmor = equipmentItem;
            }
        }




    }

    // 최적의 무기 장착
    if(bestWeapon) {
        EquipWeapon(bestWeapon);  // 새 무기 장착
        std::cout << bestWeapon->GetName() << "을(를) 무기로 장착합니다.\n";
        std::cout<< "현재 공격력은 " << Attack << "입니다.\n";
        Inventory.erase(bestWeapon->GetName());  // 인벤토리에서 제거
    }

    // 최적의 방어구 장착
    if(bestArmor) {
        EquipArmor(bestArmor);  // 새 방어구 장착
        std::cout << bestArmor->GetName() << "을(를) 방어구로 장착합니다.\n";
        std::cout << "현재 방어력은 " << Defense << "입니다.\n";
        Inventory.erase(bestArmor->GetName());  // 인벤토리에서 제거
    }
}