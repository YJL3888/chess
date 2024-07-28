#ifndef LEVEL4_H
#define LEVEL4_H

#include "computerplayer.h"

class Level4 : public ComputerPlayer {
public:
    std::pair<Position, Position> getMove(Board* board) override;
};

#endif // LEVEL4_H
