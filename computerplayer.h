#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include "types.h"

class ComputerPlayer : public Player {
  bool isWhite;

 public:
  ComputerPlayer(bool isWhite);
  ~ComputerPlayer() {};
  Move getMove(Board* board) override;
};

#endif
