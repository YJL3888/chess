#ifndef ROOK_H_
#define ROOK_H_
#include "chesspiece.h"

using namespace std;

class Rook: public ChessPiece {
    private:
        bool isFirstMove = 1;
    public:
        Rook(bool);

        vector<Position> validMoves(Position, Board*) override;
        Piece getPiece() override;

        ~Rook(){}
};

#endif
