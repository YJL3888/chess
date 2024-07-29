#include "level1.h"

Level1::Level1(bool isWhite) : ComputerPlayer(isWhite) {};
Level1::~Level1() {}

std::pair<Position, Position> Level1::getMove(Board* b) {
  vector<PotentialMoves> moves = b->allPotentialMoves(isWhite);
  vector<PotentialMoves> allMoves;
  for (auto m : moves) {
    Position first = m.first;
    std::vector<Position> second = m.second;
    PotentialMoves currentMoves;
    currentMoves.first = first;
    currentMoves.second = {};
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (!b->inCheck(isWhite)) {
        currentMoves.second.emplace_back(s);
      }
      b->reverseMove(undoMove, false);
    }
    if (!currentMoves.second.empty()) {
      allMoves.emplace_back(currentMoves);
    }
  }

  return ComputerPlayer::pickRandomMove(allMoves);
};
