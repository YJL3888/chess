#ifndef LEVEL4_H
#define LEVEL4_H

#include "computerplayer.h"

class Level4 : public ComputerPlayer {
 public:
  Level4(bool isWhite);
  ~Level4() override;
  Move chooseMove(Board* b, std::vector<PotentialMoves> validMoves) override;
  vector<PotentialMoves> lv3list(Board* b,
                                 std::vector<PotentialMoves> validMoves);
  Move lv3Move(Board* b, std::vector<PotentialMoves> validMoves);
  vector<PotentialMoves> lv2list(Board* b,
                                 std::vector<PotentialMoves> validMoves);
  Move lv2Move(Board* b, std::vector<PotentialMoves> validMoves);
};

#endif
