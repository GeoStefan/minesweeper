
#include<iostream>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include <string.h>

Menu::Menu()
{
	arialrounded.loadFromFile("Fonts/arialrounded.TTF");
	cooper.loadFromFile("Fonts/COOPBL.TTF");
	
	title2.setFont(cooper);
	title2.setString("Minesweeper");
	title2.setPosition(293, 100);
	title2.setFillColor(sf::Color::Yellow);
	title2.setCharacterSize(62);
	title3.setFont(arialrounded);
	title3.setString("Please select difficulty");
	title3.setPosition(320, 250);
	title3.setFillColor(sf::Color(255, 242, 204,255));
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

	menuTexture.loadFromFile("Images/game-background.jpg");
	menuSprite.setTexture(menuTexture);

	scoreboard.setFont(arialrounded);
	scoreboard.setString("Scoreboard");
	scoreboard.setCharacterSize(34);
	scoreboard.setFillColor(sf::Color(255, 242, 204,255));
	scoreboard.setPosition(sf::Vector2f(413, 400));

	instructions.setFont(arialrounded);
	instructions.setString("Instructions");
	instructions.setCharacterSize(34);
	instructions.setFillColor(sf::Color(255, 242, 204, 255));
	instructions.setPosition(sf::Vector2f(412, 470));

	howToPlay.setFont(arialrounded);
	howToPlay.setCharacterSize(22);
	howToPlay.setFillColor(sf::Color(255, 255, 204));

	title1.setFont(cooper);
	title1.setString("Instructions");
	title1.setPosition(330, 100);
	title1.setFillColor(sf::Color(255, 242, 204, 255));
	title1.setCharacterSize(50);

	buttonBack.setFont(arialrounded);
	buttonBack.setCharacterSize(24);
	buttonBack.setFillColor(sf::Color::White);
	buttonBack.setString("Back");
	buttonBack.setPosition(75, 115);

	dreptunghi.setFillColor(sf::Color(51, 51, 0, 255));
	dreptunghi.setSize(sf::Vector2f(850, 410));
	dreptunghi.setOutlineThickness(5);
	dreptunghi.setOutlineColor(sf::Color(236, 255, 179, 255));
	dreptunghi.setPosition(sf::Vector2f(50, 200));

	instructionTexture.loadFromFile("Images/instr.png");
	instructionImage.setTexture(instructionTexture);
}

void Menu::draw(sf::RenderWindow &window)		//afiseaza fereastra de meniu
{
	window.draw(menuSprite);	
	window.draw(title2);
	window.draw(title3);
	for (int i = 0; i < NUMBER_OF_DIFFICULTIES; i++)
	{
		window.draw(difficulty[i]);
	}
	window.draw(scoreboard);
	window.draw(instructions);
}

void Menu::focus(int i)
{
	difficulty[i].setFillColor(sf::Color::Yellow);
}

void Menu::focus_lost(int i)
{
	difficulty[i].setFillColor(sf::Color::White);
}

void Menu::focusScore(bool focus, char tab)		//stabileste culoarea in caz de focus pe Scoreboard si Instructions
{
	switch (tab)
	{
	case 's':
		if (focus)
			scoreboard.setFillColor(sf::Color::Yellow);
		else
			scoreboard.setFillColor(sf::Color(255, 242, 204, 255));
		break;
	case 'i':
		if (focus)
			instructions.setFillColor(sf::Color::Yellow);
		else
			instructions.setFillColor(sf::Color(255, 242, 204, 255));
		break;
	}
	
}

void Menu::drawInstructions(sf::RenderWindow &window)		//afisarea paginii de instructiuni
{
	window.draw(menuSprite);
	window.draw(title1);
	window.draw(buttonBack);
	window.draw(dreptunghi);
	howToPlay.setString("To open a square press left-click.");
	howToPlay.setPosition(sf::Vector2f(80, 200));
	window.draw(howToPlay);
	howToPlay.setString("To mark a bomb with a flag press rigth-click.");
	howToPlay.setPosition(sf::Vector2f(80, 230));
	window.draw(howToPlay);
	howToPlay.setString("To remove a bomb marker from a square ");
	howToPlay.setPosition(sf::Vector2f(80, 260));
	window.draw(howToPlay);
	howToPlay.setString("press rigth-click again.");
	howToPlay.setPosition(sf::Vector2f(60, 290));
	window.draw(howToPlay);
	howToPlay.setString("Clicking a square which doesn't have a bomb  ");
	howToPlay.setPosition(sf::Vector2f(80, 320));
	window.draw(howToPlay);
	howToPlay.setString("reveals the number of neighbouring squares containing bombs. ");
	howToPlay.setPosition(sf::Vector2f(60, 350));
	window.draw(howToPlay);
	howToPlay.setString("If you open a square with 0 neighboring bombs, all its neighbors will open.");
	howToPlay.setPosition(sf::Vector2f(80, 380));
	window.draw(howToPlay);
	howToPlay.setString("To open a big square(3x3) press middle-click.");
	howToPlay.setPosition(sf::Vector2f(340, 410));
	window.draw(howToPlay);
	howToPlay.setString("To win the game you have to open all the non-bomb");
	howToPlay.setPosition(sf::Vector2f(340, 440));
	window.draw(howToPlay);
	howToPlay.setString("squares without clicking on any bombs. ");
	howToPlay.setPosition(sf::Vector2f(320, 470));
	window.draw(howToPlay);
	howToPlay.setString("In the upper rigth corner are the time counter and");
	howToPlay.setPosition(sf::Vector2f(340, 500));
	window.draw(howToPlay);
	howToPlay.setString("the number of mines which is equal to the");
	howToPlay.setPosition(sf::Vector2f(320, 530));
	window.draw(howToPlay);
	howToPlay.setString("maximum number of available flags.");
	howToPlay.setPosition(sf::Vector2f(320, 560));
	window.draw(howToPlay);

	instructionImage.setTextureRect(sf::IntRect(0, 0, 122, 124));
	instructionImage.setPosition(680, 220);
	window.draw(instructionImage);
	instructionImage.setTextureRect(sf::IntRect(145, 0, 128, 99));
	instructionImage.setPosition(130, 450);
	window.draw(instructionImage);
}

void Menu::focusBack(bool focus)
{
	if (focus)
		buttonBack.setFillColor(sf::Color::Yellow);
	else
		buttonBack.setFillColor(sf::Color::White);
}