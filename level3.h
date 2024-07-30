#ifndef LEVEL3_H
#define LEVEL3_H

#include "computerplayer.h"

class Level3 : public ComputerPlayer {
 public:
  Level3(bool isWhite);
  ~Level3();
  Move chooseMove(Board* b, vector<PotentialMoves> validMoves) override;
  vector<PotentialMoves> lv2list(Board* b,
                                 std::vector<PotentialMoves> validMoves);
  Move lv2Move(Board* b, std::vector<PotentialMoves> validMoves);
};

#endif
