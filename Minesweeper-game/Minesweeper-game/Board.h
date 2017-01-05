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
	sf::Texture nr1;
	sf::Texture nr2;
	sf::Texture nr3;
	sf::Texture nr4;
	sf::Texture nr5;
	sf::Texture nr6;
	sf::Texture nr7;
	sf::Texture nr8;
	sf::Texture black;
	sf::Texture white;
	sf::Texture bomb;
	sf::Texture flag;
	sf::Texture bomb_defused;
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
	sf::Text flagsMessage;
};
