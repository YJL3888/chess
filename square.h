#ifndef SQUARE_H_
#define SQUARE_H_

#include <memory>
#include "chesspiece.h"
#include "types.h"
using namespace std;

class Square {
    shared_ptr<ChessPiece> chessPiece;
    Position position;

public:
    Square();
    void setState(shared_ptr<ChessPiece> piece);
    shared_ptr<ChessPiece> getState() const;
    Piece getPiece() const;
    Position getPosition();
};

#endif
