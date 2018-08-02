#include <iostream>
#include <string>
#include "baseClasses.h"
#include "chessPiece.h"
#include "chessBoard.h"

using namespace std;

enum colors { Black = 0, White = 1 };
enum pieces { King = 0, Queen = 1, Bishop = 2, Knight = 3, Rook = 4, Pawn = 5 };

const string ColorStrings[2] = { "Black","White" };

const int MAX_POSITION = 7;
const int MIN_POSITION = 0;

class Color
{
public:
	Color(colors color = White) :color(color) {};

	colors getColor() { return color; }

	string colorStr() { return ColorStrings[color]; }

	void printColor() { cout << ColorStrings[color]; }
	
	Color& operator++()
	{
		this->color = (colors)(((int)this->color + 1) % 2);
		return *this;
	}

	Color operator++(int)
	{
		Color ret(this->color);
		++(*this);
		return ret;
	}

private:
	colors color;
};

class Position
{
public:
	Position(int row = 0, int col = 0) :row(row), col(col) {}
	bool operator==(Position& otherPos)
	{
		return ((this->row == otherPos.getRow()) && (this->col == otherPos.getCol()));
	}
	void advance(int rows, int cols)
	{
		this->row += rows;
		this->col += cols;
	}
	void setPosition(int row, int col)
	{
		this->row = row;
		this->col = col;
	}
	int getRow() { return row; };
	int getCol() { return col; };
	bool getFromUser()
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
	Position operator=(Position other)
	{
		row = other.getRow();
		col = other.getCol();
	}
private:
	int row;
	int col;
};

class PositionNode :public Position
{
public:
	PositionNode(int row, int col) :Position(row, col), Next(nullptr) {};
	PositionNode* getNext()
	{
		return Next;
	}
	~PositionNode()
	{
		if (Next != nullptr) delete(Next);
	}
	bool operator==(PositionNode& other)
	{
		return ((this->getRow() == other.getRow()) && (this->getCol() == other.getCol()));
	}
private:
	PositionNode * Next;
};

class ChessPiece
{
public:
	ChessPiece(colors color, int row, int col, pieces piece = King) :color(color), curPosition(row, col), possibleMoves(nullptr), piece(piece) {}
	~ChessPiece()
	{
		if (nullptr != possibleMoves) delete(possibleMoves);
	}
	bool isLegalMove(Position * target)
	{
		PositionNode * check = possibleMoves;
		PositionNode * targetNode = new PositionNode(target->getRow(), target->getCol());
		while (check != nullptr)
		{
			if (check == targetNode) return true;
			check = check->getNext();
		}
		delete(targetNode);
		return false;
	}
	colors getColor() { return color; }
	pieces getPiece() { return piece; }
	PositionNode * getPossibleMoves() { return possibleMoves; }
	virtual void addAllPossibleMoves() = 0;
	virtual void printPiece() = 0;
private:
	const colors color;
	const pieces piece;
	Position curPosition;
	PositionNode* possibleMoves;
};

class KingPiece :public ChessPiece
{
public:
	KingPiece(colors color, int row, int col, pieces piece = King) :ChessPiece(color, row, col, piece) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BK";
		else                           cout << "WK";
	}
};

class QueenPiece :public ChessPiece
{
public:
	QueenPiece(colors color, int row, int col, pieces piece = Queen) :ChessPiece(color, row, col, piece) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BQ";
		else                           cout << "WQ";
	}
};

class BishopPiece :public ChessPiece
{
public:
	BishopPiece(colors color, int row, int col, pieces piece = Bishop) :ChessPiece(color, row, col, piece) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BB";
		else                           cout << "WB";
	}
};

class KnightPiece :public ChessPiece
{
public:
	KnightPiece(colors color, int row, int col, pieces piece = Knight) :ChessPiece(color, row, col, piece) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BH";
		else                           cout << "WH";
	}
};

class RookPiece :public ChessPiece
{
public:
	RookPiece(colors color, int row, int col, pieces piece = Rook) :ChessPiece(color, row, col, piece) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BR";
		else					       cout << "WR";
	}
};

class PawnPiece :public ChessPiece
{
public:
	PawnPiece(colors color, int row, int col, pieces piece = Pawn) :ChessPiece(color, row, col, piece) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BP";
		else						   cout << "WP";
	}
};

class ChessBoard
{
public:
	ChessBoard()
	{
		Board[0][0] = new RookPiece(White, 0, 0);
		Board[0][1] = new KnightPiece(White, 0, 1);
		Board[0][2] = new BishopPiece(White, 0, 2);
		Board[0][3] = new QueenPiece(White, 0, 3);
		Board[0][4] = new KingPiece(White, 0, 4);
		Board[0][5] = new BishopPiece(White, 0, 5);
		Board[0][6] = new KnightPiece(White, 0, 6);
		Board[0][7] = new RookPiece(White, 0, 7);
		Board[7][0] = new RookPiece(Black, 7, 0);
		Board[7][1] = new KnightPiece(Black, 7, 1);
		Board[7][2] = new BishopPiece(Black, 7, 2);
		Board[7][3] = new QueenPiece(Black, 7, 3);
		Board[7][4] = new KingPiece(Black, 7, 4);
		Board[7][5] = new BishopPiece(Black, 7, 5);
		Board[7][6] = new KnightPiece(Black, 7, 6);
		Board[7][7] = new RookPiece(Black, 7, 7);

		for (int i = 0; i < 8; i++) Board[1][i] = new PawnPiece(White, 1, i);
		for (int i = 0; i < 8; i++) Board[6][i] = new PawnPiece(Black, 6, i);

		for (int i = 2; i < 6; i++) for (int j = 0; j < 8; j++) Board[i][j] = nullptr;

		WhiteKing.setPosition(0, 4);
		BlackKing.setPosition(7, 4);

		curTurn = White;
	}

	void printBoard()
	{
		cout << "-----------------------------------------" << endl;
		for (int i = 7; i >= 0; i--)
		{
			cout << "| ";
			for (int j = 0; j < 8; j++)
			{
				if (nullptr == Board[i][j]) cout << "  ";
				else Board[i][j]->printPiece();
				cout << " | ";
			}
			if (i != 0) cout << endl << "|---------------------------------------|" << endl;
		}
		cout << endl << "-----------------------------------------" << endl;
	}

	bool isCheck(colors color)
	{
		Position kingPosition = (color == Black) ? BlackKing : WhiteKing;
		return false;
	}
	
	bool isCheckMate(colors color)
	{
		Position kingPosition = (color == Black) ? BlackKing : WhiteKing;
	    return false;
	}

	bool isEmpty(Position * choice) { return (Board[choice->getRow()][choice->getCol()] == nullptr); }

	bool isOppositeColor(Position * choice)
	{
		return (Board[choice->getRow()][choice->getCol()]->getColor() != curTurn);
	}

	bool isLegalPiece(Position * pickUp)
	{
		int row = pickUp->getRow(), col = pickUp->getCol();
		ChessPiece * curPiece = Board[pickUp->getRow()][pickUp->getCol()];
		if (isEmpty(pickUp))
		{
			cout << "There is no piece there!" << endl;
			return false;
		}
		if (isOppositeColor(pickUp))
		{
			cout << "Piece is of the opposite color." << endl;
			return false;
		}
		Board[row][col] = nullptr;
		bool cannotMove = isCheck(curTurn);
		Board[row][col] = curPiece;
		if (cannotMove)
		{
			cout << "Moving this piece leaves your King in check." << endl;
			return false;
		}
		curPiece->addAllPossibleMoves();
		if (curPiece->getPossibleMoves() == nullptr)
		{
			cout << "This piece has no legal moves available." << endl;
			return false;
		}
		return true;
	}

	Position * pickUpPiece()
	{
		Position * choice = new Position;
		bool userChoseLegalPiece = false;
		cout << "Next move: " << ColorStrings[curTurn] << endl;
		while (!userChoseLegalPiece)
		{
			while (!choice->getFromUser()) cout << "Try again:" << endl;
			if (!isLegalPiece(choice)) cout << "Try again:" << endl;
			else userChoseLegalPiece = true;
		}
		return choice;
	}

	void createNewPiece(Position * target)
	{
		bool userEntryCorrect = false;
		char entry;
		
		cout << "Pawn reached end of board!" << endl;
		cout << "Choose piece to turn into: (Q - Queen, R - Rook, B - Bishop, K - Knight)" << endl;
		while (!userEntryCorrect)
		{
			cin >> entry;
            switch (entry)
            {
                case 'Q':
				Board[target->getRow()][target->getCol()] = new QueenPiece(curTurn, target->getRow(), target->getCol());
				userEntryCorrect = true;
                break;
                case 'R':
				Board[target->getRow()][target->getCol()] = new RookPiece(curTurn, target->getRow(), target->getCol());
				userEntryCorrect = true;
                break;
                case 'B':
				Board[target->getRow()][target->getCol()] = new BishopPiece(curTurn, target->getRow(), target->getCol());
				userEntryCorrect = true;
                break;
                case 'K':
				Board[target->getRow()][target->getCol()] = new KnightPiece(curTurn, target->getRow(), target->getCol());
				userEntryCorrect = true;
                break;
                default:
                cout << "Input must be Q, R, B or K." << endl;
            }
		}
	}

	bool movePiece(Position * origin)
	{
		Position * target;
		ChessPiece * movingPiece = Board[origin->getRow()][origin->getCol()];
		bool userChoseLegalTarget = false;
		colors opponent = (curTurn == Black) ? White : Black;
		cout << "Move where?" << endl;
		while (!userChoseLegalTarget)
		{
			while (!target->getFromUser()) cout << "Try again:" << endl;
			if (!movingPiece->isLegalMove(target)) cout << "Try again:" << endl;
			else userChoseLegalTarget = true;
		}
		if (nullptr != Board[target->getRow()][target->getCol()])
			delete(Board[target->getRow()][target->getCol()]);
		Board[target->getRow()][target->getCol()] = movingPiece;
		Board[origin->getRow()][origin->getCol()] = nullptr;
		if (movingPiece->getPiece() == Pawn && ((movingPiece->getColor() == Black && target->getRow() == 0) ||
			(movingPiece->getColor() == White && target->getRow() == 7)))
		{
			delete(movingPiece);
			createNewPiece(target);
		}
		else if (movingPiece->getPiece() == King)
		{
			if (curTurn == Black) BlackKing = *target;
			else                  WhiteKing = *target;
		}
		
		if (isCheck(opponent))
		{
			if (isCheckMate(opponent))
			{
				cout << "Checkmate!!! " << ColorStrings[curTurn] << " wins!!!" << endl;
				return true;
			}
			cout << "Check!" << endl;
		}
		
		return false;
	}

	bool nextTurn()
	{
		Position * pieceToMove = pickUpPiece();
		colors opponent = curTurn == Black ? White : Black;
		movePiece(pieceToMove);
		if (isCheck(opponent))
		{
			if (isCheckMate(opponent))
			{
				cout << "Checkmate!!! " << ColorStrings[curTurn] << " wins!!!" << endl;
				return true;
			}
			cout << "Check!" << endl;
		}
		return false;
	}

private:
	ChessPiece * Board[8][8];
	Position	 WhiteKing;
	Position	 BlackKing;
	colors       curTurn;
};

int main()
{
	ChessBoard myBoard;
	myBoard.printBoard();
	Position foo(1, 2);
	foo.advance(1, 2);
	Position foo2(2, 3);
	cout << (bool)(foo == foo2) << endl;
	cout << foo.getRow() << ' ' << foo.getCol() << endl;
	return 0;
}
