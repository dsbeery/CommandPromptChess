#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#include "baseClasses.h"

class ChessPiece
{
public:
	ChessPiece(colors color, int row, int col, pieces piece = King);
	~ChessPiece();
	bool isLegalMove(Position * target);
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
	KingPiece(colors color, int row, int col, pieces piece = King);
	void addAllPossibleMoves();
	void printPiece();
};

class QueenPiece :public ChessPiece
{
public:
	QueenPiece(colors color, int row, int col, pieces piece = Queen);
	void addAllPossibleMoves();
	void printPiece();
};

class BishopPiece :public ChessPiece
{
public:
	BishopPiece(colors color, int row, int col, pieces piece = Bishop);
	void addAllPossibleMoves();
	void printPiece();
};

class KnightPiece :public ChessPiece
{
public:
	KnightPiece(colors color, int row, int col, pieces piece = Knight);
	void addAllPossibleMoves();
	void printPiece();
};

class RookPiece :public ChessPiece
{
public:
	RookPiece(colors color, int row, int col, pieces piece = Rook);
	void addAllPossibleMoves();
	void printPiece();
};

class PawnPiece :public ChessPiece
{
public:
	PawnPiece(colors color, int row, int col, pieces piece = Pawn);
	void addAllPossibleMoves();
	void printPiece();
};

#endif // CHESS_PIECES_H