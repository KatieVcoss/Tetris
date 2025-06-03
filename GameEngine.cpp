#include "GameEngine.h"

// Конструктор класса GameEngine
GameEngine::GameEngine()
{
    // Установка фонового изображения
    background.setTexture(&AssetManager::GetTexture("image/Tetris.png"));

    // Загрузка иконки окна
    if (!icon.loadFromFile("image/game.png")) window->close();
    window->setIcon(256, 256, icon.getPixelsPtr());

    // Настройка текста для отображения счета
    text.setFont(AssetManager::GetFont("font/Godzilla.ttf"));
    text.setFillColor(sf::Color::Green);

    // Инициализация тетромино (фигурки тетриса)
    tetramino.maket(sf::Vector2f(70, 20));
}

// Функция обработки ввода пользователя
void GameEngine::input()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        // Закрытие окна
        if (event.type == sf::Event::Closed) window->close();

        // Обработка нажатий клавиш:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            tetramino.tetDirection(Tetramino::direction::left); // Движение влево
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            tetramino.tetDirection(Tetramino::direction::right); // Движение вправо
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            tetramino.speed(); // Ускоренное падение
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            tetramino.rotate(); // Поворот фигуры
        }

        // Обработка колесика мыши
        if (event.type == sf::Event::MouseWheelMoved)
        {
            if ((event.mouseWheel.delta == -1) || (event.mouseWheel.delta == 1))
            {
                tetramino.speed(); // Ускоренное падение при прокрутке колесика мыши
            }
        }

        // Обработка нажатий кнопок мыши
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // Левая кнопка мыши
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Проверка кликов по кнопкам интерфейса:
                if (pause.checkClick(sf::Mouse::getPosition(*window)))
                {
                    mypause = !mypause; // Пауза/продолжение игры
                }
                if (sound.checkClick(sf::Mouse::getPosition(*window)))
                {
                    if (mus) mus = false; else mus = true; // Вкл/выкл звука
                    tetramino.mustet(mus);
                }
                if (restart.checkClick(sf::Mouse::getPosition(*window)))
                {
                    tetramino.restart(); // Перезапуск игры
                }
                if (exit.checkClick(sf::Mouse::getPosition(*window)))
                {
                    myexit = true; // Выход из игры
                }

                // Обработка кликов в игровом поле для движения фигуры
                if ((sf::Mouse::getPosition(*window).x < tetramino.getPositio().x)
                    && (sf::Mouse::getPosition(*window).x > 208) && (sf::Mouse::getPosition(*window).x < 609))
                {
                    tetramino.tetDirection(Tetramino::direction::left); // Движение влево
                }
                if (sf::Mouse::getPosition(*window).x >= tetramino.getPositio().x
                    && sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 609)
                {
                    tetramino.tetDirection(Tetramino::direction::right); // Движение вправо
                }
            }

            // Правая кнопка мыши - поворот фигуры
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                if (sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 609)
                {
                    tetramino.rotate();
                }
            }
        }

        // Обработка отпускания кнопки мыши
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                restart.checkClick();
                exit.checkClick();
            }
        }
    }
}

// Функция обновления состояния игры
// Принимает: deltaTime - время с последнего обновления
void GameEngine::update(sf::Time const& deltaTime)
{
    // Обновление состояния тетромино, если игра не на паузе
    if (!mypause) tetramino.update(deltaTime);

    // Обработка выхода из игры
    if (myexit) {
        tm += deltaTime;
        if (tm > sf::seconds(1))
        {
            if (myexit) window->close(); // Закрытие окна через 1 секунду
        }
    }
}

// Функция отрисовки игры
void GameEngine::draw()
{
    window->clear(sf::Color::Black); // Очистка экрана

    // Отрисовка игровых элементов:
    tetramino.draw(); // Отрисовка тетромино и поля
    window->draw(background); // Фон
    window->draw(*pause.getSprite()); // Кнопка паузы
    window->draw(*restart.getSprite()); // Кнопка рестарта
    window->draw(*sound.getSprite()); // Кнопка звука
    window->draw(*exit.getSprite()); // Кнопка выхода

    // Отрисовка счета
    text.setPosition(15, 515);
    text.setString(" < score > ");
    window->draw(text);
    text.setString(std::to_string(tetramino.getscore()));
    text.setPosition(100 - text.getGlobalBounds().width / 2, 555);
    window->draw(text);

    window->display(); // Отображение на экране
}

// Главный игровой цикл
void GameEngine::run()
{
    sf::Clock clock; // Таймер для измерения времени кадра

    while (window->isOpen())
    {
        sf::Time dt = clock.restart(); // Время с последнего кадра
        input(); // Обработка ввода
        update(dt); // Обновление состояния
        draw(); // Отрисовка
    }
}