#include <iostream>
#include <string>
#include "baseClasses.h"
#include "chessPiece.h"
#include "chessBoard.h"

using namespace std;

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
