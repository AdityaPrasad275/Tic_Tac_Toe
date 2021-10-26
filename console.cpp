#include "Console.h"

void gameManager::start()
{
	bool leave = false, checkifWon = false;
	int i = 0;//this keeps track of move, (i+1)th move , so it mustn't exceed (sidelength)^2

	while (!leave) {
		system("CLS");//fresh start 

		cout << "welcome to the game!\n\n\n\n";
		cout << "NOTE: To mark your symbol please use coordinate system\n";

		init();
		print(); //inital map ready

		while (!checkifWon && i < sideLength*sideLength) {
			// taking input for both players one after another
			if (i % 2 == 0) {
				inputSymbol(sPlayer1);
			}
			else {
				inputSymbol(sPlayer2);
			}
			print();
			
			//checking to see if somebody wins only after move 4 (small optimization)
			if (i > 3) {
				checkifWon = somebodyWon();
			}

			i++;
		}

		//setting the things back to inital as game is over
		map.clear();
		checkifWon = false;

		cout << "\nDo you want to leave ? 1(True) or 0(False)";
		cin >> leave;
	}
}

void gameManager::init()
{
	//setting the board
	cout << "\n\n\nplease set the side length of the board (square board): ";
	cin >> sideLength;

	//error check
	while (sideLength < 3) {
		cout << "\nThe side Length can't be less the 3, please set the sideLength again: ";
		cin >> sideLength;
		cout << endl;
	}

	cout << "\nPlayer 1, please select the symbol you'd like to have: ";
	cin >> sPlayer1;

	cout << "\nPlayer 2, please select the symbol you'd like to have: ";
	cin >> sPlayer2;

	//filling the vector 
	string row;
	
	//making one row
	for (int i = 0; i < sideLength; i++)
	{
		row = row + ".";
	}
	//filling the vector 
	for (int i = 0; i < sideLength; i++)
	{
		map.push_back(row);
	}
}

void gameManager::inputSymbol(char input_symbol)
{
	cout << "x coordinate: ";
	cin >> xPos;
	cout << "y coordinate: ";
	cin >> yPos;
	//no idea what to do with the green squigly line
	if(map[yPos - 1][xPos - 1] != sPlayer1 && map[yPos - 1][xPos - 1] != sPlayer2)
		map[yPos - 1][xPos - 1] = input_symbol;
	else {
		inputSymbol(input_symbol); //loop to ensure that correct coordinates are given
	}
}

void gameManager::print()
{
	system("CLS");
	//side length + 1 for printing out the numbers at the side (kind of x axis and y axis)
	for (int i = 0; i < sideLength + 1; i++)
	{
		for (int j = 0; j < sideLength + 1; j++)
		{
			if (i == 0 && j == 0)
				cout << "0";
			else if (i == 0 && j != 0)
				cout << "| " << j;
			else if (j == 0 && i != 0)
				cout << i;
			else
				cout << "| " << map[i - 1][j - 1];
		}
		cout << endl;
	}
}

bool gameManager::somebodyWon()
{
	//the repetitive checking bugs me a lot, tho no idea if it is possible to avoid them

	if (checkColumn(sPlayer1) || checkRow(sPlayer1) || checkDiagonal_LeftRight(sPlayer1) || checkDiagonal_RightLeft(sPlayer1)) {
		system("CLS");
		cout << "Congrats Player 1 you've won !!!";
		return true;
	}
	else if (checkColumn(sPlayer2) || checkRow(sPlayer2) || checkDiagonal_LeftRight(sPlayer2) || checkDiagonal_RightLeft(sPlayer2)) {
		system("CLS");
		cout << "Congrats Player 2 you've won !!!";
		return true;
	}
	else
		return false;
}

bool gameManager::checkColumn(char symbol)
{
	//compares three things ( 3 vertical symbols ) at a time, moves through the vector
	// -2 because the (number side length - 3) needs to be checked and also because up to down movemnt is limited
	for (int i = 0; i < sideLength; i++)
	{
		for (int j = 0; j < sideLength - 2; j++)
		{
			if (map[j][i] == symbol && map[j + 1][i] == symbol && map[j + 2][i] == symbol)
				return true;
		}
	}

	return false;
}

bool gameManager::checkRow(char symbol)
{
	//same as check coloumn, but this time the left to right movement is limited so - 2
	for (int i = 0; i < sideLength - 2; i++)
	{
		for (int j = 0; j < sideLength; j++)
		{
			if (map[j][i] == symbol && map[j][i + 1] == symbol && map[j][i + 2] == symbol)
				return true;
		}
	}
	return false;
}

bool gameManager::checkDiagonal_LeftRight(char symbol)
{
	//the whole thing is limited by how many 3 box diagonals you can draw 
	// 1 in 3*3, 4 in 4*4 , 9 in 5*5
	for (int i = 0; i < sideLength - 1; i++)
	{
		for (int j = 0; j < sideLength - 1; j++)
		{
			if (map[i][j] == symbol && map[i + 1][j + 1] == symbol && map[i + 2][j + 2] == symbol)
				return true;
		}
	}
	return false;
}

bool gameManager::checkDiagonal_RightLeft(char symbol)
{
	//same as above
	for (int i = 0; i < sideLength - 2; i++)
	{
		for (int j = sideLength - 1; j >= 2; j--)
		{
			if (map[i][j] == symbol && map[i + 1][j - 1] == symbol && map[i + 2][j - 2] == symbol)
				return true;
		}
	}
	return false;
}
