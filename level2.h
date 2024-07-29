#ifndef LEVEL2_H
#define LEVEL2_H

#include "computerplayer.h"

class Level2 : public ComputerPlayer {
  bool isWhite;
  bool noMoves(vector<PotentialMoves> Moves);

 public:
  Level2(bool isWhite);
  ~Level2() override;
  Move getMove(Board* b) override;
};

#endif
