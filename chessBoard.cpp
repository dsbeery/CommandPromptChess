#include "chessBoard.h"


ChessBoard::ChessBoard()
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

	if (curTurn.getColor() != White) cout << "Initial color mismatch" << endl;
}

void ChessBoard::printBoard()
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

bool ChessBoard::isCheck(Color color)
{
	Position kingPosition = (color == Color(Black)) ? BlackKing : WhiteKing;
	return false;
}

bool ChessBoard::isCheckMate(Color color)
{
	Position kingPosition = (color == Color(Black)) ? BlackKing : WhiteKing;
	return false;
}

bool ChessBoard::isEmpty(Position * choice)
{ 
	return (Board[choice->getRow()][choice->getCol()] == nullptr);
}

bool ChessBoard::isOppositeColor(Position * choice)
{
	return (Board[choice->getRow()][choice->getCol()]->getColor() != curTurn);
}

bool ChessBoard::isLegalPiece(Position * pickUp)
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

Position * ChessBoard::pickUpPiece()
{
	Position * choice = new Position;
	bool userChoseLegalPiece = false;
	cout << "Next move: " << ColorStrings[curTurn.getColor()] << endl;
	while (!userChoseLegalPiece)
	{
		while (!choice->getFromUser()) cout << "Try again:" << endl;
		if (!isLegalPiece(choice)) cout << "Try again:" << endl;
		else userChoseLegalPiece = true;
	}
	return choice;
}

void ChessBoard::createNewPiece(Position * target)
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
			Board[target->getRow()][target->getCol()] = new QueenPiece(curTurn.getColor(), target->getRow(), target->getCol());
			userEntryCorrect = true;
			break;
		case 'R':
			Board[target->getRow()][target->getCol()] = new RookPiece(curTurn.getColor(), target->getRow(), target->getCol());
			userEntryCorrect = true;
			break;
		case 'B':
			Board[target->getRow()][target->getCol()] = new BishopPiece(curTurn.getColor(), target->getRow(), target->getCol());
			userEntryCorrect = true;
			break;
		case 'K':
			Board[target->getRow()][target->getCol()] = new KnightPiece(curTurn.getColor(), target->getRow(), target->getCol());
			userEntryCorrect = true;
			break;
		default:
			cout << "Input must be Q, R, B or K." << endl;
		}
	}
}

bool ChessBoard::movePiece(Position * origin)
{
	Position target_pos;
	Position * target = &target_pos;
	ChessPiece * movingPiece = Board[origin->getRow()][origin->getCol()];
	bool userChoseLegalTarget = false;
	Color opponent = (curTurn == Color(Black)) ? White : Black;
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
	if (movingPiece->getPiece() == Pawn && ((movingPiece->getColor() == Color(Black) && target->getRow() == 0) ||
		(movingPiece->getColor() == Color(White) && target->getRow() == 7)))
	{
		delete(movingPiece);
		createNewPiece(target);
	}
	else if (movingPiece->getPiece() == King)
	{
		if (curTurn == Color(Black)) BlackKing = *target;
		else                  WhiteKing = *target;
	}

	if (isCheck(opponent))
	{
		if (isCheckMate(opponent))
		{
			cout << "Checkmate!!! " << ColorStrings[curTurn.getColor()] << " wins!!!" << endl;
			return true;
		}
		cout << "Check!" << endl;
	}

	return false;
}

bool ChessBoard::nextTurn()
{
	Position * pieceToMove = pickUpPiece();
	colors opponent = (curTurn == Color(Black)) ? White : Black;
	movePiece(pieceToMove);
	if (isCheck(opponent))
	{
		if (isCheckMate(opponent))
		{
			cout << "Checkmate!!! " << ColorStrings[curTurn.getColor()] << " wins!!!" << endl;
			return true;
		}
		cout << "Check!" << endl;
	}
	return false;
}