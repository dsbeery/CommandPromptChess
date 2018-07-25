#include <iostream>
#include <string>

using namespace std;

enum colors { Black = 0, White = 1 };

const string ColorStrings[2] = { "Black","White" };

const int MAX_POSITION = 7;
const int MIN_POSITION = 0;

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
	ChessPiece(colors color, int row, int col) :color(color), curPosition(row, col), possibleMoves(nullptr) {}
	~ChessPiece()
	{
		if (nullptr != possibleMoves) delete(possibleMoves);
	}
	bool isLegalMove(Position target)
	{
		PositionNode* check = possibleMoves;
		PositionNode* targetNode = new PositionNode(target.getRow(), target.getCol());
		while (check != nullptr)
		{
			if (check == targetNode) return true;
			check = check->getNext();
		}
		delete(targetNode);
		return false;
	}
	colors getColor() { return color; }
	virtual void addAllPossibleMoves() = 0;
	virtual void printPiece() = 0;
private:
	const colors color;
	Position curPosition;
	PositionNode* possibleMoves;
};

class King :public ChessPiece
{
public:
	King(colors color, int row, int col) :ChessPiece(color, row, col) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BK";
		else                cout << "WK";
	}
};

class Queen :public ChessPiece
{
public:
	Queen(colors color, int row, int col) :ChessPiece(color, row, col) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BQ";
		else                cout << "WQ";
	}
};

class Bishop :public ChessPiece
{
public:
	Bishop(colors color, int row, int col) :ChessPiece(color, row, col) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BB";
		else                cout << "WB";
	}
};

class Knight :public ChessPiece
{
public:
	Knight(colors color, int row, int col) :ChessPiece(color, row, col) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BH";
		else                cout << "WH";
	}
};

class Rook :public ChessPiece
{
public:
	Rook(colors color, int row, int col) :ChessPiece(color, row, col) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BR";
		else                cout << "WR";
	}
};

class Pawn :public ChessPiece
{
public:
	Pawn(colors color, int row, int col) :ChessPiece(color, row, col) {}
	void addAllPossibleMoves()
	{

	}
	void printPiece()
	{
		if (this->getColor() == Black) cout << "BP";
		else                cout << "WP";
	}
};

class ChessBoard
{
public:
	ChessBoard()
	{
		Board[0][0] = new Rook(White, 0, 0);
		Board[0][1] = new Knight(White, 0, 1);
		Board[0][2] = new Bishop(White, 0, 2);
		Board[0][3] = new Queen(White, 0, 3);
		Board[0][4] = new King(White, 0, 4);
		Board[0][5] = new Bishop(White, 0, 5);
		Board[0][6] = new Knight(White, 0, 6);
		Board[0][7] = new Rook(White, 0, 7);
		Board[7][0] = new Rook(Black, 7, 0);
		Board[7][1] = new Knight(Black, 7, 1);
		Board[7][2] = new Bishop(Black, 7, 2);
		Board[7][3] = new Queen(Black, 7, 3);
		Board[7][4] = new King(Black, 7, 4);
		Board[7][5] = new Bishop(Black, 7, 5);
		Board[7][6] = new Knight(Black, 7, 6);
		Board[7][7] = new Rook(Black, 7, 7);

		for (int i = 0; i < 8; i++) Board[1][i] = new Pawn(White, 1, i);
		for (int i = 0; i < 8; i++) Board[6][i] = new Pawn(Black, 6, i);

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
