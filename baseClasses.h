#ifndef BASE_CLASSES_H
#define BASE_CLASSES_H

#include <iostream>
#include <string>

using namespace std;

enum colors { Black = 0, White = 1 };
enum pieces { King = 0, Queen = 1, Bishop = 2, Knight = 3, Rook = 4, Pawn = 5 };

const int COLORS_NUM = 2;
const int PIECES_NUM = 6;
const int BOARD_SIZE = 8;
const int MAX_POSITION = BOARD_SIZE - 1;
const int MIN_POSITION = 0;

const string ColorStrings[COLORS_NUM] = { "Black","White" };
const char ColorLetters[COLORS_NUM] = { 'B','W' };
const char PieceLetters[PIECES_NUM] = { 'K','Q','B','H','R','P' };

class Color
{
public:
	Color(colors color = White);

	colors getColor();

	string colorStr();

	void printColor();

	void printColorLetter();

	Color& operator++();

	Color operator++(int);

	bool operator==(Color& other);
	bool operator!=(Color& other);

private:
	colors color;
};

class Position
{
public:
	Position(int row = 0, int col = 0);
	bool operator==(Position& otherPos);
	void advance(int rows, int cols);
	void setPosition(int row, int col);
	int getRow() { return row; };
	int getCol() { return col; };
	bool getFromUser();
	Position operator=(Position other);
private:
	int row;
	int col;
};

class PositionNode :public Position
{
public:
	PositionNode(int row, int col);
	PositionNode* getNext();
	~PositionNode();
	bool operator==(PositionNode& other);
private:
	PositionNode * Next;
};

#endif // BASE_CLASSES_H