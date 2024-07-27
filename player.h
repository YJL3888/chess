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
  bool isCheckMate(Board*, bool);
  bool isStaleMate(Board*, bool);
  virtual Move getMove(Board*) = 0;  // move is a pair of positions
};

#endif
