#include "square.h"
using namespace std;

// private ctor
Square::Square(Position position, shared_ptr<ChessPiece> chessPiece): 
    position(position), chessPiece{chessPiece}, observers() {}

// overloaded public ctor with observer
Square::Square(Position position, shared_ptr<ChessPiece> chessPiece, shared_ptr<Observer> observer): 
    position(position), chessPiece(chessPiece), observers() {
    attach(observer);
    notifyObservers();
}

void Square::setState(shared_ptr<ChessPiece>& piece) {
    // chessPiece = piece;
    if(chessPiece){
        chessPiece->incrementMoves();
    }
    chessPiece.swap(piece);
    notifyObservers();
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

void Square::minusMoves(){
    if(chessPiece){
        chessPiece->decrementMoves();
    }
}

void Square::check(){
    chessPiece.swap(tempChessPiece);
    notifyObservers();
}

void Square::undoCheck(){
    minusMoves();
    chessPiece.swap(tempChessPiece);
    notifyObservers();
}

std::vector<Position> Square::getPossibleMoves(Board* b){
    return chessPiece->validMoves(this->getPosition(), b);
}

void Square::notifyObservers() {
    Square temp{getPosition(), chessPiece};
    observers[0]->notify(temp);
}

void Square::attach(shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

Square::~Square(){}
