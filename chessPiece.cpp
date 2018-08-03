#include "chessPiece.h"

ChessPiece::ChessPiece(colors color, int row, int col, pieces piece) :color(color), curPosition(row, col), possibleMoves(nullptr), piece(piece) {};
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

KingPiece::KingPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void KingPiece::addAllPossibleMoves()
{

}
void KingPiece::printPiece()
{
	if (this->getColor() == Black) cout << "BK";
	else                           cout << "WK";
}

QueenPiece::QueenPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void QueenPiece::addAllPossibleMoves()
{

}
void QueenPiece::printPiece()
{
	if (this->getColor() == Black) cout << "BQ";
	else                           cout << "WQ";
}


BishopPiece::BishopPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void BishopPiece::addAllPossibleMoves()
{

}
void BishopPiece::printPiece()
{
	if (this->getColor() == Black) cout << "BB";
	else                           cout << "WB";
}

KnightPiece::KnightPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void KnightPiece::addAllPossibleMoves()
{

}
void KnightPiece::printPiece()
{
	if (this->getColor() == Black) cout << "BH";
	else                           cout << "WH";
}

RookPiece::RookPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void RookPiece::addAllPossibleMoves()
{

}
void RookPiece::printPiece()
{
	if (this->getColor() == Black) cout << "BR";
	else					       cout << "WR";
}

PawnPiece::PawnPiece(colors color, int row, int col, pieces piece) :ChessPiece(color, row, col, piece) {};
void PawnPiece::addAllPossibleMoves()
{

}
void PawnPiece::printPiece()
{
	if (this->getColor() == Black) cout << "BP";
	else						   cout << "WP";
}