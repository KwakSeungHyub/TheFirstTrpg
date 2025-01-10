#include "GameManager.h"
#include <iostream>
#include <cstdlib>

Monster* GameManager::GenerateMonster(int level) {
    return new Monster("Goblin", level * 10, level * 2);
}

BossMonster* GameManager::GenerateBossMonster(int level) {
    return new BossMonster("Dragon", level * 50, level * 10);
}

void GameManager::Battle(Character* player) {
    Monster* monster = GenerateMonster(player->Level);
    std::cout << "A wild " << monster->Name << " appears!\n";
    while (monster->Health > 0 && player->Health > 0) {
        monster->TakeDamage(player->Attack);
        if (!monster->IsDefeated()) {
            player->TakeDamage(monster->Attack);
        }
    }
    if (monster->IsDefeated()) {
        player->GainExperience(50);
        std::cout << "You defeated the " << monster->Name << "!\n";
    }
    delete monster;
}

void GameManager::VisitShop(Character* player) {
    std::cout << "Visiting the shop...\n";
}

void GameManager::DisplayInventory(Character* player) {
    std::cout << "Inventory: \n";
    for (const auto& item : player->Inventory) {
        std::cout << "- " << item->GetName() << "\n";
    }
}
