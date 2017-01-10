#pragma once
#include<iostream>
#include "SFML/Graphics.hpp"


#define NUMBER_OF_DIFFICULTIES 3

class Menu
{
public:
	Menu();
	void draw(sf::RenderWindow &window);
	void focus(int i);
	void focus_lost(int i);
	void focusScore(bool focus);
private:
	sf::Font arialrounded;
	sf::Font cooper;
	sf::Text difficulty[NUMBER_OF_DIFFICULTIES];
	sf::Text title1;
	sf::Text title2;
	sf::Text title3;
	sf::Text scoreboard;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
};