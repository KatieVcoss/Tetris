#include "GameEngine.h"  
using namespace sf;      // ������������� ������������ ���� SFML

int main()
{
    // �������� ������ ��������� �� ������ GameEngine
    // make_unique ��������� ������� ������
    auto myGame = std::make_unique<GameEngine>();

    // ������ ��������� �������� �����
    myGame->run();

    return 0;  
}