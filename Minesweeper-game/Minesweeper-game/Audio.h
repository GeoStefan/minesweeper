#pragma once
#include <SFML/Audio.hpp>

class Audio
{
public:
	Audio();
	void playSound(int win);
private:
	sf::SoundBuffer bufferMine;
	sf::SoundBuffer bufferWin;
	sf::Sound soundMine;
	sf::Sound soundWin;
};