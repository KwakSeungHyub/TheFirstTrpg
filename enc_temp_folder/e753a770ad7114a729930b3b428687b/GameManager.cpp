
#include "GameManager.h"
#include <iostream>
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include "Equipment.h"
#include <map>
using namespace std;

std::unique_ptr<Monster> GameManager::GenerateRandomMonster(int level)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rand_seed(0, 3);
    
    int randomMonster = rand_seed(gen);  // 0부터 3까지 랜덤 숫자 생성

    std::unique_ptr<Monster> monster;

    switch (randomMonster) {
    case 0:
        cout << "\n========================\n";
        std::cout << "슬라임을 마주쳤다!\n";
        monster = std::make_unique<Slime>(level);  // Slime 클래스 사용
        break;
    case 1:
        cout << "\n========================\n";
        std::cout << "고블린을 마주쳤다!\n";
        monster = std::make_unique<Goblin>(level);  // Goblin 클래스 사용
        break;
    case 2:
        cout << "\n========================\n";
        std::cout << "트롤을 마주쳤다!\n";
        monster = std::make_unique<Troll>(level);  // Troll 클래스 사용
        break;
    case 3:
        cout << "\n========================\n";
        std::cout << "오크를 마주쳤다!\n";
        monster = std::make_unique<Orc>(level);  // Orc 클래스 사용
        break;
    default:
        cout << "\n========================\n";
        std::cout << "기본 몬스터를 마주쳤다!\n";
        monster = std::make_unique<Monster>(level);  // 기본 몬스터
        break;
    }

    return monster;  // 생성된 몬스터 리턴
}





void GameManager::StartGame(Character* player, Shop* shop)
{
    int choice;
    do {
        std::cout << "\n======캐릭터 스탯======\n";
        player->DisplayStatus();

        std::cout << "\n어떤 활동을 하시겠습니까?\n";
        std::cout << "1. 전투\n2. 상점 방문\n3. 인벤토리 확인\n4. 게임 종료\n";
        std::cout << "원하는 동작을 선택하세요: ";
        std::cin >> choice;
        std::cin.ignore(); // 버퍼 비우기

        if (choice == 1)
        {
            // 레벨 10 이상일 때 보스 몬스터와 전투
            if (player->Level >= 10)
            {
                BossBattle(player);
                break;  // 보스 전투 후 게임 종료
            }
            else
            {
                Battle(player);  // 일반 몬스터와 전투
            }
        }
        else if (choice == 2)
        {
            VisitShop(player, shop, this);  // gameManager 제거하고 직접 호출
        }
        else if (choice == 3)
        {
            DisplayInventory(player);
        }
        else if (choice == 4)
        {
            std::cout << "게임을 종료합니다.\n";
        }
        else
        {
            std::cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }
    } while (choice != 4);
}
// 보스 몬스터 생성
std::unique_ptr<BossMonster> GameManager::GenerateBossMonster(int level)
{
    std::cout << "마왕의 성에 도착했다!\n";
    return std::make_unique<BossMonster>(level);  // BossMonster 클래스를 사용
}

void GameManager::Battle(Character* player)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(10,20);
    int rand_gold = dist(gen);




    // 랜덤 몬스터 생성
    std::unique_ptr<Monster> monster = GenerateRandomMonster(player->Level);

    // 전투 시작 전에 아이템 자동 사용
    player->AutoUseItems();

    int turn = 1; // 몬스터와 턴제로 몇번 싸우는걸 출력하기위해서

    std::cout << "\n야생 " << monster->Name << "(이)가 나타났습니다.\n\n";
    std::cout << " 레벨  : " << monster->Level << "\n";
    std::cout << " 체력  : " << monster->Health << "\n";
    std::cout << "공격력 : " << monster->Attack << "\n";
    std::cout << "방어력 : " << monster->Defense << "\n";
    cout << "=========================\n";
    cout << "\n싸우시겠습니까?\n";
    cout << "\n1. 싸운다\n";
    cout << "2. 돌아간다\n";
    cout << "원하는 동작을 선택하세요: ";
    int choice;
    cin >> choice;

    // 1을 누르면 전투시작
    if (choice == 1)
    {
        //전투 들어가기 전 공격력 포션 먹기 위한 autouseItem 호출
        player -> AutoUseItems();
        cout << "\n==================================\n";
        std::cout << player->Name << "와 " << monster->Name << "의 전투가 시작됩니다!\n";
        cout << "==================================\n\n";
        while (monster->Health > 0 && player->Health > 0)
        {
            cout << "-------------------------------------------------------\n";
            cout << turn << " 번째 턴" << "\n";
            turn++;
            // 플레이어의 공격
            int damageToMonster = std::max(0,player->Attack - monster->Defense); // 방어력 차감
            cout << damageToMonster<< "만큼의 피해를 입혔습니다.\n";
            monster->Health -= damageToMonster;
            monster->Health = max(0, monster->Health);  // 몬스터의 음수 체력 방지
            // 피해 계산 시 방어력만 고려 (EquippedArmor에 의한 추가 방어력은 이미 반영됨)
            cout << player->Name << "의 공격! " << monster->Name << " 에게 " << damageToMonster << "만큼의 피해를 입혔습니다.\n";
            cout << monster->Name << "체력: " << monster->Health << " / " << monster->MaxHealth << "\n";
            
            int damageToPlayer = std::max(0,monster->Attack - player->Defense); // 방어력 차감
            player->Health -= damageToPlayer;
            player->Health = max(0, player->Health);  // 플레이어의 음수 체력 방지
            // 피해 계산 시 방어력만 고려 (EquippedArmor에 의한 추가 방어력은 이미 반영됨)
            cout << monster->Name << "의 반격! " << player->Name << " 에게 " << damageToPlayer << "만큼의 피해를 입혔습니다.\n";
            cout << player->Name << "체력: " << player->Health << " / " << player->MaxHealth << "\n";
            player -> AutoUseItems();
        }
        cout << "-------------------------------------------------------\n";
        // 전투에서 이기면 경험치 획득
        if (monster->Health <= 0)
        {
            std::cout << monster->Name << "을 처치했습니다!\n";
            player ->GainExperience(100);  // 경험치 획득
            player ->Gold += rand_gold; //골드 획득
            player -> ResetAttackBoost();
            // 전리품 드롭
            std::unique_ptr<Item> loot = monster->DropItem();
            if (loot != nullptr) {
                std::cout << "전리품으로 " << loot->GetName() << "을(를) 획득했습니다!\n";
                player->AddItem(std::move(loot));  // 인벤토리에 아이템 추가
            }
            else {
                std::cout << "전리품이 없습니다.\n";
            }
        } // 플레이어가 패배하면 게임 종료
        else if (player->Health <= 0)
        {
            player->Health = 0;
            std::cout << player->Name << "이(가) 쓰러졌습니다. 게임 오버.\n";
            exit(0);  // 프로그램 종료
        }
    }
    else if (choice == 2)
    {
        cout << "==================================\n";
        cout << "몬스터와 전투를 피하고 돌아갑니다.\n";
        cout << "==================================\n";
    }
    else
    {
        cout << "잘못된 입력입니다.";
    }
}


void GameManager::BossBattle(Character* player)
{
    // 랜덤 보스 몬스터 생성 (보스 몬스터는 레벨과 능력치가 높을 수 있음)
    std::unique_ptr<Monster> boss = GenerateBossMonster(player->Level);

    // 전투 시작 전에 아이템 자동 사용
    player->AutoUseItems();
    cout << "\n============================\n";
    std::cout << boss->Name << "이 나타났다!\n";
    std::cout << "보스 레벨: " << boss->Level << "\n";
    std::cout << "보스 체력: " << boss->Health << "\n";
    std::cout << "보스 공격력: " << boss->Attack << "\n";
    std::cout << "보스 공격력: " << boss->Defense << "\n";
    // 보스 몬스터가 존재하면 전투 시작
    if (boss != nullptr)
    {
        std::cout << player->Name << "와 " << boss->Name << "의 보스 전투가 시작됩니다!\n";
        while (boss->Health > 0 && player->Health > 0)
        {
            // 플레이어의 공격
            int damageToBoss = std::max(0,player->Attack - boss->Defense); // 방어력 차감
            boss->Health -= damageToBoss;
            boss->Health = max(0,boss->Health);  // 몬스터의 음수 체력 방지
            // 피해 계산 시 방어력만 고려 (EquippedArmor에 의한 추가 방어력은 이미 반영됨)
            cout << player->Name << "의 공격! " << boss->Name << " 에게 " << damageToBoss << "만큼의 피해를 입혔습니다.\n";
            cout << boss->Name << "체력: " << boss->Health << " / " << boss->MaxHealth << "\n";
            
            int damageToPlayer = std::max(0,boss->Attack - player->Defense); // 방어력 차감
            player->Health -= boss->Attack;
            player->Health = max(0,player->Health);  // 플레이어의 음수 체력 방지
            // 피해 계산 시 방어력만 고려 (EquippedArmor에 의한 추가 방어력은 이미 반영됨)
            
            cout << boss->Name << "의 반격! " << player->Name << " 에게 " << damageToPlayer << "만큼의 피해를 입혔습니다.\n";
            cout << player->Name << "체력: " << player->Health << " / " << player->MaxHealth << "\n";
            player->AutoUseItems();
            // 상태 출력
            std::cout << player->Name << "의 체력: " << player->Health << "\n";
            std::cout << boss->Name << "의 체력: " << boss->Health << "\n";
        }

        // 전투 결과
        if (boss->Health <= 0)
        {
            std::cout << boss->Name << "을 처치했습니다!\n";
            player->GainExperience(500);  // 보스 처치 시 높은 경험치 획득

            // 전리품 드롭
            std::unique_ptr<Item> loot = boss->DropItem();
            if (loot != nullptr) {
                std::cout << "전리품으로 " << loot->GetName() << "을(를) 획득했습니다!\n";
                player->AddItem(std::move(loot));  // 인벤토리에 아이템 추가
            }
            else {
                std::cout << "전리품이 없습니다.\n";
            }

            // 게임 클리어 메시지 출력
            std::cout << player->Name << "님, 보스를 처치하여 게임을 클리어했습니다!\n";
            std::cout << "축하합니다! 게임을 클리어하셨습니다!\n";

            // 게임 종료 처리
            exit(0);  // 프로그램 종료
        }
        else
        {
            std::cout << player->Name << "이(가) 쓰러졌습니다. 게임 오버.\n";
            exit(0);  // 프로그램 종료
        }
    }
    else {
        std::cout << "보스 몬스터가 존재하지 않습니다!\n";
    }

    player->DisplayStatus();  // 전투 후 상태 표시
}

void GameManager::VisitShop(Character* player, Shop* shop, GameManager* gameManager)
{
    while (true)
    {
        cout << "\n====================================================\n";
        std::cout << "상점에 오신 것을 환영합니다! 무엇을 하시겠습니까?\n\n";
        std::cout << "1. 사용 아이템 구매\n";
        std::cout << "2. 장비 아이템 구매\n";
        std::cout << "3. 아이템 판매\n";
        std::cout << "4. 아이템 목록 확인\n";
        std::cout << "5. 상점 종료\n";
        cout << "선택해주세요 :";

        int choice;
        std::cin >> choice;

        int index = 0;
        std::vector<std::string> itemNames;
        std::unordered_map<std::string, std::unique_ptr<Item>>::iterator itemToSell;  // 여기서 초기화해주면 됨

        switch(choice)
        {
        case 1:  // 사용 아이템 구매
        cout << "\n=============================================\n";
        std::cout << "사용 아이템 목록입니다. 현재 보유 골드(" << player->Gold << ")\n\n";
        std::cout << "1. 체력 포션 (20 골드) : 체력 50을 회복합니다\n";
        std::cout << "2. 공격력 포션 (50 골드) : 전투 시작 시 공격력 10을 증가합니다. \n";
        std::cout << "3. 부활 포션 (100 골드) : 죽음에 이르렀을 시 살아납니다.\n";
        std::cout << "4. 뒤로가기\n";
        cout << "선택해주세요 :";
        int buyChoice;
        std::cin >> buyChoice;

        switch(buyChoice)
        {
        case 1:  // 체력 포션
        if(player->Gold >= 20)
        {
            auto it = player->Inventory.find("체력 포션");
            if(it != player->Inventory.end())
            {
                // 기존 아이템의 수량 증가
                it->second->IncreaseAmount(1);
            } else
            {
                // 새 아이템을 인벤토리에 추가
                player->AddItem(std::make_unique<HealthPotion>("체력 포션",20,1));
                player->ShowInventory();
            }
            player->Gold -= 20;
            std::cout << "체력 포션을 구매했습니다.\n";
        } else
        {
            std::cout << "골드가 부족합니다.\n";
        }
        break;

        case 2:  // 공격력 포션
        if(player->Gold >= 50)
        {
            auto it = player->Inventory.find("공격력 포션");
            if(it != player->Inventory.end())
            {
                // 기존 아이템의 수량 증가
                it->second->IncreaseAmount(1);
            } else
            {
                // 새 아이템을 인벤토리에 추가
                player->AddItem(std::make_unique<AttackBoost>("공격력 포션",50,1));
                player->ShowInventory();
            }
            player->Gold -= 50;
            std::cout << "공격력 포션을 구매했습니다.\n";
        } else
        {
            std::cout << "골드가 부족합니다.\n";
        }
        break;

        case 3:  // 부활 포션
        if(player->Gold >= 100)
        {
            auto it = player->Inventory.find("부활 포션");
            if(it != player->Inventory.end())
            {
                // 기존 아이템의 수량 증가
                it->second->IncreaseAmount(1);
            } else
            {
                // 새 아이템을 인벤토리에 추가
                player->AddItem(std::make_unique<RevivePotion>("부활 포션",100,1));
            }
            player->Gold -= 100;
            std::cout << "부활 포션을 구매했습니다.\n";
        } else
        {
            std::cout << "골드가 부족합니다.\n";
        }
        break;


        case 4:  // 뒤로가기
        std::cout << "상점으로 돌아갑니다.\n";
        break;
        }
        break;

        case 2:  // 장비 아이템 구매
        cout << "\n=================================================\n";
        std::cout << "\n장비 아이템 목록입니다. 현재 보유 골드(" << player->Gold << ")\n";
        std::cout << "1. 목검 (100 골드)\n";
        std::cout << "2. 나무갑옷 (100 골드)\n";
        std::cout << "3. 구리검 (200 골드)\n";
        std::cout << "4. 구리갑옷 (200 골드)\n";
        std::cout << "5. 철검 (500 골드)\n";
        std::cout << "6. 철갑옷 (500 골드)\n";
        std::cout << "7. 미스릴 창(1000 골드)\n";
        std::cout << "8. 미스릴 갑옷 (1000 골드)\n";
        std::cout << "9. 드래곤슬레이어 (2000 골드)\n";
        std::cout << "0. 드래곤비늘갑옷 (2000 골드)\n";
        std::cout << "99. 뒤로가기\n";

        std::cin >> buyChoice;

        switch(buyChoice)
        {
        case 1:  // 목검 (무기)
        gameManager->PurchaseEquipment(player,"목검",100,3,Equipment::EquipmentType::Weapon);
        break;

        case 2:  // 나무갑옷 (방어구)
        gameManager->PurchaseEquipment(player,"나무갑옷",100,5,Equipment::EquipmentType::Armor);
        break;

        case 3:  // 구리검 (무기)
        gameManager->PurchaseEquipment(player,"구리검",200,5,Equipment::EquipmentType::Weapon);
        break;

        case 4:  // 구리갑옷 (방어구)
        gameManager->PurchaseEquipment(player,"구리갑옷",200,7,Equipment::EquipmentType::Armor);
        break;
        case 5:  // 철검 (무기)
        gameManager->PurchaseEquipment(player,"철검",500,20,Equipment::EquipmentType::Weapon);
        break;
        case 6:  // 철갑옷 (방어구)
        gameManager->PurchaseEquipment(player,"철갑옷",500,20,Equipment::EquipmentType::Armor);
        break;
        case 7:  // 미스릴 창 (무기)
        gameManager->PurchaseEquipment(player,"미스릴 창",700,30,Equipment::EquipmentType::Weapon);
        break;
        case 8:  // 드래곤 비늘갑옷 (방어구)
        gameManager->PurchaseEquipment(player,"미스릴 갑옷",700,30,Equipment::EquipmentType::Armor);
        break;
        case 9:  // 드래곤 슬레이어 (무기)
        gameManager->PurchaseEquipment(player,"드래곤 슬레이어",1000,50,Equipment::EquipmentType::Weapon);
        break;
        case 0:  // 드래곤 비늘갑옷 (방어구)
        gameManager->PurchaseEquipment(player,"드래곤 비늘갑옷",1000,50,Equipment::EquipmentType::Armor);
        break;
        case 99:  // 뒤로가기
        std::cout << "상점으로 돌아갑니다.\n";
        break;

        default:
        std::cout << "잘못된 선택입니다. 다시 시도해 주세요.\n";
        break;
        }
        break;

        case 3:  // 아이템 판매
        {
            if(player->Inventory.empty()) {
                std::cout << "인벤토리가 비어 있습니다.\n";
                break;
            }
        cout << "\n=============================\n";
        std::cout << "판매할 아이템을 선택하세요.\n\n";
        std::cout << "현재 보유한 아이템 목록:\n";
        index = 1;

        // 아이템 목록 출력
        for(const auto& item : player->Inventory) {
            std::cout << index++ << ". " << item.first << ": " << item.second->GetAmount() << " 개\n";
        }

        std::cout << "판매할 아이템 번호를 입력하세요: ";
        int sellChoice;
        std::cin >> sellChoice;

        // 범위 검사 먼저 수행
        if(sellChoice < 1 || sellChoice >= index) {
            std::cout << "잘못된 번호입니다.\n";
            break;
        }

        // **선택한 아이템을 찾기 (sellChoice가 유효한 경우에만)**
        auto itemToSell = std::next(player->Inventory.begin(),sellChoice - 1);


        // 선택한 아이템 수량 확인
        int itemAmount = itemToSell->second->GetAmount();

        if(itemAmount > 1) {
            // 수량이 2개 이상일 경우 일괄 판매 여부 확인
            std::cout << itemToSell->first << "이(가) " << itemAmount << "개 있습니다. 일괄 판매하시겠습니까? (Y/N): ";
            char bulkSellChoice;
            std::cin >> bulkSellChoice;

            if(bulkSellChoice == 'Y' || bulkSellChoice == 'y') {
                int totalPrice = itemAmount * itemToSell->second->GetPrice();
                player->Gold += totalPrice;
                std::cout << itemToSell->first << " " << itemAmount << "개를 판매했습니다. 총 " << totalPrice << " 골드가 추가되었습니다.\n";
                player->Inventory.erase(itemToSell);  // 아이템 삭제
            } else {
                std::cout << itemToSell->first << " 1개를 판매 하시겠습니까?";
                char sellChoice;
                std::cin >> sellChoice;
                if(sellChoice == 'Y' || sellChoice == 'y') {
                    int totalPrice = itemAmount * itemToSell->second->GetPrice();
                    player->Gold += totalPrice;
                    std::cout << itemToSell->first << " " << itemAmount << "개를 판매했습니다. 총 " << totalPrice << " 골드가 추가되었습니다.\n";
                    player->Inventory.erase(itemToSell);  // 아이템 삭제
                } else {
                    // 수량 감소
                    std::cout << "판매를 진행하지 않습니다. 전 메뉴로 돌아갑니다.\n";
                    return;
                }
            }
        } else {
            // 수량이 1개일 경우 판매 여부 확인
            std::cout << itemToSell->first << "이(가) " << itemAmount << "개 있습니다. 판매하시겠습니까? (Y/N): ";
            char sellChoice;
            std::cin >> sellChoice;
            if(sellChoice == 'Y' || sellChoice == 'y') {
                int totalPrice = itemAmount * itemToSell->second->GetPrice();
                player->Gold += totalPrice;
                std::cout << itemToSell->first << " " << itemAmount << "개를 판매했습니다. 총 " << totalPrice << " 골드가 추가되었습니다.\n";
                player->Inventory.erase(itemToSell);  // 아이템 삭제
            } else {
                // 수량 감소
                std::cout << "판매를 진행하지 않습니다. 전 메뉴로 돌아갑니다.\n";
                return;
            }
            player->Gold += itemToSell->second->GetPrice();
            std::cout << itemToSell->first << "을(를) 판매했습니다. " << itemToSell->second->GetPrice() << " 골드가 추가되었습니다.\n";
            player->Inventory.erase(itemToSell);
        }

        break;
        }
        case 4:  // 아이템 목록 확인
        std::cout << "\n===========================\n";
        std::cout << "현재 보유한 아이템 목록:\n";

        if(player->Inventory.empty()) {
            std::cout << "인벤토리가 비어 있습니다.\n";
        } else {
            int index = 1;
            for(const auto& item : player->Inventory) {
                std::cout << index++ << ". " << item.first << ": " << item.second->GetAmount() << " 개\n";
            }
        }
        std::cout << "===========================\n";
        break;


        case 5:  // 상점 종료
            std::cout << "상점을 종료합니다.\n";
            return;

        default:
            std::cout << "잘못된 선택입니다. 다시 시도해 주세요.\n";
            break;
        }
    }
}


void GameManager::PurchaseEquipment(Character* player, const std::string& itemName, int price, int bonusStat, Equipment::EquipmentType type)
{
    if (player->Gold >= price)
    {
        // 장비가 이미 인벤토리에 있는지 확인
        auto it = player->Inventory.find(itemName);
        if (it != player->Inventory.end()) // 이미 가지고 있는 경우
        {
            it->second->IncreaseAmount(1);  // 수량 증가
        }
        else // 새로운 장비 구매
        {
            // Equipment 객체를 std::unique_ptr<Item>로 변환하여 전달
            std::unique_ptr<Item> item = std::move(std::make_unique<Equipment>(itemName, price, bonusStat, type));

            // AddItem에서 std::move(item)을 통해 소유권을 넘깁니다.
            player->AddItem(std::move(item));  // AddItem 함수에서 소유권을 전달
        }

        player->Gold -= price;  // 골드 차감
        std::cout << itemName << "을(를) 구매했습니다.\n";
    }
    else
    {
        std::cout << "골드가 부족합니다.\n";
    }
}




void GameManager::DisplayInventory(Character* player)
{
    cout << "\n==================================\n";
    std::cout << "\n인벤토리:\n";
    for (const auto& item : player->Inventory)
    {
        std::cout << item.first << ": " << item.second->GetName() << " (" << item.second->GetAmount() << " 개)\n";
    }
}
