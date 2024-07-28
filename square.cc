#include "square.h"
using namespace std;

Square::Square() : chessPiece(nullptr) {}

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
