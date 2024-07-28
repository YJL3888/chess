#ifndef LEVEL1_H
#define LEVEL1_H

#include "computerplayer.h"

class Level1 : public ComputerPlayer {
public:
    std::pair<Position, Position> getMove(Board* board) override;
};

#endif
