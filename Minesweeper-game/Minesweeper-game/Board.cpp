#include<iostream>
#include "Board.h"
#include "SFML/Graphics.hpp"
using namespace std;

void Afisare::afisareMode(sf::RenderWindow &window, char difficulty)
{
	cooper.loadFromFile("COOPBL.TTF");
	mode.setPosition(270, 30);
	mode.setFillColor(sf::Color::Yellow);
	mode.setCharacterSize(62);
	mode.setFont(cooper);
	switch (difficulty)
	{
	case 'e':
		mode.setString("Easy mode");
		break;
	case 'm':
		mode.setString("Medium mode");
		break;
	case 'h':
		mode.setString("Hard mode");
		break;
	}
	window.draw(mode);
}

void Afisare::afisareMatrix(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window)
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
	bomb_defused.loadFromFile("Images/bombD.jpg");
	boardTexture.loadFromFile("game-background.jpg");
	boardSprite.setTexture(boardTexture);
	Afisare afisp;
	window.draw(boardSprite);
	afisp.afisareMode(window, difficulty);
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