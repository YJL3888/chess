#include "level1.h"

Level1::Level1(bool isWhite) : ComputerPlayer(isWhite) {};
Level1::~Level1() {}

std::pair<Position, Position> Level1::chooseMove(
    Board* b, vector<PotentialMoves> validMoves) {
  // level 1: choose a random move that is valid.
  return ComputerPlayer::pickRandomMove(validMoves);
};
