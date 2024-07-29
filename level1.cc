#include "level1.h"

Level1::Level1(bool isWhite) : ComputerPlayer(isWhite) {};

bool noMoves(vector<PotentialMoves> Moves) {
  for (auto m : Moves) {
    if (!m.second.empty()) {
      return false;
    }
  }
  return true;
}

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

  Move ans;

  if (noMoves(allMoves)) {
    Move staleMate =
        std::make_pair(std::make_pair(Y, -1), std::make_pair(Y, -1));
    return staleMate;
  }

  int random = rand() % allMoves.size();

  while (allMoves.at(random).second.empty()) {
    random = rand() % allMoves.size();
  }

  ans.first = allMoves.at(random).first;
  ans.second = allMoves.at(random).second.at(allMoves.size());
  return Move(ans.first, ans.second);
};

Level1::~Level1() {}
