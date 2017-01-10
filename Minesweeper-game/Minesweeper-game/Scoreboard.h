#pragma once
#include<iostream>
#include "SFML/Graphics.hpp"

class Scoreboard
{
public:
	Scoreboard();
	void afisareScoreboard(sf::RenderWindow &window);
	void writeScore(int m, int s, char mode);
	void focusBack(bool focus);
	void initScores();
	void scrieInFisier();
private:
	int secE[3],secM[3],secH[3];
	sf::Text title;
	sf::Text buttonBack;
	sf::Text difficulty[3];
	sf::Text secunde;
	sf::Font fontScore;
	sf::Font fontDifficulty;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	void newHighscore(int newscore, int &score1, int &score2, int &score3);
};