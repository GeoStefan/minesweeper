#include <iostream>
#include <stdlib.h>
#include <random>  
#include <ctype.h>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Board.h"
using namespace std;

Afisare board;

Game::Game()
{

}

void Game::init(char difficulty)
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
	cout << "difi " << mode <<" length " <<length<<" width "<<width<< endl;
	for(int i=0;i<length;i++)
		for (int j = 0; j < width; j++)
		{
			mat[i][j] = 0;
			viz[i][j] = 0;
		}
	nrFlags = 0;
	nrCorrect_box = 0;
}

bool Game::mouseInBoard(int x, int y)
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

void Game::position(int &x, int &y)
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

bool Game::isNotMineFirst(int x, int y, int newX, int newY)
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
	/*for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			mat[i][j] = 0;*/
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, width - 1);
	int i = 0, l, c;
	int oriz[8] = { -1,-1,-1,0,1,1,1,0 };
	int vert[8] = { -1,0,1,1,1,0,-1,-1 };
	while (i < nrMines)
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

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (mat[i][j] == 0)
				for (int k = 0; k < 8; k++)
					if (oriz[k] + i >= 0 && oriz[k] + i < length && vert[k] + j >= 0 && vert[k] + j < width)
						if (mat[oriz[k] + i][vert[k] + j] == -1)
							mat[i][j]++;
}

void Game::safeZone(int x, int y)
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

void Game::firstClickLeft(int x, int y)
{
	int coordx = x, coordy = y;
	position(coordx, coordy);
	//cout << "coordonatele in firstclick " << coordy << " " << coordx << endl;
	viz[coordy][coordx] = 1;
	matrix(coordy, coordx);
	safeZone(coordy, coordx);
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
			cout << " " << mat[i][j] << " ";
		cout << endl;
	}
	cout << endl;/*
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
			cout << viz[i][j] << " ";
		cout << endl;
	}*/
}

void Game::drawBoard(sf::RenderWindow &window)
{
	board.afisareMatrix(mat, viz, length, width, mode, window, nrMines-nrFlags);
}

bool Game::ifMine(int x, int y)
{
	int coordx = x, coordy = y;
	position(coordx, coordy);
	if (mat[coordy][coordx] == -1)
		return true;
	return false;
}

bool Game::ifGameWin()
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
			viz[y][x] = 1;
			if (mat[y][x] != -1)
				nrCorrect_box++;
			if (mat[y][x] == 0)
			{
				nrCorrect_box--;
				safeZone(y, x);
			}
		}
		else
			if (nrFlags < maxFlags)
			{
				viz[y][x] = 2;
				nrFlags++;
			}
			else
				cout << endl << "Ai folosit deja toate steagurile posibile " << endl;
	else
		if (viz[y][x] == 2 && mouse == 'd')
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
					viz[i][j] = 1;
				else
					if (viz[i][j] == 2)
						viz[i][j] = 3;
	board.gameOver(mat,viz,length,width,mode,window,win);
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
	if (viz[y][x] == 0)
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
		for(int i=0;i<8;i++)
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
								mine = true;
				}
	}
	return mine;
}