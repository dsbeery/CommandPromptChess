#include "chessPiece.h"

ChessPiece::ChessPiece(colors color, int row, int col, pieces piece) :color(Color(color)), curPosition(row, col), possibleMoves(nullptr), piece(piece) {};
ChessPiece::~ChessPiece()
{
	if (nullptr != possibleMoves) delete(possibleMoves);
}
bool ChessPiece::isLegalMove(Position * target)
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
void ChessPiece::printPiece()
{
	color.printColorLetter();
	cout << PieceLetters[piece];
}

KingPiece::KingPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void KingPiece::addAllPossibleMoves()
{

}

QueenPiece::QueenPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void QueenPiece::addAllPossibleMoves()
{

}

BishopPiece::BishopPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void BishopPiece::addAllPossibleMoves()
{

}

KnightPiece::KnightPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void KnightPiece::addAllPossibleMoves()
{

}

RookPiece::RookPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void RookPiece::addAllPossibleMoves()
{

}

PawnPiece::PawnPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void PawnPiece::addAllPossibleMoves()
{

}