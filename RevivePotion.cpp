#include "RevivePotion.h"
#include "Character.h"
#include <iostream>

RevivePotion::RevivePotion()
    : Item("��Ȱ ����", 70) {  // �θ� Ŭ������ �ѱ� �̸� ����
}

std::string RevivePotion::GetName() const {
    return Name;  // �ѱ۷� ��ȯ
}

void RevivePotion::Use(Character* character) {
    if (character->Health <= 0) {
        character->Health = character->MaxHealth / 2;  // ��Ȱ �� ü�� 50% ȸ��
        std::cout << character->Name << " ��Ȱ ���� ������� ü�� 50% ���·� ��Ȱ!\n";
    }
    else {
        std::cout << "������ �̸����� ���� ��� �����մϴ�.\n";
    }
}