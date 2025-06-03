#include "Button.h"


/**
 * Конструктор кнопки - Инициализирует кнопку, устанавливает текстуры и позицию
 * location - позиция кнопки на экране (координаты x,y)
 * normal - текстура для обычного состояния кнопки
 * clicked - текстура для нажатого состояния кнопки
 */
Button::Button(sf::Vector2f location, const sf::Texture& normal, const sf::Texture& clicked)
{
    // устанавливаем текстуры для спрайтов 
    this->normal.setTexture(normal);   // нормальная кнопка
    this->clicked.setTexture(clicked); // кнопка нажата
    // устанавливаем координаты расположения кнопок
    this->normal.setPosition(location);
    this->clicked.setPosition(location);
    // присваиваем указателю нормальное состояние кнопки
    currentSpr = &this->normal;
}

/**
 * Проверка клика по кнопке
 * mousePos - координаты курсора мыши (x,y)
 * return true если был клик по кнопке, false если клика не было
 */
bool Button::checkClick(sf::Vector2i mousePos) 
{
    // если передаются координаты курсора мышки делаем проверку, 
    // что курсор находится в пределах границ кнопки
    // Если переданы валидные координаты мыши (x >= 0)
    if (mousePos.x>=0)
    {
    if ((static_cast<float>(mousePos.x) > currentSpr->getPosition().x && 
        static_cast<float>(mousePos.x) < (currentSpr->getPosition().x + 
        currentSpr->getGlobalBounds().width))
        && (static_cast<float>(mousePos.y) > currentSpr->getPosition().y && 
            static_cast<float>(mousePos.y) < (currentSpr->getPosition().y + 
        currentSpr->getGlobalBounds().height)) )
        {
        // меняем состояние кнопки на противоположное
        setState(!current); return true;
        }
      }
    else
        // если кнопка нажата меняем её вид в нормальное положение
        if (current) 
        { 
            setState(!current); return true; 
        } 
    return false;
}
//Установка состояния кнопки
//Изменяет текущее состояние кнопки и переключает отображаемый спрайт
void Button::setState(bool which) 
{
    // Сохраняем новое состояние
    current = which;
    
    if (current) 
    {
        currentSpr = &clicked;
        
        return;
    }
    currentSpr = &normal;  
}
//Получение текущего спрайта кнопки - получаем спрайт для отрисовки кнопки в текущем состоянии
sf::Sprite* Button::getSprite() 
{
    return currentSpr;
}
