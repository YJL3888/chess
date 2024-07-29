#ifndef KING_H_
#define KING_H_
#include <utility>
#include "chesspiece.h"

using namespace std;

class King: public ChessPiece {
    private:
        // bool isFirstMove = numMoves == 0;
        bool checkCastling(Board*, Position&, Position&, Position&);
    public:
        King(bool);

        vector<Position> validMoves(Position, Board*) override;
        Piece getPiece() override;

        ~King(){};
};

#endif
