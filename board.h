#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include "types.h"

class Board{
  public:
    Board();
    ~Board();

    Piece getType(Position);
};


#endif
