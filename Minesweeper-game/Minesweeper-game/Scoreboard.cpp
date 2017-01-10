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
}

void Scoreboard::initScores()
{
	ifstream fe("easyscore.txt");
	int i = 0;
	while (i < 3)
	{
		fe >> secE[i++];
	}
	fe.close();

	ifstream fm("mediumscore.txt");
	i = 0;
	while (i < 3)
	{
		fm >> secM[i++];
	}
	fm.close();

	ifstream fh("hardscore.txt");
	i = 0;
	while (i < 3)
	{
		fh >> secH[i++];
	}
	fh.close();
}

void Scoreboard::afisareScoreboard(sf::RenderWindow &window)
{
	window.draw(menuSprite);
	window.draw(title);
	window.draw(buttonBack);
	for (int i = 0; i < 3; i++)
	{
		window.draw(difficulty[i]);
	}
	int min, sec;
	for (int i = 0; i < 3; i++)
	{
		min = secE[i] / 60;
		sec = secE[i] % 60;
		string s = to_string(min) + " : " + to_string(sec);
		secunde.setString(s);
		secunde.setPosition(sf::Vector2f(210, 300 + i * 50));
		window.draw(secunde);
	}
	for (int i = 0; i < 3; i++)
	{
		min = secM[i] / 60;
		sec = secM[i] % 60;
		string s = to_string(min) + " : " + to_string(sec);
		secunde.setString(s);
		secunde.setPosition(sf::Vector2f(450, 300 + i * 50));
		window.draw(secunde);
	}
	for (int i = 0; i < 3; i++)
	{
		min = secH[i] / 60;
		sec = secH[i] % 60;
		string s = to_string(min) + " : " + to_string(sec);
		secunde.setString(s);
		secunde.setPosition(sf::Vector2f(672, 300 + i * 50));
		window.draw(secunde);
	}
}

void Scoreboard::focusBack(bool focus)
{
	if (focus)
		buttonBack.setFillColor(sf::Color::Yellow);
	else
		buttonBack.setFillColor(sf::Color::White);
}

void Scoreboard::newHighscore(int newscore, int &score1, int &score2, int &score3)
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

void Scoreboard::writeScore(int m, int s, char mode)
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

void Scoreboard::scrieInFisier()
{
	ofstream ge("easyscore.txt");
	ge << secE[0] << " ";
	ge << secE[1] << " ";
	ge << secE[2] << " ";
	ge.close();
	ofstream gm("mediumscore.txt");
	gm << secM[0] << " ";
	gm << secM[1] << " ";
	gm << secM[2] << " ";
	gm.close();
	ofstream gh("hardscore.txt");
	gh << secH[0] << " ";
	gh << secH[1] << " ";
	gh << secH[2] << " ";
	gh.close();
}