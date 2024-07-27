#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "types.h"
#include "player.h"

class HumanPlayer: public Player{
  bool isWhite;

 public:
  HumanPlayer(bool isWhite);
  ~HumanPlayer() {};
  Move getMove(Board*) override;
  bool isValidMove(Board*, Move) const;
};

#endif
