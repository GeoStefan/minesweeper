#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "SFML/Graphics.hpp"
using namespace std;

void Afisare::afisareMode(sf::RenderWindow &window, char difficulty)
{
	switch (difficulty)
	{
	case 'e':
		mode.setString("Easy mode");
		mode.setPosition(310, 30);
		break;
	case 'm':
		mode.setString("Medium mode");
		mode.setPosition(270, 30);
		break;
	case 'h':
		mode.setString("Hard mode");
		mode.setPosition(310, 30);
		break;
	}
	window.draw(mode);
}

void Afisare::afisareMatrix(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window, int nrFlags)
{
	int indentX,indentY;
	float squareSize;
	if (difficulty == 'e')
	{
		squareSize = 45;
		indentX = 277;
		indentY = 150;
	}
	else
		if (difficulty == 'm')
		{
			squareSize = 30;
			indentX = 244;
			indentY = 150;
		}
		else
		{
			squareSize = 30;
			indentX = 30;
			indentY = 150;
		}
	square.setSize(sf::Vector2f(squareSize, squareSize));
	
	window.draw(boardSprite);
	afisareMode(window, difficulty);
	afisNrAvailableFlags(nrFlags,window);
	for(int i=0;i<length;i++)
		for (int j = 0; j < width; j++)
		{
			square.setTextureRect(sf::IntRect(0, 0, 150, 150));
			if (viz[i][j] == 0)
				square.setTexture(&black);
			else
				if (viz[i][j] == 2)
					square.setTexture(&flag);
				else
					if (viz[i][j] == 1)
					{
						if (mat[i][j] == -1)
							square.setTexture(&bomb);
						else
							if (mat[i][j] == 0)
								square.setTexture(&white);
							else
							{
								switch (mat[i][j])
								{
								case 1:
									square.setTexture(&nr1);
									break;
								case 2:
									square.setTexture(&nr2);
									break;
								case 3:
									square.setTexture(&nr3);
									break;
								case 4:
									square.setTexture(&nr4);
									break;
								case 5:
									square.setTexture(&nr5);
									break;
								case 6:
									square.setTexture(&nr6);
									break;
								case 7:
									square.setTexture(&nr7);
									break;
								case 8:
									square.setTexture(&nr8);
									break;
								}
							}
					}
					else
						if (viz[i][j] == 3)
							square.setTexture(&bomb_defused);
	
			square.setPosition(sf::Vector2f(squareSize*j+indentX, squareSize*i+indentY));
			window.draw(square);
		}
}

void Afisare::initTextures()
{
	nr1.loadFromFile("Images/number1.jpg");
	nr2.loadFromFile("Images/number2.jpg");
	nr3.loadFromFile("Images/number3.jpg");
	nr4.loadFromFile("Images/number4.jpg");
	nr5.loadFromFile("Images/number5.jpg");
	nr6.loadFromFile("Images/number6.jpg");
	nr7.loadFromFile("Images/number7.jpg");
	nr8.loadFromFile("Images/number8.jpg");
	black.loadFromFile("Images/rsz_black3.jpg");
	white.loadFromFile("Images/white.jpg");
	bomb.loadFromFile("Images/rsz_bomb.jpg");
	flag.loadFromFile("Images/rsz_flag3.png");
	bomb_defused.loadFromFile("Images/rsz_bombD.jpg");
	boardTexture.loadFromFile("game-background.jpg");
	boardSprite.setTexture(boardTexture);

	cooper.loadFromFile("COOPBL.TTF");
	arial.loadFromFile("arialrounded.TTF");
	mode.setFillColor(sf::Color::Yellow);
	mode.setCharacterSize(62);
	mode.setFont(cooper);
	flags.setFillColor(sf::Color::White);
	flags.setCharacterSize(22);
	flags.setFont(arial);
	flags.setPosition(sf::Vector2f(850,95));
	flagsMessage.setFont(arial);
	flagsMessage.setCharacterSize(18);
	flagsMessage.setString("Available flags:");
	flagsMessage.setPosition(sf::Vector2f(800, 80));
	
	playButton.setFont(arial);
	playButton.setCharacterSize(30);
	playButton.setFillColor(sf::Color::White);
	playButton.setString("Play again");
	playButton.setPosition(sf::Vector2f(30, 35));

	exitButton.setFont(arial);
	exitButton.setCharacterSize(30);
	exitButton.setFillColor(sf::Color::White);
	exitButton.setString("Exit");
	exitButton.setPosition(sf::Vector2f(30, 80));

	timeMinut.setFont(arial);
	timeMinut.setPosition(sf::Vector2f(860, 30));
	timeMinut.setFillColor(sf::Color::Yellow);
	timeSec.setPosition(sf::Vector2f(890, 30));
	timeSec.setFillColor(sf::Color::Yellow);
	timeSeparator.setFont(arial);
	timeSeparator.setPosition(sf::Vector2f(878, 30));
}

void Afisare::afisNrAvailableFlags(int nrFlags, sf::RenderWindow &window)
{
	char nrf[10];
	_itoa_s(nrFlags, nrf, 10, 10);
	flags.setString(nrf);
	window.draw(flags);
	window.draw(flagsMessage);
}

void Afisare::gameOver(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window,int win)
{
	int indentX, indentY;
	float squareSize;
	if (difficulty == 'e')
	{
		squareSize = 45;
		indentX = 277;
		indentY = 150;
	}
	else
		if (difficulty == 'm')
		{
			squareSize = 30;
			indentX = 244;
			indentY = 150;
		}
		else
		{
			squareSize = 30;
			indentX = 30;
			indentY = 150;
		}
	square.setSize(sf::Vector2f(squareSize, squareSize));
	window.draw(boardSprite);
	winner.setFont(cooper);
	winner.setCharacterSize(42);
	winner.setFillColor(sf::Color::Yellow);
	if (win)
	{
		winner.setString("You win!");
		winner.setPosition(400,60);
	}
	else
	{
		winner.setString("Booom !!! You lost!");
		winner.setPosition(275,60);
	}
	window.draw(winner);
	for (int i = 0; i<length; i++)
		for (int j = 0; j < width; j++)
		{
			square.setTextureRect(sf::IntRect(0, 0, 150, 150));
			if (viz[i][j] == 0)
				square.setTexture(&black);
			else
				if (viz[i][j] == 2)
					square.setTexture(&flag);
				else
					if (viz[i][j] == 1)
					{
						if (mat[i][j] == -1)
							square.setTexture(&bomb);
						else
							if (mat[i][j] == 0)
								square.setTexture(&white);
							else
							{
								switch (mat[i][j])
								{
								case 1:
									square.setTexture(&nr1);
									break;
								case 2:
									square.setTexture(&nr2);
									break;
								case 3:
									square.setTexture(&nr3);
									break;
								case 4:
									square.setTexture(&nr4);
									break;
								case 5:
									square.setTexture(&nr5);
									break;
								case 6:
									square.setTexture(&nr6);
									break;
								case 7:
									square.setTexture(&nr7);
									break;
								case 8:
									square.setTexture(&nr8);
									break;
								}
							}
					}
					else
						if (viz[i][j] == 3)
							square.setTexture(&bomb_defused);

			square.setPosition(sf::Vector2f(squareSize*j + indentX, squareSize*i + indentY));
			window.draw(square);
		}
	
	window.draw(playButton);
	window.draw(exitButton);
}

void Afisare::gameOverFocus(int element, bool focus)
{
	switch (focus)
	{
	case true:
		if(element==1)
			playButton.setFillColor(sf::Color::Yellow);
		else
			exitButton.setFillColor(sf::Color::Yellow);
		break;
	case false:
		if (element == 1)
			playButton.setFillColor(sf::Color::White);
		else
			exitButton.setFillColor(sf::Color::White);
		break;
	}
}

void Afisare::timer(int m,int s, sf::RenderWindow &window)
{
	char minut[10],sec[10];
	_itoa_s(m, minut, 10, 10);
	_itoa_s(s, sec, 10, 10);
	
	timeMinut.setString(minut);
	timeSec.setFont(arial);
	timeSec.setString(sec);
	timeSeparator.setString(":");

	window.draw(timeSec);
	window.draw(timeMinut);
	window.draw(timeSeparator);
}