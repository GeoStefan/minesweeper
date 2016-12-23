/*
		Minesweeper game
		author: Popescu Georgian-Stefan
		group: A7
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

int mat[30][16],length,width;
void matrix(int lenght, int width)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			mat[i][j] = 0;
}

void afisareMat(int length, int width)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
			if (mat[i][j] == 0)
				cout << "# ";
			else
				cout << mat[i][j] << " ";
		cout << endl;
	}
}

void meniu()
{
	cout << "		Minesweeper " << endl;
	cout << "		Welcome! " << endl << endl;
	cout << " Choose difficulty to continue" << endl;
	cout << " E- Easy ( 9x9 )   M- Medium ( 16x16 )   H- Hard ( 30x16 )" << endl;
	char difficulty;
	cin >> difficulty;
	system("cls");
	switch (difficulty)
	{
	case 'E':
		length = 9;
		width = 9; 
		cout << "Easy mode" << endl;
		break;
	case 'M':
		length = 16;
		width = 16;
		cout << "Medium mode" << endl;
		break;
	case 'H':
		length = 30;
		width = 16;
		cout << "Hard mode" << endl;
		break;
	}
	matrix(length, width);
	afisareMat(length, width);
}

int main()
{
	cout << endl << endl << endl;
	meniu();
	return 0;
}