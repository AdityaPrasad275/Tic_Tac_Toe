#ifndef CPPCODES_TIC_TAC_TOE
#define CPPCODES_TIC_TAC_TOE

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;


class gameManager {
public:
	void start();
private:
	void init(); //setting the board , symbol and filling up vector
	void inputSymbol(char input_symbol);
	void print();
	bool somebodyWon();

	//components of somebody won
	bool checkColumn(char symbol);
	bool checkRow(char symbol);
	bool checkDiagonal_LeftRight(char symbol); // top left to bottom right
	bool checkDiagonal_RightLeft(char symbol); // top right to bottom left

	int sideLength = 0, xPos = 0, yPos = 0;
	char sPlayer1 = '.', sPlayer2 = '.'; //s for symbol
	std::vector<string> map;
};

#endif
