#include "square.h"
using namespace std;

// private ctor
Square::Square(Position position, shared_ptr<ChessPiece> chessPiece): 
    observers{}, chessPiece{chessPiece}, position(position) {}

// overloaded public ctor with observer
Square::Square(Position position, shared_ptr<ChessPiece> chessPiece, shared_ptr<Observer> observer): 
    observers{}, chessPiece{chessPiece}, position(position) {
    attach(observer);
    notifyObservers();
}

void Square::setState(shared_ptr<ChessPiece> piece) {
    chessPiece = piece;
}

shared_ptr<ChessPiece> Square::getState() const {
    return chessPiece;
}

Piece Square::getPiece() const {
    if (chessPiece) {
        return chessPiece->getPiece();
    } else {
        return {PieceType::Empty, false}; // false for color if the square is empty
    }
}

Position Square::getPosition() {
    return position;
}

int Square::getNumMoves(){
    if(chessPiece){
        return chessPiece->getNumMoves();
    }
    return 0;
}

void Square::notifyObservers() {
    Square temp{getPosition(), chessPiece};
    observers[0] -> notify(temp);
}

void Square::attach(shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

Square::~Square(){}
