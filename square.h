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
    shared_ptr<ChessPiece> chessPiece;  // chess piece with Piece and other info
    Position position;                  // xy coordinate in form: pair<xlocation, int>
    vector<shared_ptr<Observer>> observers;        // list of observers attached
    Square(Position position, shared_ptr<ChessPiece>);
    void notifyObservers();
    void attach(shared_ptr<Observer>);
    
public:
    Square(Position position, shared_ptr<ChessPiece>, shared_ptr<Observer> observer);
    void setState(shared_ptr<ChessPiece> piece);    // setting chessPiece to the parameter piece
    shared_ptr<ChessPiece> getState() const;        // return the private field chessPiece
    Piece getPiece() const;     // call respective chess piece's getPiece(), return pair<PieceType, bool>
    Position getPosition();     // get the x and y coordinates in form: pair<xlocation, int>
    int getNumMoves(); // return the number of moves made
    ~Square();
};

#endif
