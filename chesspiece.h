#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <vector>
#include "types.h"

using namespace std;

class Board;

class ChessPiece{
  protected:
    Piece piece;
    int numMoves = 0; // need this for en Passant and other operations
  public:
    ChessPiece(bool colour);
    
    virtual vector<Position> validMoves(Position, Board*) = 0;
    virtual Piece getPiece() = 0;

    void diagonal(Position, Board*, vector<Position>&);
    void rowCol(Position, Board*, vector<Position>&);

    virtual ~ChessPiece(){};

    int getNumMoves();
    void incrementMoves();
};

#endif