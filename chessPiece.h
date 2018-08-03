#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#include "baseClasses.h"

class ChessPiece
{
public:
	ChessPiece(colors color, int row, int col, pieces piece = King);
	~ChessPiece();
	bool isLegalMove(Position * target);
	Color getColor() { return color; }
	pieces getPiece() { return piece; }
	PositionNode * getPossibleMoves() { return possibleMoves; }
	void printPiece();
	virtual void addAllPossibleMoves() = 0;
private:
	Color color;
	pieces piece;
	Position curPosition;
	PositionNode* possibleMoves;
};

class KingPiece :public ChessPiece
{
public:
	KingPiece(colors color, int row, int col, pieces piece = King);
	void addAllPossibleMoves();
};

class QueenPiece :public ChessPiece
{
public:
	QueenPiece(colors color, int row, int col, pieces piece = Queen);
	void addAllPossibleMoves();
};

class BishopPiece :public ChessPiece
{
public:
	BishopPiece(colors color, int row, int col, pieces piece = Bishop);
	void addAllPossibleMoves();
};

class KnightPiece :public ChessPiece
{
public:
	KnightPiece(colors color, int row, int col, pieces piece = Knight);
	void addAllPossibleMoves();
};

class RookPiece :public ChessPiece
{
public:
	RookPiece(colors color, int row, int col, pieces piece = Rook);
	void addAllPossibleMoves();
};

class PawnPiece :public ChessPiece
{
public:
	PawnPiece(colors color, int row, int col, pieces piece = Pawn);
	void addAllPossibleMoves();
};

#endif // CHESS_PIECES_H