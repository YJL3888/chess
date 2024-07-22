#ifndef BISHOP_H_
#define BISHOP_H_
#include "chesspiece.h"

using namespace std;

class Bishop: public ChessPiece{
    public:
        Bishop(bool);

        vector<Position> validMoves(Position, Board*) override;
        Piece getPiece() override;
        
        ~Bishop(){};
};

#endif