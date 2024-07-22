#ifndef QUEEN_H_
#define QUEEN_H_
#include "chesspiece.h"

using namespace std;

class Queen: public ChessPiece{
  public:
    Queen(bool);

    vector<Position> validMoves(Position, Board*) override;
    Piece getPiece() override;

    ~Queen(){}
};

#endif
