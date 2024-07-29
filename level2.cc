#include "level2.h"

Level2::Level2(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level2 constructor
}

Level2::~Level2() {}

bool Level2::noMoves(vector<PotentialMoves> Moves) {
  for (auto m : Moves) {
    if (!m.second.empty()) {
      return false;
    }
  }
  return true;
}

Move Level2::getMove(Board* b) {
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

  Move ans = std::make_pair(std::make_pair(Z, -2), std::make_pair(Z, -2));
  // vector<PotentialMoves> moves = b->allPotentialMoves(isWhite);

  // prioritize move that checks
  for (auto m : moves) {
    Position first = m.first;
    vector<Position> second = m.second;
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (b->inCheck(!isWhite)) {
        b->reverseMove(undoMove, false);
        ans.first = first;
        ans.second = s;
        return ans;
      }
      b->reverseMove(undoMove, false);
    }
  }

  vector<PotentialMoves> movesList;

  for (auto move : allMoves) {
    PotentialMoves aMove;
    aMove.first = move.first;
    aMove.second = {};
    for (auto s : move.second) {
      if (b->getPiece(s).first != PieceType::Empty &&
          b->getPiece(s).second != isWhite) {
        aMove.second.emplace_back(s);
      }
    }
    if (!aMove.second.empty()) {
      movesList.emplace_back(aMove);
    }
  }

  if (!movesList.empty()) {
    if (noMoves(movesList)) {
      Move staleMate =
          std::make_pair(std::make_pair(Y, -1), std::make_pair(Y, -1));
      return staleMate;
    }
    int random = rand() % movesList.size();
    while (movesList.at(random).second.empty()) {
      random = rand() % movesList.size();
    }

    ans.first = movesList.at(random).first;
    ans.second = movesList.at(random).second.at(movesList.size());
    return ans;
  } else {
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
    return ans;
  }
}
