#ifndef LEVEL1_H
#define LEVEL1_H

#include "computerplayer.h"

class Level1 : public ComputerPlayer {
<<<<<<< HEAD
  bool isWhite;

 public:
  Level1(bool isWhite);
  std::pair<Position, Position> getMove(Board* board) override;
=======
public:
    Level1(bool isWhite);
    ~Level1() override;
    Move getMove(Board* b) override;
>>>>>>> 8d44027f0fc8cc308f1927785cb701977606f4b0
};

#endif
