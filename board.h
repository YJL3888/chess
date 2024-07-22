#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "chesspiece.h"

class Board : public Observer {
 private:
  Square squares[8][8];
  std::vector<ChessPiece> whitePieces;
  std::vector<ChessPiece> blackPieces;
}

#endif