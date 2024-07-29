#ifndef LEVEL1_H
#define LEVEL1_H

#include "computerplayer.h"

class Level1 : public ComputerPlayer {
  bool isWhite;

 public:
  Level1(bool isWhite);
  ~Level1() override;
  Move getMove(Board* b) override;
};

#endif
