#include <iostream>
#include <string>
#include <fstream>
#include "Scoreboard.h"
#include "SFML/Graphics.hpp"

using namespace std;

Scoreboard::Scoreboard()
{
	fontScore.loadFromFile("arialrounded.TTF");
	fontDifficulty.loadFromFile("COOPBL.TTF");
	for (int i = 0; i < 3; i++)
	{
		difficulty[i].setFont(fontDifficulty);
		difficulty[i].setCharacterSize(34);
		difficulty[i].setFillColor(sf::Color::Yellow);
	}
	title.setFont(fontDifficulty);
	title.setCharacterSize(50);
	title.setFillColor(sf::Color(236, 255, 179, 255));
	title.setString("Scoreboard");
	title.setPosition(327, 100);

	buttonBack.setFont(fontScore);
	buttonBack.setCharacterSize(24);
	buttonBack.setFillColor(sf::Color::White);
	buttonBack.setString("Back");
	buttonBack.setPosition(75, 115);

	buttonReset.setFont(fontDifficulty);
	buttonReset.setCharacterSize(34);
	buttonReset.setFillColor(sf::Color::Yellow);
	buttonReset.setString("Reset");

	difficulty[0].setString("Easy");
	difficulty[1].setString("Medium");
	difficulty[2].setString("Hard");
	difficulty[0].setPosition(sf::Vector2f(200, 250));
	difficulty[1].setPosition(sf::Vector2f(400, 250));
	difficulty[2].setPosition(sf::Vector2f(655, 250));

	menuTexture.loadFromFile("game-background.jpg");
	menuSprite.setTexture(menuTexture);

	secunde.setFont(fontScore);
	secunde.setCharacterSize(24);
	secunde.setFillColor(sf::Color::White);

	crownTexture.loadFromFile("Images/crown.png");
	crownShape.setTexture(&crownTexture);

	dreptunghi.setFillColor(sf::Color(33, 114, 49, 255));
	dreptunghi.setSize(sf::Vector2f(560, 30));
	dreptunghi.setOutlineThickness(5);
	dreptunghi.setOutlineColor(sf::Color(26, 71, 35, 255));
	dreptunghi.setPosition(sf::Vector2f(190, 300));
}

void Scoreboard::initScores()			//citirea scorurilor din fisier
{
	ifstream f("scores.txt");
	int i = 0;
	while (i < 3)
	{
		f >> secE[i++];
	}
	i = 0;
	while (i < 3)
	{
		f >> secM[i++];
	}
	i = 0;
	while (i < 3)
	{
		f >> secH[i++];
	}
	f.close();
}

void Scoreboard::afisareScoreboard(sf::RenderWindow &window)			//afisarea paginii de Scoreboard
{
	window.draw(menuSprite);
	window.draw(title);
	window.draw(buttonBack);
	for (int i = 0; i < 3; i++)
	{
		window.draw(difficulty[i]);
	}
	dreptunghi.setPosition(sf::Vector2f(190, 300));
	window.draw(dreptunghi);
	dreptunghi.setPosition(sf::Vector2f(190, 350));
	window.draw(dreptunghi);
	dreptunghi.setPosition(sf::Vector2f(190, 400));
	window.draw(dreptunghi);

	int min, sec;
	for (int i = 0; i < 3; i++)
	{
		if (secE[i] < 3599)
		{
			min = secE[i] / 60;
			sec = secE[i] % 60;
			string s = to_string(min) + " : " + to_string(sec);
			secunde.setString(s);
		}
		else
		{
			string s = " - : - ";
			secunde.setString(s);
		}
		
		secunde.setPosition(sf::Vector2f(210, 300 + i * 50));
		window.draw(secunde);									//afiseaza scorul de la Easy
	}
	for (int i = 0; i < 3; i++)
	{
		if (secM[i] < 3599)
		{
			min = secM[i] / 60;
			sec = secM[i] % 60;
			string s = to_string(min) + " : " + to_string(sec);
			secunde.setString(s);
		}
		else
		{
			string s = " - : - ";
			secunde.setString(s);
		}
		secunde.setPosition(sf::Vector2f(450, 300 + i * 50));
		window.draw(secunde);									//afiseaza scorul de la Medium
	}
	for (int i = 0; i < 3; i++)
	{
		if (secH[i] < 3599)
		{
			min = secH[i] / 60;
			sec = secH[i] % 60;
			string s = to_string(min) + " : " + to_string(sec);
			secunde.setString(s);
		}
		else
		{
			string s = " - : - ";
			secunde.setString(s);
		}
		secunde.setPosition(sf::Vector2f(672, 300 + i * 50));
		window.draw(secunde);									//afiseaza scorul de la Hard
	}
	crownShape.setSize(sf::Vector2f(60, 40));
	crownShape.setPosition(sf::Vector2f(110, 288));
	crownShape.setTextureRect(sf::IntRect(28,167,430,400));
	window.draw(crownShape);
	crownShape.setSize(sf::Vector2f(90, 50));
	crownShape.setPosition(sf::Vector2f(110, 400));
	crownShape.setTextureRect(sf::IntRect(523, 282, 480, 300));
	window.draw(crownShape);
	crownShape.setSize(sf::Vector2f(40, 40));
	crownShape.setPosition(sf::Vector2f(118, 338));
	crownShape.setTextureRect(sf::IntRect(1003, 95, 300, 450));
	window.draw(crownShape);
	buttonReset.setPosition(200, 440);
	window.draw(buttonReset);
	buttonReset.setPosition(430, 440);
	window.draw(buttonReset);
	buttonReset.setPosition(650, 440);
	window.draw(buttonReset);
}

void Scoreboard::focusBack(bool focus)
{
	if (focus)
		buttonBack.setFillColor(sf::Color::Yellow);
	else
		buttonBack.setFillColor(sf::Color::White);
}

void Scoreboard::newHighscore(int newscore, int &score1, int &score2, int &score3)	//modifica scorurile in cazul in care e scor record
{
	if (newscore < score1)
	{
		score3 = score2;
		score2 = score1;
		score1 = newscore;
	}
	else
		if (newscore < score2)
		{
			score3 = score2;
			score2 = newscore;
		}
		else
			if (newscore < score3)
				score3 = newscore;
}

void Scoreboard::writeScore(int m, int s, char mode)	//apeleaza modificarea scorurilor in functie de mod
{
	int newscore = m * 60 + s;
	switch (mode)
	{
	case 'e':
		newHighscore(newscore, secE[0], secE[1], secE[2]);
		break;
	case 'm':
		newHighscore(newscore, secM[0], secM[1], secM[2]);
		break;
	case 'h':
		newHighscore(newscore, secH[0], secH[1], secH[2]);
		break;
	}
}

void Scoreboard::scrieInFisier()		//scrie scorurile in fisier
{
	ofstream g("scores.txt");
	for (int i = 0; i < 3; i++)
		g << secE[i] << " ";
	for (int i = 0; i < 3; i++)
		g << secM[i] << " ";
	for (int i = 0; i < 3; i++)
		g << secH[i] << " ";
	g.close();
}

void Scoreboard::resetScore(char mode)
{
	switch (mode)
	{
	case 'e':
		for (int i = 0; i < 3; i++)
			secE[i] = 3599;
		break;
	case 'm':
		for (int i = 0; i < 3; i++)
			secM[i] = 3599;
		break;
	case 'h':
		for (int i = 0; i < 3; i++)
			secH[i] = 3599;
		break;
	}
}
