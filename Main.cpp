#include "GameManager.h"
#include "Character.h"
#include "BossMonster.h"
#include <iostream>

int main() {
    Character* Player = new Character("Hero");
    Player->DisplayStatus();


    while (Player->Health > 0) {
        if (Player->Level >= 10) {
            std::cout << "A Boss Monster has appeared!\n";
            BossMonster* Boss = GameManager::GenerateBossMonster(Player->Level);
            GameManager::Battle(Player);
            if (Player->Health > 0) {
                std::cout << "You have defeated the Boss Monster! You win!\n";
                break;
            }
        }
        else {
            GameManager::Battle(Player);
            Player->DisplayStatus();
            Player->VisitShop();
        }
    }

    if (Player->Health <= 0) {
        std::cout << "Game Over!\n";
    }

    delete Player;
    return 0;
}