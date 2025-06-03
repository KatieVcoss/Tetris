#include "GameSound.h"

// Функция воспроизведения звука по индексу
// Принимает: index - индекс звука в массиве GSound
void GameSound::play(int index) 
{
	// Проверяем, не играет ли уже этот звук
	if (GSound[index].getStatus() == sf::SoundSource::Status::Stopped ) GSound[index].play(); // Запускаем воспроизведение
}
// Функция остановки звука по индексу
// Принимает: index - индекс звука в массиве GSound
void GameSound::stop(int index) 
{
	// Проверяем, играет ли сейчас этот звук
	if (GSound[index].getStatus() == sf::SoundSource::Status::Playing) GSound[index].stop(); // Останавливаем воспроизведение
}
// Функция остановки всех звуков
void GameSound::AllStop()
{
	// Проходим по всем звукам в массиве
	// Если звук играет
	// Останавливаем его
	for (int i = 0; i < n; i++) if (GSound[i].getStatus() == sf::SoundSource::Status::Playing) GSound[i].stop();
}
