#pragma once // Защита от множественного включения
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <assert.h> // Для проверок макроса assert для отладки программы
#include<map> // Для использования std::map
#include<memory> // Для умных указателей

// Класс менеджера ресурсов (текстуры, шрифты, звуки, шейдеры)
class AssetManager
{

public:
	AssetManager();
	// Статические методы для доступа к ресурсам:
	static sf::Texture& GetTexture(std::string const& filename);// Получение текстуры по имени файла
	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);// Получение звукового буфера по имени файла
	static sf::Font& GetFont(std::string const& filename);// Получение шрифта по имени файла
	static sf::Shader* GetShader(std::string const& vsFile,std::string const& fsFile);// Получение шейдера по именам vertex и fragment шейдеров
private:
	// Контейнеры для хранения ресурсов:
	std::map<std::string, sf::Texture> m_Textures;// Хранилище текстур
	std::map<std::string, sf::SoundBuffer> m_SoundBuffer;// Хранилище звуковых буферов
	std::map<std::string, sf::Font> m_Fonts;// Хранилище шрифтов
	std::map < std::string, std::unique_ptr < sf::Shader >> m_Shaders;// Хранилище шейдеров с использованием unique_ptr (шейдеры в SFML нельзя копировать)

	static AssetManager* sInstance;// Указатель на единственный экземпляр класса (реализация Singleton)

};

