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

        std::cout << "캐릭터 이름을 입력해주세요 (최대 " << maxNameLength << "자): ";

        std::getline(std::cin,playerName);

        // 이름 길이 제한 처리 / 공백 입력 처리
        while(playerName.empty() || playerName.length() > maxNameLength) 
        {
                if(playerName.empty()) 
                {
                    std::cout << "이름은 비어 있을 수 없습니다. 다시 입력해주세요: ";
                } else 
                {
                    std::cout << "이름이 너무 깁니다. 최대 " << maxNameLength << "자 이내로 입력해주세요: ";
                }
                std::getline(std::cin,playerName);
        }


        // 캐릭터와 상점 생성
        Character* player = new Character(playerName);
        Shop* shop = new Shop();

        // 게임 매니저 생성 후 시작
        GameManager gameManager;
        gameManager.StartGame(player,shop);

        // 메모리 해제
        delete player;
        delete shop;


        std::cout << "의현: 내가 다 끝내주마";
        return 0;
}