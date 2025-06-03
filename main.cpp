#include "GameEngine.h"  
using namespace sf;      // Использование пространства имен SFML

int main()
{
    // Создание умного указателя на объект GameEngine
    // make_unique безопасно создает объект
    auto myGame = std::make_unique<GameEngine>();

    // Запуск основного игрового цикла
    myGame->run();

    return 0;  
}