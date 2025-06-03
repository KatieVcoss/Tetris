#include "AssetManager.h"

// Инициализация статического указателя на экземпляр класса (начальное значение nullptr)
AssetManager* AssetManager::sInstance = nullptr;

// Конструктор класса AssetManager
AssetManager::AssetManager()
{
	// Разрешить существование только одного AssetManager
	// В противном случае сгенерировать исключение
	// Сохраняем указатель на текущий экземпляр
	assert(sInstance == nullptr);
	sInstance = this;
}

//Получение текстуры по имени файла
sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
	// Получаем ссылку на карту текстур
	auto& texMap = sInstance->m_Textures;
	// Пытаемся найти текстуру в карте
	auto pairFound = texMap.find(filename);

	if (pairFound != texMap.end())
	{
		// Если текстура найдена, возвращаем существующую текстуру
		return pairFound->second;
	}
	else // Если текстура не найдена
	{
		// Создаем новую запись в карте и загружаем текстуру из файла
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		// Возвращаем загруженную текстуру
		return texture;
	}

}
//Получение звукового буфера по имени файла
sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename)
{
	// Получаем ссылку на карту звуковых буферов
	auto& sBufferMap = sInstance->m_SoundBuffer;
	// Пытаемся найти звук в карте
	auto pairFound = sBufferMap.find(filename);

	if (pairFound != sBufferMap.end()) // Если звук найден
	{
		// Возвращаем существующий звуковой буфер
		return pairFound->second;
	}
	else // Если звук не найден
	{
		// Создаем новую запись в карте и загружаем звук из файла
		auto& sBuffer = sBufferMap[filename];
		sBuffer.loadFromFile(filename);
		// Возвращаем загруженный звуковой буфер
		return sBuffer;
	}
}
//Получение шрифта по имени файла
sf::Font& AssetManager::GetFont(std::string const& filename)
{
	// Получаем ссылку на карту шрифтов
	auto& fontMap = sInstance->m_Fonts;
	// Пытаемся найти шрифт в карте
	auto pairFound = fontMap.find(filename);

	if (pairFound != fontMap.end()) // Если шрифт найден
	{
		// Возвращаем существующий шрифт
		return pairFound->second;
	}
	else // Если шрифт не найден
	{
		// Создаем новую запись в карте и загружаем шрифт из файла
		auto& font = fontMap[filename];
		font.loadFromFile(filename);
		// Возвращаем загруженный шрифт
		return font;
	}
}
//Получение шейдера по именам файлов
sf::Shader* AssetManager::GetShader(std::string const& vsFile, std::string const& fsFile)
{
	// Получаем ссылку на карту шейдеров
	auto& shaderMap = sInstance->m_Shaders;
	// Создаем составной ключ из имен файлов шейдеров
	auto combinedKey = vsFile + ";" + fsFile;
	// Пытаемся найти шейдер в карте
	auto pairFound = shaderMap.find(combinedKey);

	if (pairFound != shaderMap.end()) // Если шейдер найден
	{
		// Возвращаем существующий шейдер (через get() получаем сырой указатель из unique_ptr)
		return pairFound->second.get();
	}
	else // Если шейдер не найден
	{
		// Создаем новый шейдер и загружаем его из файлов
		auto& shader = (shaderMap[combinedKey] = std::unique_ptr<sf::Shader>(new sf::Shader()));
		shader->loadFromFile(vsFile, fsFile);
		// Возвращаем загруженный шейдер
		return shader.get();
	}
	
}
