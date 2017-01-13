/*
		Minesweeper game
		author: Popescu Georgian-Stefan
		group: A7
*/
#include <iostream>
#include <stdlib.h>
#include <random>  
#include <ctype.h>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Game.h"
#include "Audio.h"
#include "Scoreboard.h"
using namespace std;

int main()
{
	int openMenu = 1, playGame = 0, firstClick=0;
	int game_Over = 0, win, play_sound=1, openScoreboard=0 , scrie_scor=0, openInstructions=0;
	char dif;
	clock_t start, test;
	Menu menu ;
	Game game;
	game.prepareTextures();
	Audio finalSound;
	Scoreboard scoreboard;
	scoreboard.initScores();
	sf::RenderWindow window(sf::VideoMode(960, 660), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed: 
					scoreboard.scrieInFisier();
					window.close();
					break;
				case sf::Event::MouseButtonPressed:					
					if (event.key.code == sf::Mouse::Left)
					{
						if (firstClick)
						{
							if (game.mouseInBoard(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
							{
								game.firstClickLeft(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
								playGame = 1;
								firstClick = 0;
								start = clock();
								//cout << "da";
							}

						}		//close firstClick */
						
						if (openMenu)
						{
							if (sf::Mouse::getPosition(window).x >= 350 && sf::Mouse::getPosition(window).x < 420 && sf::Mouse::getPosition(window).y >= 320 && sf::Mouse::getPosition(window).y < 355)
							{
								//cout << "apasa easy" << endl;
								game.init('e');
								firstClick = 1;
								openMenu = 0;
								dif = 'e';
							}
							if (sf::Mouse::getPosition(window).x >= 450 && sf::Mouse::getPosition(window).x < 563 && sf::Mouse::getPosition(window).y >= 320 && sf::Mouse::getPosition(window).y < 350)
							{
								//cout << "apasa med" << endl;
								game.init('m');
								firstClick = 1;
								openMenu = 0;
								dif = 'm';
							}
							if(sf::Mouse::getPosition(window).x >= 590 && sf::Mouse::getPosition(window).x < 660 && sf::Mouse::getPosition(window).y >= 320 && sf::Mouse::getPosition(window).y < 350)
							{
								//cout << "apasa hard" << endl;
								game.init('h');
								firstClick = 1;
								openMenu = 0;
								dif = 'h';
							}
							if (sf::Mouse::getPosition(window).x >= 413 && sf::Mouse::getPosition(window).x < 603 && sf::Mouse::getPosition(window).y >= 400 && sf::Mouse::getPosition(window).y < 433)
							{
								openMenu = 0;
								openScoreboard = 1;
							}
							if (sf::Mouse::getPosition(window).x >= 412 && sf::Mouse::getPosition(window).x < 603 && sf::Mouse::getPosition(window).y >= 470 && sf::Mouse::getPosition(window).y < 503)
							{
								//cout << "instructions" << endl;
								openInstructions = 1;
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
								play_sound = 1;
							}
							if (game.ifGameWin())
							{
								win = 1;
								playGame = 0;
								game_Over = 1;
								play_sound = 1;
								scrie_scor = 1;
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
							{
								scoreboard.scrieInFisier();
								window.close();
							}
						}
						if (openScoreboard)
						{
							if (sf::Mouse::getPosition(window).x >= 75 && sf::Mouse::getPosition(window).x < 133 && sf::Mouse::getPosition(window).y >= 115 && sf::Mouse::getPosition(window).y < 138)
							{
								openScoreboard = 0;
								openMenu = 1;
							}
							if (sf::Mouse::getPosition(window).x >= 200 && sf::Mouse::getPosition(window).x < 297 && sf::Mouse::getPosition(window).y >= 440 && sf::Mouse::getPosition(window).y < 474)
								scoreboard.resetScore('e');
							if (sf::Mouse::getPosition(window).x >= 430 && sf::Mouse::getPosition(window).x < 526 && sf::Mouse::getPosition(window).y >= 440 && sf::Mouse::getPosition(window).y < 474)
								scoreboard.resetScore('m');
							if (sf::Mouse::getPosition(window).x >= 650 && sf::Mouse::getPosition(window).x < 748 && sf::Mouse::getPosition(window).y >= 440 && sf::Mouse::getPosition(window).y < 474)
								scoreboard.resetScore('h');
						}
						if (openInstructions)
						{
							if (sf::Mouse::getPosition(window).x >= 75 && sf::Mouse::getPosition(window).x < 133 && sf::Mouse::getPosition(window).y >= 115 && sf::Mouse::getPosition(window).y < 138)
							{
								openInstructions = 0;
								openMenu = 1;
							}
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
						else
							if (event.key.code == sf::Mouse::Middle)
							{
								if (playGame)
								{
									int x = sf::Mouse::getPosition(window).x;
									int y = sf::Mouse::getPosition(window).y;
									if (game.mouseInBoard(x, y))
									{
										if(game.middleClick(x, y))
										{
											win = 0;
											playGame = 0;
											game_Over = 1;
											play_sound = 1;
										}
										else
										if (game.ifGameWin())
										{
											win = 1;
											playGame = 0;
											game_Over = 1;
											play_sound = 1;
											scrie_scor = 1;
										}
									}
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
						if (event.mouseMove.x >= 413 && event.mouseMove.x  < 603 && event.mouseMove.y >= 400 && event.mouseMove.y < 433)
						{
							menu.focusScore(true,'s');
						}
						else
							menu.focusScore(false,'s');
						if (event.mouseMove.x >= 412 && event.mouseMove.x  < 603 && event.mouseMove.y >= 470 && event.mouseMove.y < 503)
						{
							menu.focusScore(true, 'i');
						}
						else
							menu.focusScore(false, 'i');
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
					if (openScoreboard)
					{
						if (sf::Mouse::getPosition(window).x >= 75 && sf::Mouse::getPosition(window).x < 133 && sf::Mouse::getPosition(window).y >= 115 && sf::Mouse::getPosition(window).y < 138)
							scoreboard.focusBack(true);
						else
							scoreboard.focusBack(false);
					}
					if (openInstructions)
					{
						if (sf::Mouse::getPosition(window).x >= 75 && sf::Mouse::getPosition(window).x < 133 && sf::Mouse::getPosition(window).y >= 115 && sf::Mouse::getPosition(window).y < 138)
							menu.focusBack(true);
						else
							menu.focusBack(false);
					}
					break;
			}
			//cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
		}
		if (play_sound && game_Over)
		{
			finalSound.playSound(win);
			play_sound = 0;
		}
		window.clear();
		if (openMenu)
			menu.draw(window);
		if (playGame || firstClick)
		{
			game.drawBoard(window);
		}
		if (playGame)
		{
			test = clock();
			int t = int((test - start) / 1000);
			int m, s;
			m = t / 60;
			s = t % 60;
			game.timer(m,s,window);
		}
		if (game_Over)
		{
			game.gameOver(win,window);
			int t = int((test - start) / 1000);
			int m, s;
			m = t / 60;
			s = t % 60;
			game.timer(m, s, window);
			if (win && scrie_scor)
			{
				scoreboard.writeScore(m, s, dif);
				scrie_scor=0;
			}
		}
		if(openScoreboard)
		{
			scoreboard.afisareScoreboard(window);
		}
		if (openInstructions)
		{
			menu.drawInstructions(window);
		}
		window.display();
	}
	
	return 0;
}