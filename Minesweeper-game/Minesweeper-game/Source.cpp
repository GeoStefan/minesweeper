/*
		Minesweeper game
		author: Popescu Georgian-Stefan
		group: A7
*/
#include <iostream>
#include <stdlib.h>
#include <random>  
#include <ctype.h>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Game.h"
using namespace std;

void position(int &x, int &y)
{
	char mode = 'e';
	switch (mode)
	{
	case 'e':
		x -= 277;
		x /= 45;
		y -= 150;
		y /= 45;
		break;
	case 'm':
		x -= 244;
		x /= 30;
		y -= 150;
		y /= 30;
		break;
	case 'h':
		x -= 30;
		x /= 45;
		y -= 150;
		y /= 30;
		break;
	}
}

int main()
{
		
	int openMenu = 1, playGame = 0, firstClick=0;
	int nrFlags = 0, nrCorrect_box = 0, game_Over = 0, win;
	Menu menu ;
	Game game;
	game.prepareTextures();
	sf::RenderWindow window(sf::VideoMode(960, 660), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:                   
					window.close();
					break;
				case sf::Event::MouseButtonPressed:					
					if (event.key.code == sf::Mouse::Left)
					{
						if (firstClick)
						{
							if (game.mouseInBoard(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
							{
								cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
								
								int x= sf::Mouse::getPosition(window).x, y= sf::Mouse::getPosition(window).y;
								position(x, y);
								//cout << "casuta de coordonate " << y << " " << x << endl;
								game.firstClickLeft(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
								playGame = 1;
								firstClick = 0;
								cout << "da";
							}

						}		//close firstClick */
						
						if (openMenu)
						{
							if (sf::Mouse::getPosition(window).x >= 350 && sf::Mouse::getPosition(window).x < 420 && sf::Mouse::getPosition(window).y >= 320 && sf::Mouse::getPosition(window).y < 355)
							{
								cout << "apasa easy" << endl;
								game.init('e');
								firstClick = 1;
								openMenu = 0;
							}
							if (sf::Mouse::getPosition(window).x >= 450 && sf::Mouse::getPosition(window).x < 563 && sf::Mouse::getPosition(window).y >= 320 && sf::Mouse::getPosition(window).y < 350)
							{
								cout << "apasa med" << endl;
								game.init('m');
								firstClick = 1;
								openMenu = 0;
							}
							if(sf::Mouse::getPosition(window).x >= 590 && sf::Mouse::getPosition(window).x < 660 && sf::Mouse::getPosition(window).y >= 320 && sf::Mouse::getPosition(window).y < 350)
							{
								cout << "apasa hard" << endl;
								game.init('h');
								firstClick = 1;
								openMenu = 0;
							}
						}

						if (playGame)
						{
							int x = sf::Mouse::getPosition(window).x;
							int y = sf::Mouse::getPosition(window).y;
							if (game.mouseInBoard(x, y))
								game.inGame(x, y, 's');
							if (game.ifMine(x, y))
							{
								win = 0;
								playGame = 0;
								game_Over = 1;
							}
							if (game.ifGameWin())
							{
								win = 1;
								playGame = 0;
								game_Over = 1;
							}
						}
						if (game_Over)
						{
							if (sf::Mouse::getPosition(window).x >= 30 && sf::Mouse::getPosition(window).x < 180 && sf::Mouse::getPosition(window).y >= 35 && sf::Mouse::getPosition(window).y < 69)
							{
								game_Over = 0;
								openMenu = 1;
							}
							if (sf::Mouse::getPosition(window).x >= 30 && sf::Mouse::getPosition(window).x < 87 && sf::Mouse::getPosition(window).y >= 80 && sf::Mouse::getPosition(window).y < 109)
								window.close();
						}
					}
					else
						if (event.key.code == sf::Mouse::Right)
						{
							if (playGame)
							{
								int x = sf::Mouse::getPosition(window).x;
								int y = sf::Mouse::getPosition(window).y;
								if (game.mouseInBoard(x, y))
									game.inGame(x, y, 'd');
							}
						}
					break;
				case sf::Event::MouseMoved:
					if (openMenu)
					{
						if (event.mouseMove.x >= 350 && event.mouseMove.x < 420 && event.mouseMove.y >= 320 && event.mouseMove.y < 355)
						{
							menu.focus(0);
						}
						else
							menu.focus_lost(0);
						if (event.mouseMove.x >= 450 && event.mouseMove.x < 563 && event.mouseMove.y >= 320 && event.mouseMove.y < 350)
						{
							menu.focus(1);
						}
						else
							menu.focus_lost(1);
						if (event.mouseMove.x >= 590 && event.mouseMove.x < 660 && event.mouseMove.y >= 320 && event.mouseMove.y < 350)
						{
							menu.focus(2);
						}
						else
							menu.focus_lost(2);
					}     //close openmenu
					if (game_Over)
					{
						if (sf::Mouse::getPosition(window).x >= 30 && sf::Mouse::getPosition(window).x < 180 && sf::Mouse::getPosition(window).y >= 35 && sf::Mouse::getPosition(window).y < 69)
							game.gameOverFocus(1, 1);
						else
							game.gameOverFocus(1, 0);
						if (sf::Mouse::getPosition(window).x >= 30 && sf::Mouse::getPosition(window).x < 87 && sf::Mouse::getPosition(window).y >= 80 && sf::Mouse::getPosition(window).y < 109)
							game.gameOverFocus(2, 1);
						else
							game.gameOverFocus(2, 0);
					}
					break;
			}
		}
		//cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
		
		window.clear();
		if (openMenu)
			menu.draw(window);
		if (playGame || firstClick)
		{
			game.drawBoard(window);
		}
		if (game_Over)
		{
			game.gameOver(win,window);
		}
		window.display();
	}
	
	return 0;
}