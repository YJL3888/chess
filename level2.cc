#include "level2.h"

Level2::Level2(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level2 constructor
}

Level2::~Level2() {}

Move Level2::getMove(Board* b) {
  vector<PotentialMoves> moves = b->allPotentialMoves(isWhite);
  vector<PotentialMoves> allMoves =
      ComputerPlayer::getValidMoves(moves, b, isWhite);

  Move ans = std::make_pair(std::make_pair(Z, -2), std::make_pair(Z, -2));

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
    return ComputerPlayer::pickRandomMove(
        movesList);  // if there are moves that checks, randomly pick in those
  } else {
    return ComputerPlayer::pickRandomMove(
        allMoves);  // else return a random move
  }
}
