#pragma once // Защита от множественного включения
#include"Button.h";
#include"Tetramino.h";

// Класс игрового движка, управляющего основным циклом игры
class GameEngine
{
public:
	GameEngine();          
	void run();  // Главный игровой цикл          
private:
	// Менеджер ресурсов (текстуры, шрифты, звуки)
	AssetManager manager;
	// Графическое окно (используется unique_ptr для безопасного управления памятью)
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
		(sf::VideoMode(640, 640), L"Тетрис", sf::Style::Close);
	// иконка графического окна
	sf::Image icon;
	// игровой фон
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));
	// кнопки игрового интерфейса
	Button pause = Button(sf::Vector2f(13, 140), 
	AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 220), 
	AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 300), 
	AssetManager::GetTexture("image/nosound.png"), AssetManager::GetTexture("image/sound.png"));
	Button exit = Button(sf::Vector2f(13, 380), 
	AssetManager::GetTexture("image/exit1.png"), AssetManager::GetTexture("image/exit2.png"));
	// Текст для отображения счета
	sf::Text text;
	// игра тетрис
	Tetramino tetramino = Tetramino(*window, sf::Vector2f(210, -42), sf::Vector2i(20,33), 20);
	// Приватные методы:
	void input();    // Обработка ввода (клавиатура/мышь)      
	void update(sf::Time const& deltaTime);// Обновление игрового состояния
	void draw();     // Отрисовка игры     
	// Состояния игры:
	bool myexit = false;   // Флаг выхода из игры
	bool mypause = false;  // Флаг паузы
	bool mus = false;      // Флаг звука (вкл/выкл)
	sf::Time tm;           // Таймер для задержки выхода       
};