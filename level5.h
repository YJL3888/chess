#ifndef LEVEL5_H
#define LEVEL5_H

#include "computerplayer.h"

class Level5 : public ComputerPlayer {
 public:
  Level5(bool isWhite);
  ~Level5();
  Move chooseMove(Board* b, std::vector<PotentialMoves> validMoves) override;

 private:
  int evaluateBoard(Board* b, bool isWhite);
  int minimax(Board* b, int depth, bool maximizingPlayer, bool isWhite,
              int alpha, int beta);
};

#endif
