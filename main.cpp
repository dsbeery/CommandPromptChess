#include <iostream>
#include <string>

using namespace std;

enum colors {Black = 0, White = 1};

const string ColorStrings[2] = {"Black","White"};

const int MAX_POSITION = 7;
const int MIN_POSITION = 0;

class Position
{
public:
    Position(int row = 0, int col = 0):row(row),col(col){}
    bool operator==(Position& otherPos)
    {
        return ((this->row == otherPos.getRow()) && (this->col == otherPos.getCol()));
    }
    void advance(int rows, int cols)
    {
        this->row += rows;
        this->col += cols;
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

class PositionNode:public Position
{
public:
    PositionNode(int row, int col):Position(row,col),Next(nullptr){};
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
    PositionNode* Next;
};

class ChessPiece
{
public:
    ChessPiece(colors color, int row, int col):color(color),curPosition(row,col),possibleMoves(nullptr){}
    ~ChessPiece()
    {
        if (nullptr != possibleMoves) delete(possibleMoves);
    }
    bool isMovePossible(Position target)
    {

    }
    virtual void addAllPossibleMoves() = 0;
private:
    const colors color;
    Position curPosition;
    Position* possibleMoves;
};

int main()
{
    Position foo(1,2);
    foo.advance(1,2);
    Position foo2(2,3);
    cout << (bool)(foo == foo2) << endl;
    cout << foo.getRow() << ' ' << foo.getCol() << endl;
    return 0;
}
