#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "SFML/Graphics.hpp"
using namespace std;

void Afisare::afisareMode(sf::RenderWindow &window, char difficulty)		//afisarea modului de joc ales
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
	window.draw(boardSprite);									//desenarea background-ului
	afisareMode(window, difficulty);							//afisarea modului
	afisNrAvailableFlags(nrFlags,window);						//afisarea numarului de steaguri disponibile
	afisareBoard(mat, viz, length, width, difficulty, window);	//afisarea matricii
}

void Afisare::initTextures()
{
	
	numere.loadFromFile("Images/board-textures.png");
	square.setTexture(&numere);

	boardTexture.loadFromFile("Images/game-background.jpg");
	boardSprite.setTexture(boardTexture);

	cooper.loadFromFile("Fonts/COOPBL.TTF");
	arial.loadFromFile("Fonts/arialrounded.TTF");
	mode.setFillColor(sf::Color::Yellow);
	mode.setCharacterSize(62);
	mode.setFont(cooper);
	flags.setFillColor(sf::Color::White);
	flags.setCharacterSize(30);
	flags.setFont(arial);
	flags.setPosition(sf::Vector2f(860,85));
	greenflag.loadFromFile("Images/rsz_greenflag.png");
	flagIcon.setTexture(&greenflag);
	flagIcon.setTextureRect(sf::IntRect(0, 0, 180, 194));
	flagIcon.setSize(sf::Vector2f(30, 31));
	flagIcon.setPosition(sf::Vector2f(820, 90));
	
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

	clockTexture.loadFromFile("Images/clock.png");
	clockIcon.setTexture(&clockTexture);
	clockIcon.setTextureRect(sf::IntRect(0, 0, 180, 180));
	clockIcon.setPosition(sf::Vector2f(820, 34));
	clockIcon.setSize(sf::Vector2f(30, 30));

	timeSec.setFont(arial);
	timeSeparator.setString(":");
}

void Afisare::afisNrAvailableFlags(int nrFlags, sf::RenderWindow &window)
{
	char nrf[10];
	_itoa_s(nrFlags, nrf, 10, 10);
	flags.setString(nrf);
	window.draw(flags);
	window.draw(flagIcon);
}

void Afisare::gameOver(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window,int win)
{																				//afiseaza fereastra de la finalul jocului
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
	afisareBoard(mat, viz, length, width, difficulty, window);
	window.draw(playButton);
	window.draw(exitButton);
}

void Afisare::gameOverFocus(int element, bool focus)
{
	switch (focus)							//schimba culoarea butoanelor de Play again si Exit daca mouse-ul se afla deasupra lor
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

void Afisare::timer(int m,int s, sf::RenderWindow &window)				//afiseaza timpul
{
	char minut[10],sec[10];
	_itoa_s(m, minut, 10, 10);
	_itoa_s(s, sec, 10, 10);
	
	timeMinut.setString(minut);
	timeSec.setString(sec);

	window.draw(timeSec);
	window.draw(timeMinut);
	window.draw(timeSeparator);
	window.draw(clockIcon);
}

void Afisare::afisareBoard(int mat[16][30], int viz[16][30], int length, int width, char difficulty, sf::RenderWindow &window)
{
	int indentX, indentY;
	float squareSize;
	if (difficulty == 'e')				//stabilirea marginilor din stanga,sus si marimea patratului in functie de dificultate
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

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)   
		{
			if (viz[i][j] == 0)
				square.setTextureRect(sf::IntRect(784, 363, 150, 150));				//afiseaza patrat negru pt nevizitat
			else
				if (viz[i][j] == 2)
					square.setTextureRect(sf::IntRect(782, 194, 150, 150));			//afiseaza steag
				else
					if (viz[i][j] == 1)
					{
						if (mat[i][j] == -1)
							square.setTextureRect(sf::IntRect(782, 15, 150, 150));	//afiseaza bomba
						else
							if (mat[i][j] == 0)
								square.setTextureRect(sf::IntRect(953, 194, 150, 150));	//afiseaza patrat alb pt vizitat
							else
							{
								switch (mat[i][j])									//afiseaza numarul din patrat
								{
								case 1:

									square.setTextureRect(sf::IntRect(224, 249, 150, 150));
									break;
								case 2:

									square.setTextureRect(sf::IntRect(555, 249, 150, 150));
									break;
								case 3:

									square.setTextureRect(sf::IntRect(223, 419, 150, 150));
									break;
								case 4:

									square.setTextureRect(sf::IntRect(223, 79, 150, 150));
									break;
								case 5:

									square.setTextureRect(sf::IntRect(390, 419, 150, 150));
									break;
								case 6:

									square.setTextureRect(sf::IntRect(388, 79, 150, 150));
									break;
								case 7:

									square.setTextureRect(sf::IntRect(58, 249, 150, 150));
									break;
								case 8:

									square.setTextureRect(sf::IntRect(389, 249, 150, 150));
									break;
								}
							}
					}
					else
						if (viz[i][j] == 3)
							square.setTextureRect(sf::IntRect(949, 15, 150, 150));		//afiseaza mina dezamorsata

			square.setPosition(sf::Vector2f(squareSize*j + indentX, squareSize*i + indentY));
			window.draw(square);
		}
}