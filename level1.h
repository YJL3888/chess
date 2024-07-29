#ifndef LEVEL1_H
#define LEVEL1_H

#include "computerplayer.h"

class Level1 : public ComputerPlayer {
  bool isWhite;
  bool noMoves(vector<PotentialMoves>);

 public:
  Level1(bool isWhite);
  Move getMove(Board* b) override;
  ~Level1() override;
};

#endif
