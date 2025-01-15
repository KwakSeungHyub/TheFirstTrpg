#include "Character.h"
#include "Shop.h"
#include "HealthPotion.h"
#include "RevivePotion.h"
#include <iostream>
#include "AttackBoost.h"
using namespace std;


Character::Character(const std::string& name)
    : Name(name), Level(1), Health(100), MaxHealth(100), Attack(10), Experience(0), Gold(100), AttackBoostAmount(0), Defense(0), MaxExperience(100) {
}

// 레벨업 기능
void Character::LevelUp(int &mini, int &max)
{
    Level++;
    MaxHealth += 20;
    MaxExperience += 15;
    Attack += 5;
    Health = MaxHealth;
    Experience;
    mini += 50;
    max += 50;
    std::cout << "레벨 업! 현재 레벨: " << Level << "!\n";
}


// 경험치 획득 및 레벨업 체크
void Character::GainExperience(int exp, int &mini, int &max)
{
    Experience += exp;
    std::cout << exp << " 경험치를 획득했습니다.\n";
    
    // 경험치가 최대 경험치를 초과할 경우 처리
    while (Experience >= MaxExperience) {
        int overflow = Experience - MaxExperience; // 초과된 경험치
        Experience = overflow; // 초과 경험치를 현재 경험치로 설정
        LevelUp(mini,max); // 레벨업
    }
    
    // 레벨업 후에 전체 경험치(MaxExperience) 갱신
    std::cout << "현재 경험치: " << Experience << " / " << MaxExperience << std::endl;
}


// 데미지 받기
void Character::TakeDamage(int damage)
{
    int effectiveDamage = (damage > AttackBoostAmount) ? (damage - AttackBoostAmount) : 0;
    Health -= effectiveDamage;
    if (Health < 0) Health = 0;
    std::cout << Name << "이(가) " << effectiveDamage << " 피해를 입었습니다.\n";
    AutoUseItems();
    if (Health <= 0)
    {
        std::cout << "당신은 패배했습니다.\n";
    }
}

// 상태창 출력
void Character::DisplayStatus() const {
    cout << " 이름  :  " << Name << endl;
    cout << " 레벨  :  " << Level << endl;
    cout << " 체력  :  " << Health << "/" << MaxHealth << endl;
    cout << "공격력 :  " << Attack << endl;
    cout << "방어력 :  " << Defense << endl;
    cout << " 골드  :  " << Gold << endl;
    cout << " EXP   :  " << Experience << "/" << MaxExperience << endl;
    cout << "=======================\n";
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

        if (choice == 1)
        {
            int itemIndex;
            std::cout << "구매할 아이템 번호를 선택하세요: ";
            std::cin >> itemIndex;
            shop->BuyItem(itemIndex - 1, this);
        }
        else if (choice == 2)
        {
            SellItemAtShop(shop);
        }
        else if (choice == 3)
        {
            std::cout << "상점을 떠납니다.\n";
        }
        else
        {
            std::cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }
    } while (choice != 3);
}

// 인벤토리 표시
void Character::ShowInventory() const
{
    cout << "\n==================================\n";
    std::cout << "인벤토리:\n";
    if (Inventory.empty())
    {
        std::cout << "인벤토리가 비어 있습니다.\n";
    }
    else
    {
        for (const auto& item : Inventory)
        {
            std::cout << item.first << ": " << item.second->GetAmount() << " 개\n";
        }
    }
}

// 아이템 추가
void Character::AddItem(std::unique_ptr<Item> item)
{
    const std::string& itemName = item->GetName();
    if (Inventory.find(itemName) == Inventory.end())
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
    if (it != Inventory.end() && it->second->GetAmount() > 0)
    {
        shop->SellItem(itemName, this);
    }
    else
    {
        std::cout << "이 아이템을 가지고 있지 않습니다.\n";
    }
}


// 자동 아이템 사용 (전투 중)
void Character::AutoUseItems()
{
    // 체력 포션 사용
    auto healthPotion = Inventory.find("체력 포션");
    if (Health <= MaxHealth / 2 && healthPotion != Inventory.end() && healthPotion->second->GetAmount() > 0)
    {
        std::cout << "자동으로 체력 포션을 사용합니다!\n";
        healthPotion->second->Use(this);
        healthPotion->second->DecreaseAmount(1);
        if (healthPotion->second->GetAmount() == 0)
        {
            Inventory.erase(healthPotion);
        }
    }

    // 부활 포션 사용
    auto revivePotion = Inventory.find("부활 포션");
    if (Health <= 0 && revivePotion != Inventory.end() && revivePotion->second->GetAmount() > 0)
    {
        std::cout << "자동으로 부활 포션을 사용합니다!\n";
        revivePotion->second->Use(this);
        revivePotion->second->DecreaseAmount(1);
        if (revivePotion->second->GetAmount() == 0)
        {
            Inventory.erase(revivePotion);
        }
        Health = MaxHealth;
    }

    // 공격력 포션 사용
    auto attackBoostPotion = Inventory.find("공격력 포션");
    // 공격력 포션이 있고, 이미 사용한 적이 없는 경우만 허용
    if(attackBoostPotion != Inventory.end() && AttackBoostAmount == 0) {
        if(attackBoostPotion->second->GetAmount() > 0) {  // 포션 수량 확인
            if(AttackBoostAmount == 0) {  // 아직 사용하지 않은 경우
                std::cout << "자동으로 공격력 포션을 사용합니다!\n";
                attackBoostPotion->second->Use(this);  // 포션 사용
                attackBoostPotion->second->DecreaseAmount(1);  // 포션 수량 감소

                // 포션 수량 0일 시 인벤토리에서 제거
                if(attackBoostPotion->second->GetAmount() == 0) {
                    Inventory.erase(attackBoostPotion);
                }

                // 포션 사용 상태 기록 (AttackBoostAmount를 사용했음을 기록)
                AttackBoostAmount = 1;  // 포션을 사용한 상태로 설정
            } else {
                std::cout << "이미 공격력 포션을 사용하여 추가 사용이 불가능합니다!\n";
            }
        } else {
            std::cout << "공격력 포션이 없습니다!\n";  // 포션이 수량이 0일 때 메시지 출력
        }
    } 
}


// 공격력 초기화
void Character::ResetAttackBoost()
{
    // 공격력 10만큼 감소 공격력 포션을 먹었을 때만 적용되게(효과 제거)
    if(AttackBoostAmount == 1) 
    {
        Attack -= 10;
        std::cout << "전투가 끝났습니다. 공격력이 초기화되었습니다. 현재 공격력: " << Attack << "\n";
        AttackBoostAmount = 0;
    }
    
    
}

// 무기 장착
bool Character::EquipWeapon(Equipment* weapon)
{
    // 무기가 유효한지, Equipment 타입인지 체크
    if(weapon && weapon->GetEquimentType() == Equipment::EquipmentType::Weapon)
    {
        // 기존 무기 해제 처리
        if(EquippedWeapon != nullptr)
        {
            // 기존 무기와 새 무기의 보너스 스탯을 비교하여, 새로운 무기가 더 나은 경우에만 교체
            if(weapon->GetBonusStat() > EquippedWeapon->GetBonusStat())
            {
                Attack -= EquippedWeapon->GetBonusStat();  // 기존 무기 효과 제거
                std::cout << "기존 무기 " << EquippedWeapon->GetName() << "의 효과가 제거되었습니다.\n";

                // 기존 무기를 인벤토리에 다시 추가
                auto it = Inventory.find(EquippedWeapon->GetName());
                if(it == Inventory.end()) {
                    Inventory[EquippedWeapon->GetName()] = std::make_unique<Equipment>(*EquippedWeapon);
                }
            } else
            {
                std::cout << "현재 무기가 더 좋습니다. 장비를 교체하지 않습니다.\n";
                return false;  // 새 무기가 기존 무기보다 나쁘므로 장착하지 않음
            }
        }

        // 새로운 무기 장착
        EquippedWeapon = weapon;
        Attack += weapon->GetBonusStat();  // 새 무기 보너스 추가
        std::cout << weapon->GetName() << " 무기가 장착되었습니다. 현재 공격력: " << Attack << "\n";

        return true;  // 장착 성공
    } else
    {
        std::cout << "장착할 수 있는 무기가 아닙니다.\n";
        return false;  // 장착 실패
    }
}

// 방어구 장착
bool Character::EquipArmor(Equipment* armor)
{
    // 방어구가 유효한지, Equipment 타입인지 체크
    if(armor && armor->GetEquimentType() == Equipment::EquipmentType::Armor)
    {
        // 기존 방어구 해제 처리
        if(EquippedArmor != nullptr)
        {
            // 기존 방어구와 새 방어구의 보너스 스탯을 비교하여, 새로운 방어구가 더 나은 경우에만 교체
            if(armor->GetBonusStat() > EquippedArmor->GetBonusStat())
            {
                Defense -= EquippedArmor->GetBonusStat();  // 기존 방어구 효과 제거
                std::cout << "기존 방어구 " << EquippedArmor->GetName() << "의 효과가 제거되었습니다.\n";

                // 기존 방어구를 인벤토리에 다시 추가
                auto it = Inventory.find(EquippedArmor->GetName());
                if(it == Inventory.end())
                {
                    Inventory[EquippedArmor->GetName()] = std::make_unique<Equipment>(*EquippedArmor);
                }
            } else
            {
                std::cout << "현재 방어구가 더 좋습니다. 장비를 교체하지 않습니다.\n";
                return false;  // 새 방어구가 기존 방어구보다 나쁘므로 장착하지 않음
            }
        }

        // 새로운 방어구 장착
        EquippedArmor = armor;
        Defense += armor->GetBonusStat();  // 새 방어구 보너스 추가
        std::cout << armor->GetName() << " 방어구가 장착되었습니다. 현재 방어력: " << Defense << "\n";

        return true;  // 장착 성공
    } else
    {
        std::cout << "장착할 수 있는 방어구가 아닙니다.\n";
        return false;  // 장착 실패
    }
}



