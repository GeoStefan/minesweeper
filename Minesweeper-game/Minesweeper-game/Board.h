#pragma once
#include "SFML/Graphics.hpp"
#include<iostream>
using namespace std;
class Afisare
{
public:
	void afisareMatrix(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window, int nrFlags);
	void initTextures();
	void gameOver(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window,int win);
	void gameOverFocus(int element, bool focus);
	void timer(int m,int s, sf::RenderWindow &window);
private:
	void afisareMode(sf::RenderWindow &window, char difficulty);
	void afisNrAvailableFlags(int nrFlags, sf::RenderWindow &window);
	void afisareBoard(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window);
	sf::Texture numere;
	sf::RectangleShape square;
	sf::Sprite boardSprite;
	sf::Texture boardTexture;
	sf::Text mode;
	sf::Font cooper;
	sf::Font arial;
	sf::Text flags;
	sf::Text winner;
	sf::Text playButton;
	sf::Text exitButton;
	sf::Text timeSec;
	sf::Text timeMinut;
	sf::Text timeSeparator;
	sf::Texture greenflag;
	sf::RectangleShape flagIcon;
	sf::Texture clockTexture;
	sf::RectangleShape clockIcon;
};
