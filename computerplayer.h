#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"
#include "types.h"

class ComputerPlayer : public Player {
  // bool isWhite;

 public:
  ComputerPlayer(bool isWhite);
  virtual ~ComputerPlayer() override;
  virtual Move getMove(Board* b) override = 0; // Pure virtual function
  PlayerType getPlayerType() const override { return PlayerType::computer; }
};

#endif
