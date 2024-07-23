#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include "types.h"

class HumanPlayer : public Player {
  bool isWhite;

 public:
  HumanPlayer(bool isWhite);
  ~HumanPlayer() {};
  Move getMove(Board* board) override;
  bool isValidMove(Board* board, Move move) const;
};

#endif
