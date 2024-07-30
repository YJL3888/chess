#ifndef LEVEL2_H
#define LEVEL2_H

#include "computerplayer.h"

class Level2 : public ComputerPlayer {
  // bool isWhite;

 public:
  Level2(bool isWhite);
  ~Level2();
  Move chooseMove(Board* b, vector<PotentialMoves> validMoves) override;
};

#endif
