#include "GameManager.h"
#include <iostream>
#include <cstdlib>  // rand() 함수 사용
std::unique_ptr<Monster> GameManager::GenerateRandomMonster(int level)
{
    int randomMonster = rand() % 4;  // 0부터 3까지 랜덤 숫자 생성

    std::unique_ptr<Monster> monster;

    switch (randomMonster) {
    case 0:
        std::cout << "슬라임을 마주쳤다!\n";
        monster = std::make_unique<Slime>(level);  // Slime 클래스 사용
        break;
    case 1:
        std::cout << "고블린을 마주쳤다!\n";
        monster = std::make_unique<Goblin>(level);  // Goblin 클래스 사용
        break;
    case 2:
        std::cout << "트롤을 마주쳤다!\n";
        monster = std::make_unique<Troll>(level);  // Troll 클래스 사용
        break;
    case 3:
        std::cout << "오크를 마주쳤다!\n";
        monster = std::make_unique<Orc>(level);  // Orc 클래스 사용
        break;
    default:
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
        std::cout << "\n현재 상태:\n";
        player->DisplayStatus();

        std::cout << "\n어떤 활동을 하시겠습니까?\n";
        std::cout << "1. 전투\n2. 상점 방문\n3. 인벤토리 확인\n4. 게임 종료\n";
        std::cout << "원하는 동작을 선택하세요: ";
        std::cin >> choice;
        std::cin.ignore(); // 버퍼 비우기

        if (choice == 1) {
            

            // 레벨 10 이상일 때 보스 몬스터와 전투
            if (player->Level >= 10) {
                BossBattle(player);
                break;  // 보스 전투 후 게임 종료
            }
            else {
                Battle(player);  // 일반 몬스터와 전투
            }
        }
        else if (choice == 2) {
            VisitShop(player, shop);
        }
        else if (choice == 3) {
            DisplayInventory(player);
        }
        else if (choice == 4) {
            std::cout << "게임을 종료합니다.\n";
        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }
    } while (choice != 4);
}
void GameManager::Battle(Character* player)
{
    // 랜덤 몬스터 생성
    std::unique_ptr<Monster> monster = GenerateRandomMonster(player->Level);

    // 전투 시작 전에 아이템 자동 사용
    player->AutoUseItems();
    
    std::cout << "야생 " << monster->Name << "가 나타났다!\n";
    std::cout << "몬스터 이름: " << monster->Name << "\n";
    std::cout << "몬스터 레벨: " << monster->Level << "\n";
    std::cout << "몬스터 체력: " << monster->Health << "\n";
    std::cout << "몬스터 공격력: " << monster->Attack << "\n";

    // 몬스터가 존재하면 전투 시작
    if (monster != nullptr) {
        std::cout << player->Name << "와 " << monster->Name << "의 전투가 시작됩니다!\n";
        while (monster->Health > 0 && player->Health > 0) {
            std::cout << player->Name << "의 공격! " << monster->Name << "의 체력이 " << monster->Health << "로 감소!\n";
            monster->TakeDamage(player->Attack);

            if (monster->Health > 0) {
                std::cout << monster->Name << "의 공격! " << player->Name << "의 체력이 " << player->Health << "로 감소!\n";
                player->TakeDamage(monster->Attack);
            }

            // 상태 출력
            std::cout << player->Name << "의 체력: " << player->Health << "\n";
            std::cout << monster->Name << "의 체력: " << monster->Health << "\n";
        }

        // 전투 결과
        if (monster->Health <= 0) {
            std::cout << monster->Name << "을 처치했습니다!\n";
            player->GainExperience(100);  // 경험치 획득
            // 전리품 드롭
            std::unique_ptr<Item> loot = monster->DropItem();
            if (loot != nullptr) {
                std::cout << "전리품으로 " << loot->GetName() << "을(를) 획득했습니다!\n";
                player->AddItem(std::move(loot));  // 인벤토리에 아이템 추가
            }
            else {
                std::cout << "전리품이 없습니다.\n";
            }
        }
        else {
            std::cout << player->Name << "이(가) 쓰러졌습니다. 게임 오버.\n";
            exit(0);  // 프로그램 종료
        }
    }
    else {
        std::cout << "몬스터가 존재하지 않습니다!\n";
    }
    player->DisplayStatus();  // 전투 후 상태 표시
}



// 보스 몬스터 생성
std::unique_ptr<BossMonster> GameManager::GenerateBossMonster(int level) {
    std::cout << "마왕을 마주쳤다!\n";
    return std::make_unique<BossMonster>(level);  // BossMonster 클래스를 사용
}

void GameManager::BossBattle(Character* player) {
    // 마왕 보스를 생성
    auto boss = GenerateBossMonster(player->Level);  // 마왕 보스 생성
    std::cout << "보스 몬스터 " << boss->Name << "가 나타났습니다!\n";

    // 전투 시작 전 공격력 증가 아이템 사용
    player->AutoUseItems();

    while (boss->Health > 0 && player->Health > 0) {
        std::cout << "플레이어의 공격! " << boss->Name << "의 체력이 " << boss->Health << "로 감소!\n";
        boss->TakeDamage(player->Attack);

        // 보스가 살아 있다면 보스의 공격
        if (boss->Health > 0) {
            std::cout << boss->Name << "의 공격! " << player->Name << "의 체력이 " << player->Health << "로 감소!\n";
            player->TakeDamage(boss->Attack);
        }

        // 플레이어와 보스 상태 출력
        std::cout << player->Name << "의 현재 체력: " << player->Health << "\n";
        std::cout << boss->Name << "의 현재 체력: " << boss->Health << "\n";
    }

    if (boss->Health <= 0) {
        std::cout << boss->Name << "을 처치했습니다! 게임 클리어!\n";
        player->GainExperience(500);  // 보스 처치 후 경험치
    }
    else if (player->Health <= 0) {
        std::cout << player->Name << "이(가) 쓰러졌습니다. 게임 오버.\n";
    }

    // 게임 종료 메시지
    std::cout << "게임을 종료합니다.\n";
}





void GameManager::VisitShop(Character* player, Shop* shop)
{
    while (true) {
        std::cout << "상점에 오신 것을 환영합니다! 무엇을 하시겠습니까?\n";
        std::cout << "1. 아이템 구매\n";
        std::cout << "2. 아이템 판매\n";
        std::cout << "3. 아이템 목록 확인\n";
        std::cout << "4. 상점 종료\n";

        int choice;
        std::cin >> choice;

        // 여기서 변수를 초기화하도록 변경
        int index;
        std::vector<std::string> itemNames;  // 'itemNames' 변수 초기화

        switch (choice) {
        case 1:  // 아이템 구매
            std::cout << "1. 체력 포션 (20 골드)\n";
            std::cout << "2. 공격력 포션 (50 골드)\n";
            std::cout << "3. 부활 포션 (100 골드)\n";
            std::cout << "4. 뒤로가기\n";
            int buyChoice;
            std::cin >> buyChoice;

            switch (buyChoice) {
            case 1:
                if (player->Gold >= 20)
                {
                    player->Inventory["체력 포션"]++;
                    player->Gold -= 20;  // 20 골드 차감
                    std::cout << "체력 포션을 구매했습니다.\n";
                }
                else
                {
                    std::cout << "골드가 부족합니다.\n";
                }
                break;
            case 2:
                if (player->Gold >= 50)
                {
                    player->Inventory["공격력 포션"]++;
                    player->Gold -= 50;  // 50 골드 차감
                    std::cout << "공격력 포션을 구매했습니다.\n";
                }
                else {
                    std::cout << "골드가 부족합니다.\n";
                }
                break;
            case 3:
                if (player->Gold >= 100)
                {
                    player->Inventory["부활 포션"]++;  // 부활 포션 추가
                    player->Gold -= 100;  // 100 골드 차감
                    std::cout << "부활 포션을 구매했습니다.\n";
                }
                else {
                    std::cout << "골드가 부족합니다.\n";
                }
                break;
            case 4:
                std::cout << "상점으로 돌아갑니다.\n";
                break;
            default:
                std::cout << "잘못된 선택입니다. 다시 시도해 주세요.\n";
            }
            break;
        case 2:  // 아이템 판매
            std::cout << "판매할 아이템을 선택하세요.\n";
            std::cout << "현재 보유한 아이템 목록:\n";

            index = 1;  // 'index' 초기화

            // 플레이어의 인벤토리에서 판매할 아이템을 나열
            for (const auto& item : player->Inventory) {
                if (item.second > 0) {  // 아이템이 1개 이상 있을 경우에만 표시
                    std::cout << index << ". " << item.first << ": " << item.second << "개\n";  // 아이템 목록 출력
                    itemNames.push_back(item.first);  // 아이템 이름을 itemNames 배열에 추가
                    index++;  // 인덱스 증가
                }
            }

            if (itemNames.empty()) {
                std::cout << "판매할 아이템이 없습니다.\n";
                break;
            }

            std::cout << "0. 뒤로가기\n";

            int sellChoice;
            std::cin >> sellChoice;

            if (sellChoice == 0) {
                std::cout << "상점으로 돌아갑니다.\n";
                break;
            }

            // sellChoice가 유효한 범위인지 확인
            if (sellChoice < 0 || sellChoice > itemNames.size()) {
                std::cout << "잘못된 선택입니다. 다시 시도해 주세요.\n";
                break;
            }

            // 유효한 sellChoice일 경우, 아이템 판매
            if (sellChoice > 0 && sellChoice <= itemNames.size()) {
                std::string itemName = itemNames[sellChoice - 1];  // 선택된 아이템 이름
                int itemCount = player->Inventory[itemName];

                if (itemCount > 0) {
                    shop->SellItem(itemName, player);  // 아이템 판매
                }
                else {
                    std::cout << "판매할 " << itemName << "이(가) 없습니다.\n";
                }
            }
            break;

        case 3:  // 아이템 목록 확인
            std::cout << "현재 보유한 아이템 목록:\n";
            for (const auto& item : player->Inventory) {
                std::cout << item.first << ": " << item.second << "개\n";
            }
            break;

        case 4:  // 상점 종료
            std::cout << "상점을 종료합니다.\n";
            return;  // 상점 종료

        default:
            std::cout << "잘못된 선택입니다. 다시 시도해 주세요.\n";
            break;
        }
    }
}



void GameManager::DisplayInventory(Character* player) 
{
    std::cout << "인벤토리:\n";
    for (const auto& item : player->Inventory) {
        std::cout << item.first << ": " << item.second << " 개\n";
    }
}
