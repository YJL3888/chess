#ifndef LEVEL1_H
#define LEVEL1_H

#include "computerplayer.h"

class Level1 : public ComputerPlayer {
  // bool isWhite;

 public:
  Level1(bool isWhite);
  Move chooseMove(Board* b, vector<PotentialMoves> validMoves) override;
  ~Level1();
};

#endif
