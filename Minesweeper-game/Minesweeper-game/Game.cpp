#include <iostream>
#include <stdlib.h>
#include <random>  
#include <ctype.h>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Board.h"
#include "Scoreboard.h"
using namespace std;

Afisare board;

Game::Game()
{

}

void Game::init(char difficulty)					//functia care initializeaza dimensiunile matricii in functie de dificultate
{
	switch (difficulty)
	{
	case 'e':
		length = 9;
		width = 9;
		nrMines = 10;
		mode = 'e';
		break;
	case 'm':
		length = 16;
		width = 16;
		nrMines = 30;
		mode = 'm';
		break;
	case 'h':
		length = 16;
		width = 30;
		nrMines = 80;
		mode = 'h';
		break;
	}
	//cout << "dificultate " << mode <<" length " <<length<<" width "<<width<< endl;
	for(int i=0;i<length;i++)
		for (int j = 0; j < width; j++)
		{
			mat[i][j] = 0;
			viz[i][j] = 0;
		}
	nrFlags = 0;
	nrCorrect_box = 0;
}	   

bool Game::mouseInBoard(int x, int y)			//functia care verifica daca s-a apasat click pe matrice
{
	bool inBoard = false;
	switch (mode)
	{
	case 'e':
		if (x >= 277 && x <= 682 && y >= 150 && y <= 555)
			inBoard = true;
		break;
	case 'm':
		if (x >= 244 && x <= 724 && y >= 150 && y <= 630)
			inBoard = true;
		break;
	case 'h':
		if (x >= 30 && x <= 930 && y >= 150 && y <= 630)
			inBoard = true;
		break;
	}
	return inBoard;
}

void Game::position(int &x, int &y)				//transformarea coordonatelor click-ului in coordonatele din matrice
{
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
		x = x - 30;
		x = x / 30;
		y -= 150;
		y /= 30;
		break;
	}
}

bool Game::isNotMineFirst(int x, int y, int newX, int newY)			//verifica daca nu s-a generat bomba in coordonatele primului click
{
	if (x == newX && y == newY)
		return false;
	int oriz[8] = { -1,-1,-1,0,1,1,1,0 };
	int vert[8] = { -1,0,1,1,1,0,-1,-1 };
	for (int i = 0; i < 8; i++)
		if (x + oriz[i] == newX && y + vert[i] == newY)
			return false;
	return true;
}

void Game::matrix( int first_x, int first_y)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, width - 1);
	int i = 0, l, c;
	int oriz[8] = { -1,-1,-1,0,1,1,1,0 };
	int vert[8] = { -1,0,1,1,1,0,-1,-1 };
	while (i < nrMines)							//generarea random a pozitiei bombelor
	{
		l = dist(gen);
		c = dist(gen);
		while (l >= length)
		{
			l = dist(gen);
		}
		if (mat[l][c] == 0)
			if (isNotMineFirst(first_x, first_y, l, c))
			{
				mat[l][c] = -1;
				i++;
			}
	}

	for (int i = 0; i < length; i++)			//calcularea numarului de bombe vecine 
		for (int j = 0; j < width; j++)
			if (mat[i][j] == 0)
				for (int k = 0; k < 8; k++)
					if (oriz[k] + i >= 0 && oriz[k] + i < length && vert[k] + j >= 0 && vert[k] + j < width)
						if (mat[oriz[k] + i][vert[k] + j] == -1)
							mat[i][j]++;
}

void Game::safeZone(int x, int y)		//parcurge toata zona cu patratele in care se gaseste 0 si marcheaza ca vizitate si patratele adiacente
{
	viz[x][y] = 1;
	nrCorrect_box++;
	if (x - 1 >= 0 && y - 1 >= 0)
		if (mat[x - 1][y - 1] == 0 && viz[x - 1][y - 1] == 0)
			safeZone(x - 1, y - 1);
		else
			if (mat[x - 1][y - 1] > 0 && viz[x - 1][y - 1] == 0)
			{
				nrCorrect_box++;
				viz[x - 1][y - 1] = 1;
			}
	if (x - 1 >= 0)
		if (mat[x - 1][y] == 0 && viz[x - 1][y] == 0)
			safeZone(x - 1, y);
		else
			if (mat[x - 1][y] > 0 && viz[x - 1][y] == 0)
			{
				nrCorrect_box++;
				viz[x - 1][y] = 1;
			}
	if (x - 1 >= 0 && y + 1 <width)
		if (mat[x - 1][y + 1] == 0 && viz[x - 1][y + 1] == 0)
			safeZone(x - 1, y + 1);
		else
			if (mat[x - 1][y + 1] > 0 && viz[x - 1][y + 1] == 0)
			{
				nrCorrect_box++;
				viz[x - 1][y + 1] = 1;
			}
	if (y + 1 <width)
		if (mat[x][y + 1] == 0 && viz[x][y + 1] == 0)
			safeZone(x, y + 1);
		else
			if (mat[x][y + 1] > 0 && viz[x][y + 1] == 0)
			{
				nrCorrect_box++;
				viz[x][y + 1] = 1;
			}
	if (x + 1 <length && y + 1 <width)
		if (mat[x + 1][y + 1] == 0 && viz[x + 1][y + 1] == 0)
			safeZone(x + 1, y + 1);
		else
			if (mat[x + 1][y + 1] > 0 && viz[x + 1][y + 1] == 0)
			{
				nrCorrect_box++;
				viz[x + 1][y + 1] = 1;
			}
	if (x + 1 <length)
		if (mat[x + 1][y] == 0 && viz[x + 1][y] == 0)
			safeZone(x + 1, y);
		else
			if (mat[x + 1][y] > 0 && viz[x + 1][y] == 0)
			{
				nrCorrect_box++;
				viz[x + 1][y] = 1;
			}
	if (x + 1 <length && y - 1 >= 0)
		if (mat[x + 1][y - 1] == 0 && viz[x + 1][y - 1] == 0)
			safeZone(x + 1, y - 1);
		else
			if (mat[x + 1][y - 1] > 0 && viz[x + 1][y - 1] == 0)
			{
				nrCorrect_box++;
				viz[x + 1][y - 1] = 1;
			}
	if (y - 1 >= 0)
		if (mat[x][y - 1] == 0 && viz[x][y - 1] == 0)
			safeZone(x, y - 1);
		else
			if (mat[x][y - 1] > 0 && viz[x][y - 1] == 0)
			{
				nrCorrect_box++;
				viz[x][y - 1] = 1;
			}
}

void Game::firstClickLeft(int x, int y)			//functia apelata pentru primul click stanga
{
	int coordx = x, coordy = y;
	position(coordx, coordy);
	viz[coordy][coordx] = 1;
	matrix(coordy, coordx);
	safeZone(coordy, coordx);
	/*
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
			cout << " " << mat[i][j] << " ";
		cout << endl;
	}
	cout << endl;*/
}

void Game::drawBoard(sf::RenderWindow &window)				//apeleaza afisarea matricii si a ferestrei in joc
{
	board.afisareMatrix(mat, viz, length, width, mode, window, nrMines-nrFlags);
}

bool Game::ifMine(int x, int y)				//verifica daca utilizatorul a apasat pe o bomba
{
	int coordx = x, coordy = y;
	position(coordx, coordy);
	if (mat[coordy][coordx] == -1 && viz[coordy][coordx]==1)
		return true;
	return false;
}

bool Game::ifGameWin()						//verifica daca s-a castigat jocul
{
	if (nrCorrect_box == width*length - nrMines)
		return true;
	else
		return false;
}

void Game::inGame(int x, int y, char mouse)
{
	position(x, y);
	int maxFlags = nrMines;
	if (viz[y][x] == 0)
		if (mouse == 's')
		{
			viz[y][x] = 1;				//viziteaza patratul in care s-a dat click stanga
			if (mat[y][x] != -1)
				nrCorrect_box++;		//creste numarul de raspunsuri corecte daca nu s-a apasat pe bomba
			if (mat[y][x] == 0)
			{
				nrCorrect_box--;
				safeZone(y, x);			//viziteaza toata zona cu patrate de 0 daca este cazul
			}
		}
		else
		{
			if (nrFlags < maxFlags)		//marcarea cu steag
			{
				viz[y][x] = 2;
				nrFlags++;
			}
		}
	else
		if (viz[y][x] == 2 && mouse == 'd')		//demarcarea steagului
		{
			viz[y][x] = 0;
			nrFlags--;
		}
}

void Game::prepareTextures()
{
	board.initTextures();
}

void Game::gameOver(int win,sf::RenderWindow &window)
{
	for (int i = 0; i < length; i++)			
		for (int j = 0; j < width; j++)
			if (mat[i][j] == -1)
				if (viz[i][j] == 0)
					viz[i][j] = 1;				//viziteaza toate bombele nevizitate
				else
					if (viz[i][j] == 2)
						viz[i][j] = 3;			//marcheaza diferit minele dezamorsate
	board.gameOver(mat,viz,length,width,mode,window,win);		//afisarea matricii finale 
}

void Game::gameOverFocus(int element, bool focus)
{
	board.gameOverFocus(element, focus);
}

void Game::timer(int m,int s, sf::RenderWindow &window)
{
	board.timer(m,s,window);
}

bool Game::middleClick(int x, int y)
{
	int oriz[8] = { -1,-1,-1,0,1,1,1,0 };
	int vert[8] = { -1,0,1,1,1,0,-1,-1 };
	bool mine = false;
	position(x, y);
	if (viz[y][x] == 0)				//se analizeaza patratul in care s-a apasat middle-click
	{
		viz[y][x] = 1;
		if (mat[y][x] > 0)
			nrCorrect_box++;
		else
			if (mat[y][x] == 0)
				safeZone(y, x);
			else
				if (mat[y][x] == -1)
					mine = true;
		if(mat[y][x]!=0)
		for(int i=0;i<8;i++)															//se analizeaza toata zona de 3x3
			if(oriz[i]+y>=0 && oriz[i]+y<length && vert[i]+x>=0 && vert[i]+x<width)
				if (viz[oriz[i] + y][vert[i] + x] == 0)
				{
					viz[oriz[i] + y][vert[i] + x] = 1;
					if (mat[oriz[i] + y][vert[i] + x] > 0)
						nrCorrect_box++;
					else
						if (mat[oriz[i] + y][vert[i] + x] == 0)
							safeZone(oriz[i] + y, vert[i] + x);
						else
							if (mat[oriz[i] + y][vert[i] + x] == -1)
								mine = true;									//verifica daca s-a apasat pe o mina
				}
	}
	return mine;
}
