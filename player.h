#include <utility>

#include "board.h"
#include "types.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
 private:
  bool isWhite;

 public:
  Player(bool isWhite);
  virtual ~Player() {};
  bool isCheckMate(Board* b, bool side);
  bool isStaleMate(Board* b, bool side);
  virtual std::pair<Position, Position> getMove(Board* b) = 0;
};

#endif
