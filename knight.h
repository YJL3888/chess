#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "chesspiece.h"

using namespace std;

class Knight: public ChessPiece {
  public:
    Knight(bool);

    vector<Position> validMoves(Position, Board*) override;
    Piece getType() override;

    ~Knight(){};
};

#endif
