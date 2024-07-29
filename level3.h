#ifndef LEVEL3_H
#define LEVEL3_H

#include "computerplayer.h"

class Level3 : public ComputerPlayer {
public:
    Level3(bool isWhite);
    ~Level3() override;
    Move getMove(Board* b) override;
};

#endif
