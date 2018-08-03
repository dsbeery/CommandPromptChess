#include "baseClasses.h"

Color::Color(colors color) :color(color) {};

colors Color::getColor()
{ 
	return color; 
}

string Color::colorStr()
{ 
	return ColorStrings[color]; 
}

void Color::printColor() 
{ 
	cout << ColorStrings[color]; 
}

void Color::printColorLetter()
{
	cout << ColorLetters[color];
}

Color& Color::operator++()
{
	this->color = (colors)(((int)this->color + 1) % 2);
	return *this;
}

Color Color::operator++(int)
{
	Color ret(this->color);
	++(*this);
	return ret;
}

bool Color::operator==(Color& other)
{
	return (color == other.getColor());
}

bool Color::operator!=(Color& other)
{
	return (color != other.getColor());
}


Position::Position(int row, int col) :row(row), col(col) {};
bool Position::operator==(Position& otherPos)
{
	return ((this->row == otherPos.getRow()) && (this->col == otherPos.getCol()));
}
void Position::advance(int rows, int cols)
{
	this->row += rows;
	this->col += cols;
}
void Position::setPosition(int row, int col)
{
	this->row = row;
	this->col = col;
}
bool Position::getFromUser()
{
	string input;
	cin >> input;
	if (input.length() != 2)
	{
		cout << "Input must be only 2 characters long." << endl;
		return false;
	}
	if (!((input[0] >= 'a' && input[0] <= 'h') || (input[0] >= 'A' && input[0] <= 'H')))
	{
		cout << "First character must be between A and H." << endl;
		return false;
	}
	if (!(input[1] >= '1' && input[1] <= '8'))
	{
		cout << "Second character must be between 1 and 8." << endl;
		return false;
	}

	row = input[1] - '1';
	col = (input[0] <= 'h' && input[0] >= 'a') ? input[0] - 'a' : input[0] - 'A';
	return true;
}
Position Position::operator=(Position other)
{
	this->setPosition(other.getRow(), other.getCol());
	return *this;
}



PositionNode::PositionNode(int row, int col) :Position(row, col), Next(nullptr) {};
PositionNode* PositionNode::getNext()
{
	return Next;
}
PositionNode::~PositionNode()
{
	if (Next != nullptr) delete(Next);
}
bool PositionNode::operator==(PositionNode& other)
{
	return ((this->getRow() == other.getRow()) && (this->getCol() == other.getCol()));
}