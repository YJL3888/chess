#ifndef LEVEL4_H
#define LEVEL4_H

#include "computerplayer.h"

class Level4 : public ComputerPlayer {
public:
    Level4(bool isWhite);
    ~Level4() override;
    Move getMove(Board* b) override;
};

#endif