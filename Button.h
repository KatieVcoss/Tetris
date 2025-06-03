#pragma once  // Защита от множественного включения заголовочного файла

#include <SFML/Graphics.hpp>  
#include <iostream>           

// Класс кнопки с двумя состояниями (нормальное и нажатое)
class Button {
public:
    // Конструктор кнопки, где 
    //   location - позиция кнопки на экране;
    //   normal - текстура для нормального состояния;
    //   clicked - текстура для нажатого состояния;
    Button(sf::Vector2f location, const sf::Texture& normal, const sf::Texture& clicked);

    // Проверка клика по кнопке,где
    //   mousePos - координаты курсора мыши (по умолчанию (-1,-1))
    bool checkClick(sf::Vector2i mousePos = sf::Vector2i(-1, -1));

    // Получение спрайта для отрисовки
    sf::Sprite* getSprite();

private:
    // Графические представления кнопки:
    sf::Sprite normal;    // Спрайт нормального состояния
    sf::Sprite clicked;   // Спрайт нажатого состояния

    // Указатель на текущий спрайт (для отрисовки)
    sf::Sprite* currentSpr;

    // Текущее состояние кнопки:
    //   false - не нажата
    //   true - нажата
    bool current = false;

    // Установка состояния кнопки - state - новое состояние кнопки
    void setState(bool state);
};