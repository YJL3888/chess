#ifndef PAWN_H_
#define PAWN_H_
#include "chesspiece.h"

using namespace std;

class Pawn: public ChessPiece{
    private:
        // bool isFirstMove = numMoves == 0;
    public:
        Pawn(bool);

        vector<Position> validMoves(Position, Board*) override;
        Piece getPiece() override;
        
        ~Pawn(){};
};

#endif
