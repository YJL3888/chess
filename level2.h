#ifndef LEVEL2_H
#define LEVEL2_H

#include "computerplayer.h"

class Level2 : public ComputerPlayer {
public:
    Level2(bool isWhite);
    std::pair<Position, Position> getMove(Board* board) override;
};

#endif
