
#include "GameManager.h"
#include "Character.h"
#include "Shop.h"
#include <Windows.h>
#include <iostream>
#include <limits>

int main()
{
    // 콘솔의 출력 인코딩을 UTF-8로 변경
    SetConsoleOutputCP(CP_UTF8);


    // 최대 길이 제한 설정
    const size_t maxNameLength = 20;
    std::string playerName;

    // 이름 길이 및 공백 검사
    while(true)
    {
        std::cout << "플레이어 이름을 입력하세요: ";
        std::getline(std::cin,playerName);

        // 공백 제거를 위한 임시 변수 생성
        std::string trimmedName = playerName;
        trimmedName.erase(remove_if(trimmedName.begin(),trimmedName.end(),isspace),trimmedName.end());

        // 공백 입력 처리
        if(trimmedName.empty())
        {
            std::cout << "이름은 비어 있을 수 없습니다. 다시 입력해주세요.\n";
            continue;
        }

        // 길이 초과 처리
        if(playerName.length() > maxNameLength)
        {
            std::cout << "이름이 너무 깁니다. 최대 " << maxNameLength << "자 이내로 입력해주세요.\n";
            continue;
        }

        // 유효한 이름일 경우 반복문 탈출
        break;
    }


    // 캐릭터와 상점 생성
    Character* player = new Character(playerName);
    Shop* shop = new Shop();

    // 게임 매니저 생성 후 시작
    GameManager gameManager;
    gameManager.StartGame(player, shop);

    // 메모리 해제
    delete player;
    delete shop;

    return 0;
}
