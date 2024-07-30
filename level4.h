#ifndef LEVEL4_H
#define LEVEL4_H

#include "computerplayer.h"

class Level4 : public ComputerPlayer {
public:
    Level4(bool isWhite);
    ~Level4() override;
    Move chooseMove(Board* b, vector<PotentialMoves> validMoves) override;
};

#endif
