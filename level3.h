#ifndef LEVEL3_H
#define LEVEL3_H

#include "computerplayer.h"

class Level3 : public ComputerPlayer {
public:
    std::pair<Position, Position> getMove(Board* board) override;
};

#endif
