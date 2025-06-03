#include "Tetramino.h"

// Конструктор класса Tetramino
// Инициализирует игровое поле и параметры тетромино
Tetramino::Tetramino(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2i square_size, float scale)
    : height(square_size.y), width(square_size.x), window(window), tet(pos), scale(scale)
{
    // Настройка внешнего вида кубиков
    cube->setOutlineColor(sf::Color(78, 87, 84)); // Серый цвет границы
    cube->setOutlineThickness(-1);                // Толщина границы
    cube->setSize(sf::Vector2f(scale, scale));    // Размер кубика

    // Инициализация игрового поля 
    for (int i = 0; i < width; i++) {
        std::vector<sf::Color> v;
        for (int j = 0; j < height; j++) {
            v.push_back(sf::Color::Black); // Пустая клетка
        }
        square.push_back(v);
    }
    restart(); // Начальная настройка игры
}

// Сброс игры в начальное состояние
void Tetramino::restart()
{
    // Очистка игрового поля
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            square[i][j] = sf::Color::Black;
        }
    }

    // Генерация случайных фигур и цветов
    typeTet.y = d(rnd); // Следующая фигура
    colTet.y = d(rnd);  // Следующий цвет
    score = 0;          // Сброс счета

    newFigrois(); // Создание новой фигуры
}

// Создание новой фигуры
void Tetramino::newFigrois()
{
    typeTet.x = typeTet.y; // Текущая фигура = следующей
    colTet.x = colTet.y;   // Текущий цвет = следующему

    // Позиционирование фигуры в центре верхней части поля
    for (int i = 0; i < t.size(); i++) {
        t[i].x = figures[typeTet.x][i] % 2 + static_cast<float>(floor(width / 2));
        t[i].y = static_cast<float>(figures[typeTet.x][i] / 2);
    }

    // Генерация следующей фигуры и цвета
    typeTet.y = d(rnd);
    colTet.y = d(rnd);
    delay = 250; // Стандартная задержка падения
}

// Обновление состояния игры
void Tetramino::update(sf::Time const& deltaTime)
{
    // Управление звуком
    if (playMus) mus.play(0); else mus.stop(0);

    // Логика движения фигуры
    frameRate += deltaTime;
    if (frameRate > sf::milliseconds(delay)) {
        frameRate = sf::milliseconds(0);

        // Горизонтальное движение
        if (check(ch::x) && click_dx != 0) {
            for (int i = 0; i < 4; i++) t[i].x += click_dx;
            mus.play(3); // Звук движения
            click_dx = 0;
        }

        // Вертикальное движение (падение)
        if (check(ch::y)) {
            for (int i = 0; i < 4; i++) t[i].y += click_dy;
        }
        else {
            // Фигура достигла дна или другой фигуры
            for (int i = 0; i < t.size(); i++) {
                if (static_cast<int>(t[i].y) == 2) { // Проигрыш
                    restart();
                    mus.play(2); // Звук проигрыша
                    return;
                }
                // Фиксация фигуры на поле
                square[static_cast<size_t>(t[i].x)][static_cast<size_t>(t[i].y)] = sf::Color(tetcolor[colTet.x]);
            }

            // Проверка заполненных линий
            int numLine = 0;
            for (int j = 0; j < height; j++) {
                int line = 0;
                for (int i = 0; i < width; i++) {
                    if (square[i][j] != sf::Color::Black) line++;
                    if (line == width) {
                        lineDead(j);    // Удаление линии
                        mus.play(1);    // Звук удаления линии
                        numLine++;
                    }
                }
            }

            // Начисление очков за собранные линии
            if (numLine != 0) {
                score += 5 * (numLine * numLine); // Квадратичный рост очков
            }

            newFigrois(); // Создание новой фигуры
        }
    }
}

// Установка направления движения
void Tetramino::tetDirection(direction dir)
{
    click_dx = static_cast<float>(dir);
}

// Поворот фигуры
void Tetramino::rotate()
{
    if (check(ch::rotation)) {
        sf::Vector2f centerRotation = t[1]; // Центр вращения
        for (int i = 0; i < t.size(); i++) {
            // Матрица поворота 90 градусов
            float x = t[i].y - centerRotation.y;
            float y = t[i].x - centerRotation.x;
            t[i].x = centerRotation.x - x;
            t[i].y = centerRotation.y + y;
        }
        mus.play(3); // Звук поворота
    }
}

// Ускоренное падение
void Tetramino::speed()
{
    mus.play(4); // Звук ускорения
    delay = 10;  // Минимальная задержка
}

// Удаление заполненной линии
void Tetramino::lineDead(int g)
{
    // Сдвиг всех линий выше удаляемой вниз
    for (int i = g; i > 0; i--) {
        for (int j = 0; j < width; j++) {
            square[j][i] = square[j][static_cast<size_t>(i - 1)];
        }
    }
}

// Проверка возможности движения/поворота
bool Tetramino::check(ch ch)
{
    switch (ch) {
    case Tetramino::ch::x: // Проверка горизонтального движения
        for (int i = 0; i < t.size(); i++) {
            if ((t[i].x + click_dx < 0) || // Выход за левую границу
                (t[i].x + click_dx > static_cast<float>(width - 1))) return false; // Выход за правую границу
            if ((static_cast<int>(t[i].y) >= 0) &&
                (square[static_cast<size_t>(t[i].x + click_dx)][static_cast<size_t>(t[i].y)] != sf::Color::Black))
                return false; // Столкновение с другой фигурой
        }
        break;

    case Tetramino::ch::y: // Проверка вертикального движения
        for (int i = 0; i < t.size(); i++) {
            if ((t[i].y + click_dy) > static_cast<float>(height - 1)) return false; // Достигли дна
            if ((static_cast<int>(t[i].y + click_dy) >= 0) &&
                (square[static_cast<size_t>(t[i].x)][static_cast<size_t>(t[i].y + click_dy)] != sf::Color::Black))
                return false; // Столкновение с другой фигурой
        }
        break;

    case Tetramino::ch::rotation: // Проверка возможности поворота
        sf::Vector2f centerRotation = t[1];
        for (int i = 0; i < t.size(); i++) {
            float x = t[i].y - centerRotation.y;
            float y = t[i].x - centerRotation.x;
            if (((centerRotation.x - x) < 0) ||
                ((centerRotation.x - x) > static_cast<float>(width - 1)) ||
                ((centerRotation.y + y) > static_cast<float>(height - 1))) return false; // Выход за границы
            if ((static_cast<int>(centerRotation.y + y) >= 0) &&
                (square[static_cast<size_t>(centerRotation.x - x)][static_cast<size_t>(centerRotation.y + y)] != sf::Color::Black))
                return false; // Столкновение с другой фигурой
        }
        break;
    }
    return true;
}

// Отрисовка игрового поля и фигур
void Tetramino::draw()
{
    // Отрисовка следующей фигуры (превью)
    if (positionmaket.x >= 0) {
        cube->setFillColor(tetcolor[colTet.y]);
        for (int i = 0; i < 4; i++) {
            cube->setPosition((figures[typeTet.y][i] % 2) * scale, (static_cast<float>(figures[typeTet.y][i] / 2)) * scale);
            cube->move(positionmaket);
            window.draw(*cube);
        }
    }

    // Отрисовка игрового поля
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cube->setFillColor(square[i][j]); // Цвет клетки
            cube->setPosition(static_cast<float>(i) * scale, static_cast<float>(j) * scale);
            cube->move(tet);
            window.draw(*cube);
        }
    }

    // Отрисовка текущей фигуры
    cube->setFillColor(tetcolor[colTet.x]);
    for (int i = 0; i < t.size(); i++) {
        cube->setPosition(t[i].x * scale, t[i].y * scale);
        cube->move(tet);
        window.draw(*cube);
    }
}

// Включение/выключение звука
void Tetramino::mustet(bool m)
{
    playMus = m;
}

// Получение текущего счета
int Tetramino::getscore() const
{
    return score;
}

// Получение позиции фигуры
sf::Vector2f Tetramino::getPositio()
{
    sf::Vector2f pos;
    pos.x = t[1].x * scale + tet.x;
    pos.y = t[1].y * scale + tet.y;
    return pos;
}

// Установка позиции превью следующей фигуры
void Tetramino::maket(sf::Vector2f posmak)
{
    positionmaket = posmak;
}