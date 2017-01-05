#pragma once

class Game
{
public:
	Game();
	void init(char difficulty);
	void initVizMatrix();
	void firstInput();
	void inGame(int x,int y, char mouse);
	bool mouseInBoard(int x, int y);
	void firstClickLeft(int x, int y);
	void drawBoard(sf::RenderWindow &window);
	bool ifMine(int x, int y);
	bool ifGameWin();
	void prepareTextures();
	void gameOver(int win,sf::RenderWindow &window);
	void gameOverFocus(int element, bool focus);
private:
	int mat[16][30];
	int length;
	int width;
	int viz[16][30];
	int nrFlags;
	int nrMines;
	int nrCorrect_box;
	char mode;
	void position(int &x, int &y);
	void safeZone(int x, int y);
	void matrix(int x, int y);
	bool isNotMineFirst(int x, int y, int newX, int newY);
};

