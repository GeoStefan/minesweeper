
#include<iostream>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include <string.h>

Menu::Menu()
{
	arialrounded.loadFromFile("arialrounded.TTF");
	cooper.loadFromFile("COOPBL.TTF");
	title1.setFont(arialrounded);
	title1.setString("Welcome to");
	title1.setPosition(350, 100);
	title1.setFillColor(sf::Color::Yellow);
	title1.setCharacterSize(62);
	title2.setFont(cooper);
	title2.setString("Minesweeper");
	title2.setPosition(293, 100);
	title2.setFillColor(sf::Color::Yellow);
	title2.setCharacterSize(62);
	title3.setFont(arialrounded);
	title3.setString("Please select difficulty");
	title3.setPosition(320, 250);
	title3.setFillColor(sf::Color::White);
	title3.setCharacterSize(34);

	
	difficulty[0].setFont(arialrounded);
	difficulty[0].setString("Easy");
	difficulty[0].setFillColor(sf::Color::White);
	difficulty[0].setPosition(sf::Vector2f(350, 320));

	difficulty[1].setFont(arialrounded);
	difficulty[1].setString("Medium");
	difficulty[1].setFillColor(sf::Color::White);
	difficulty[1].setPosition(sf::Vector2f(450, 320));

	difficulty[2].setFont(arialrounded);
	difficulty[2].setString("Hard");
	difficulty[2].setFillColor(sf::Color::White);
	difficulty[2].setPosition(sf::Vector2f(590, 320));

	menuTexture.loadFromFile("game-background.jpg");
	menuSprite.setTexture(menuTexture);
}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(menuSprite);
	window.draw(title2);
	window.draw(title3);
	for (int i = 0; i < NUMBER_OF_DIFFICULTIES; i++)
	{
		window.draw(difficulty[i]);
	}
}

void Menu::focus(int i)
{
	difficulty[i].setFillColor(sf::Color::Yellow);
}

void Menu::focus_lost(int i)
{
	difficulty[i].setFillColor(sf::Color::White);
}