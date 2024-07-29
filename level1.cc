#include "level1.h"

Level1::Level1(bool isWhite) : ComputerPlayer(isWhite) {};
Level1::~Level1() {}

std::pair<Position, Position> Level1::getMove(Board* b) {
  vector<PotentialMoves> moves = b->allPotentialMoves(isWhite);
  vector<PotentialMoves> allMoves =
      ComputerPlayer::getValidMoves(moves, b, isWhite);

  return ComputerPlayer::pickRandomMove(allMoves);
};
