#ifndef SQUARE_H_
#define SQUARE_H_

#include <memory>
#include "chesspiece.h"
#include "types.h"
#include "observer.h"
using namespace std;

class Observer;
class ChessPiece;
class Board;

class Square {
    Position position;                  // xy coordinate in form: pair<xlocation, int>
    shared_ptr<ChessPiece> chessPiece;  // chess piece with Piece and other info
    vector<shared_ptr<Observer>> observers;        // list of observers attached

    shared_ptr<ChessPiece> tempChessPiece = nullptr; // chess piece used in the check()
    Square(Position position, shared_ptr<ChessPiece>);
    void notifyObservers();
    void attach(shared_ptr<Observer>);
    
public:
    Square(Position position, shared_ptr<ChessPiece>, shared_ptr<Observer> observer);
    void setState(shared_ptr<ChessPiece>& piece);    // setting chessPiece to the parameter piece
    shared_ptr<ChessPiece> getState() const;        // return the private field chessPiece
    Piece getPiece() const;     // call respective chess piece's getPiece(), return pair<PieceType, bool>
    Position getPosition();     // get the x and y coordinates in form: pair<xlocation, int>
    int getNumMoves(); // return the number of moves made
    void minusMoves(); // reduce the number of moves
    void check(); // try a move using a test chessPiece
    void undoCheck(); // swap back to the actual chessPiece
    std::vector<Position> getPossibleMoves(Board*); // return all the available moves for a given chessPiece
    virtual ~Square();
};

#endif
