#ifndef BOARD_H_
#define BOARD_H_
#include <vector>

#include "types.h"

class Board {
 public:
  Board();
  ~Board();

  Piece getPiece(Position);
  Move previousMove(); // need this for en passant to verfiy the previous move of the opponent's pawn
  int numMoves(Position);
};

#endif
