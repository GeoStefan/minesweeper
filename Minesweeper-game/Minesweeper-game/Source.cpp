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
void matrix(int lenght, int width, unsigned nrMines)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			mat[i][j] = 0;
	random_device rd;    
	mt19937 gen(rd());   
	uniform_int_distribution<> dist(0, width-1);
	int i = 0,l,c;
	while (i < nrMines)
	{
		l = dist(gen);
		c = dist(gen);
		while (l >= length)
		{
			l = dist(gen);
		}
		if (mat[l][c] == 0)
		{
			mat[l][c] = -1;
			i++;
		}
	}
	int oriz[8] = { -1,-1,-1,0,1,1,1,0 };
	int vert[8] = { -1,0,1,1,1,0,-1,-1 };
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (mat[i][j] == 0)
				for (int k = 0; k < 9; k++)
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
	char x = 254;
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
				cout << " "<< x << " ";
			else
				if (viz[i][j] == 2)
					cout << " " << "P ";
			else
				if (mat[i][j] == -1)
					cout << " " << "X ";
				else
					if (mat[i][j] == 0)
						cout << "   ";
					else
						cout << " " << mat[i][j] << " ";
		cout << endl;
	}
}

void initVizMatrix()
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			viz[i][j] = 0;
}

void inGame()
{
	char mouse_button;
	int gameOver = 0, coord_x, coord_y;
	while (!gameOver)
	{

		
		afisareMatrix();
		afisareMat(length, width);
		cout << "Introdu coordonatele casutei selectate ";
		cin >> coord_x >> coord_y;
		cout << endl << "Introdu s-click stanga, d-click dreapta ";
		cin >> mouse_button;
		//ifBomb();
		//ifSafe();
		if (viz[coord_x][coord_y] == 0)
			if (mouse_button == 's')
				viz[coord_x][coord_y] = 1;
			else
				viz[coord_x][coord_y] = 2;
		cout << endl << "Game over? ";
		cin >> gameOver;
		system("cls");
	}
}

void meniu()
{
	int replay = 1;
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
			break;
		case 'M':
			length = 16;
			width = 16;
			nrMines = 30;
			cout << "Medium mode" << endl;
			break;
		case 'H':
			length = 16;
			width = 30;
			nrMines = 80;
			cout << "Hard mode" << endl;
			break;
		}
		matrix(length, width, nrMines);
		//afisareMat(length, width);
		initVizMatrix();
		inGame();
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