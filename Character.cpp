#include "Character.h"
#include "Shop.h"
#include "HealthPotion.h"
#include "RevivePotion.h"
#include <iostream>
#include "AttackBoost.h"

Character::Character(const std::string& name)
    : Name(name), Level(1), Health(100), MaxHealth(100), Attack(10), Experience(0), Gold(100), AttackBoostAmount(0){
}

// 레벨업 기능
void Character::LevelUp() {
    Level++;
    MaxHealth += 20;
    Attack += 5;
    Health = MaxHealth;
    std::cout << "레벨 업! 현재 레벨: " << Level << "!\n";
}

// 경험치 획득 및 레벨업 체크
void Character::GainExperience(int exp) {
    Experience += exp;
    if (Experience >= 100) {
        LevelUp();
        Experience = 0;
    }
}

// 체력 감소 및 자동 아이템 사용 (스마트 포인터 적용)
void Character::TakeDamage(int damage) {
    Health -= damage;
    std::cout << "데미지를 " << damage << "만큼 받았습니다. 현재 체력: " << Health << "\n";
    AutoUseItems();
    if (Health <= 0) {
        std::cout << "당신은 패배했습니다.\n";
    }
}

// 상태창 출력
void Character::DisplayStatus() const {
    std::cout << "이름: " << Name << ", 레벨: " << Level
        << ", 체력: " << Health << "/" << MaxHealth
        << ", 공격력: " << Attack
        << ", 골드: " << Gold << "\n";
}

// 상점 방문
void Character::VisitShop(Shop* shop) {
    int choice;
    do {
        std::cout << "상점에 방문하셨습니다.\n";
        shop->DisplayItems();  // 상점 아이템 목록 표시
        std::cout << "1. 아이템 구매\n2. 아이템 판매\n3. 상점 떠나기\n";
        std::cout << "원하는 동작을 선택하세요: ";
        std::cin >> choice;

        if (choice == 1) {
            // 아이템 구매
            std::cout << "구매할 아이템 번호를 선택하세요: ";
            int itemIndex;
            std::cin >> itemIndex;
            shop->BuyItem(itemIndex - 1, this);
        }
        else if (choice == 2) {
            // 아이템 판매
            SellItemAtShop(shop);
        }
        else if (choice == 3) {
            // 상점 떠나기
            std::cout << "상점을 떠납니다.\n";
        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }

    } while (choice != 3);  // 상점을 떠날 때까지 반복
}

// 인벤토리 표시
void Character::ShowInventory() const {
    std::cout << "인벤토리:\n";
    if (Inventory.empty()) {
        std::cout << "인벤토리가 비어 있습니다.\n";
    }
    else {
        for (const auto& item : Inventory) {
            std::cout << item.first << ": " << item.second << " 개\n";
        }
    }
}

/// 아이템 추가 (스마트 포인터 사용)
void Character::AddItem(std::unique_ptr<Item> item) {
    std::string itemName = item->GetName();

    // 영어 이름을 한글 이름으로 변경
    if (itemName == "Health Potion") {
        itemName = "체력 포션";
    }
    else if (itemName == "Attack Boost") {
        itemName = "공격력 포션";
    }
    else if (itemName == "Revive Potion") {
        itemName = "부활 포션";
    }

    Inventory[itemName]++;  // 한글 이름을 키로 아이템 개수 증가
    std::cout << "새로운 아이템을 획득했습니다: " << itemName << "!\n";
}

// 상점에서 아이템 판매 (판매 기능)
void Character::SellItemAtShop(Shop* shop) {
    ShowInventory();
    std::cout << "판매할 아이템의 이름을 입력하세요: ";
    std::string itemName;
    std::cin >> itemName;

    if (Inventory[itemName] > 0) {
        shop->SellItem(itemName, this);
    }
    else {
        std::cout << "이 아이템을 가지고 있지 않습니다.\n";
    }
}

// 자동 아이템 사용
void Character::AutoUseItems() {
    if (Health <= MaxHealth / 2 && Inventory["체력 포션"] > 0) {
        std::cout << "자동으로 체력 포션을 사용합니다!\n";
        std::shared_ptr<HealthPotion> potion = std::make_shared<HealthPotion>();
        potion->Use(this);
        Inventory["Health Potion"]--;
    }
    if (Health <= 0 && Inventory["부활 포션"] > 0) {
        std::cout << "자동으로 부활 포션을 사용합니다!\n";
        std::shared_ptr<RevivePotion> potion = std::make_shared<RevivePotion>();
        potion->Use(this);
        Inventory["부활 포션"]--;
        Health = MaxHealth;
    }
    if (Inventory["공격력 포션"] > 0) {
        std::cout << "자동으로 공격력 포션을 사용합니다!\n";
        AttackBoost potion;
        potion.Use(this);
        Inventory["Attack Boost"]--;
        AttackBoostAmount = 10;  // 포션으로 증가한 공격력
        Attack += AttackBoostAmount;  // 공격력 증가
    }
   
}
// 공격력 포션 효과 초기화 함수
void Character::ResetAttackBoost() {
    Attack -= AttackBoostAmount;  // 포션으로 증가한 공격력만큼 빼기
    AttackBoostAmount = 0;  // 포션 효과 초기화
    std::cout << "전투가 끝났습니다. 공격력이 초기화되었습니다. 현재 공격력: " << Attack << "\n";
}
