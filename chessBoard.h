#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "chessPiece.h"

class ChessBoard
{
public:
	ChessBoard();

	void printBoard();

	bool isCheck(colors color);

	bool isCheckMate(colors color);

	bool isEmpty(Position * choice);

	bool isOppositeColor(Position * choice);

	bool isLegalPiece(Position * pickUp);

	Position * pickUpPiece();

	void createNewPiece(Position * target);

	bool movePiece(Position * origin);

	bool nextTurn();

private:
	ChessPiece * Board[8][8];
	Position	 WhiteKing;
	Position	 BlackKing;
	colors       curTurn;
};

#endif // CHESS_BOARD_H