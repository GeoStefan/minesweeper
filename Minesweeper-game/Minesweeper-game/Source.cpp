/*
		Minesweeper game
		author: Popescu Georgian-Stefan
		group: A7
*/
#include <iostream>
#include <stdlib.h>
#include <random>  
#include <ctype.h>
using namespace std;

int mat[16][30],length,width,viz[16][30];

bool isNotMineFirst(int x, int y, int newX, int newY, int oriz[8], int vert[8])
{
	if (x == newX && y == newY)
		return false;
	for (int i = 0; i < 8; i++)
		if (x + oriz[i] == newX && y + vert[i] == newY)
			return false;
	return true;
}

void matrix(int lenght, int width, unsigned nrMines, int first_x, int first_y)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			mat[i][j] = 0;
	random_device rd;    
	mt19937 gen(rd());   
	uniform_int_distribution<> dist(0, width-1);
	int i = 0,l,c;
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
			if(isNotMineFirst(first_x, first_y, l, c, oriz, vert))
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

void afisareMat(int length, int width)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
			if (mat[i][j] == 0)
				cout << "# ";
			else
				if (mat[i][j] == -1)
					cout << "X ";
				else
					cout << mat[i][j] << " ";
		cout << endl;
	}
}

void afisareMatrix()
{
	char x = 254, y=248;
	cout << "   ";
	for (int k = 0; k < width; k++)
		if (k > 9)
			cout << k << " ";
		else
			cout << " " << k << " ";
	cout << endl;
	for (int i = 0; i < length; i++)
	{
		if (i > 9)
			cout << i << " ";
		else
			cout << " "<< i << " ";
		for (int j = 0; j < width; j++)
			if (viz[i][j] == 0)
				cout << " " << x << " ";
			else
				if (viz[i][j] == 2)
					cout << " " << "P ";
				else
					if (viz[i][j] == 1)
					{
						if (mat[i][j] == -1)
							cout << " " << "X ";
						else
							if (mat[i][j] == 0)
								cout << "   ";
							else
								cout << " " << mat[i][j] << " ";
					}
					else
						if (viz[i][j] == 3)
							cout << " " << y << " ";
					
		cout << endl;
	}
}

void initVizMatrix()
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			viz[i][j] = 0;
}

void safeZone(int x, int y)
{
	viz[x][y] = 1;
	if (x - 1 >= 0 && y - 1 >= 0 && mat[x - 1][y - 1] == 0 && viz[x - 1][y - 1] == 0)
		safeZone(x - 1, y - 1);
	if (x - 1 >= 0 && mat[x - 1][y] == 0 && viz[x - 1][y] == 0)
		safeZone(x - 1, y);
	if (x - 1 >= 0 && y + 1 <width && mat[x - 1][y + 1] == 0 && viz[x - 1][y + 1] == 0)
		safeZone(x - 1, y + 1);
	if (y + 1 <width && mat[x][y + 1] == 0 && viz[x][y + 1] == 0)
		safeZone(x, y + 1);
	if (x + 1 <length && y + 1 <width && mat[x + 1][y + 1] == 0 && viz[x + 1][y + 1] == 0)
		safeZone(x + 1, y + 1);
	if (x + 1 <length && mat[x + 1][y] == 0 && viz[x + 1][y] == 0)
		safeZone(x + 1, y);
	if (x + 1 <length && y - 1 >= 0 && mat[x + 1][y - 1] == 0 && viz[x + 1][y - 1] == 0)
		safeZone(x + 1, y - 1);
	if (y - 1 >= 0 && mat[x][y - 1] == 0 && viz[x][y - 1] == 0)
		safeZone(x, y - 1);
}

void firstInput(int nrMines)
{
	int coord_x, coord_y;
	afisareMatrix();
	cout << "Introdu coordonatele casutei selectate " << endl;
	cin >> coord_x >> coord_y;
	matrix(length, width, nrMines,coord_x,coord_y);
	viz[coord_x][coord_y] = 1;
	safeZone(coord_x,coord_y);
	system("cls");
}

void gameOver(int win)
{
	system("cls");
	if (win == 1)
		cout << "Felicitari! Ai castigat! " << endl;
	else
		cout << "Game over! Ai lovit o mina! " << endl;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (mat[i][j] == -1)
				if (viz[i][j] == 0)
					viz[i][j] = 1;
				else
					if (viz[i][j] == 2)
						viz[i][j] = 3;
	afisareMatrix();
}

void inGame(int nrMines,char mode)
{
	char mouse_button;
	int game_Over = 0, coord_x, coord_y, maxFlags = nrMines, nrFlags = 0, win = 1;
	initVizMatrix();
	firstInput(nrMines);
	while (!game_Over)
	{
		switch (mode)
		{
		case 'e':
			cout << "Easy mode" << endl;
			break;
		case 'm':
			cout << "Medium mode" << endl;
			break;
		case 'h':
			cout << "Hard mode" << endl;
			break;
		}
		afisareMatrix();
		afisareMat(length, width);
		cout << "Introdu coordonatele casutei selectate "<<endl;
		cin >> coord_x >> coord_y;
		cout << endl << "Introdu s-click stanga, d-click dreapta ";
		cin >> mouse_button;
		
		if (viz[coord_x][coord_y] == 0)
			if (mouse_button == 's')
			{
				viz[coord_x][coord_y] = 1;
				if (mat[coord_x][coord_y] == 0)
					safeZone(coord_x, coord_y);
			}
			else
				if (nrFlags < maxFlags)
				{
					viz[coord_x][coord_y] = 2;
					nrFlags++;
				}
				else
					cout << endl << "Ai folosit deja toate steagurile posibile " << endl;
		else
			if (viz[coord_x][coord_y] == 2 && mouse_button == 'd')
			{
				viz[coord_x][coord_y] = 0;
				nrFlags--;
			}
		if (mouse_button == 's'&&mat[coord_x][coord_y] == -1)
		{
			game_Over = 1;
			win = 0;
		}
		
		system("cls");
	}
	gameOver(win);
}

void meniu()
{
	int replay = 1;
	char mode;
	while (replay)
	{
		cout << "		Minesweeper " << endl;
		cout << "		Welcome! " << endl << endl;
		cout << " Choose difficulty to continue" << endl;
		cout << " E- Easy ( 9x9 )   M- Medium ( 16x16 )   H- Hard ( 30x16 )" << endl;
		char difficulty;
		cin >> difficulty;
		system("cls");
		unsigned nrMines;
		switch (toupper(difficulty))
		{
		case 'E':
			length = 9;
			width = 9;
			nrMines = 10;
			cout << "Easy mode" << endl;
			mode = 'e';
			break;
		case 'M':
			length = 16;
			width = 16;
			nrMines = 30;
			cout << "Medium mode" << endl;
			mode = 'm';
			break;
		case 'H':
			length = 16;
			width = 30;
			nrMines = 80;
			cout << "Hard mode" << endl;
			mode = 'h';
			break;
		}
		
		//afisareMat(length, width);
		inGame(nrMines,mode);
		cout << endl << "Apasa 1 pentru a te intoarce la meniu sau 0 pentru a iesi ";
		cin >> replay;
		system("cls");
	}
}

int main()
{
	int exit = 0;
	while (!exit)
	{
		cout << endl << endl << endl;
		meniu();
		cout << "Sigur doresti sa iesi ? (1 pt a iesi/0 pt a ramane)"<<endl;
		cin >> exit;
		system("cls");
	}
	return 0;
}