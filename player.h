#include <utility>

#include "board.h"
#include "types.h"

#ifndef PLAYER_H_
#define PLAYER_H_

#include "types.h"

class Player {
 protected:
  bool isWhite;

 public:
  Player(bool isWhite);
  virtual ~Player() {};
  bool isCheckMate(Board*, bool);
  bool isStaleMate(Board*, bool);
  virtual Move getMove(Board*) = 0;  // move is a pair of positions

  // need something to support: Player p1->getPlayerType() that returns PlayerType::computer or PlayerType::human
  virtual PlayerType getPlayerType() const = 0;
  bool getIsWhite() const { return isWhite; }

};

#endif
