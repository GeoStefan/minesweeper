#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"

Audio::Audio()
{
	bufferMine.loadFromFile("Audio/bomb.ogg");
	bufferWin.loadFromFile("Audio/win.ogg");
	soundMine.setBuffer(bufferMine);
	soundWin.setBuffer(bufferWin);
}

void Audio::playSound(int win)
{
	if (win)
		soundWin.play();
	else
		soundMine.play();
}