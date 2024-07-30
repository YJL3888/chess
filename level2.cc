#include "level2.h"

Level2::Level2(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level2 constructor
}

Level2::~Level2() {}

Move Level2::chooseMove(Board* b, vector<PotentialMoves> validMoves) {
  // vector<PotentialMoves> moves = b->allPotentialMoves(isWhite);
  // vector<PotentialMoves> allMoves =
  //     ComputerPlayer::getValidMoves(moves, b, isWhite);

  // checkmate A, -1
  Move ans = std::make_pair(std::make_pair(Z, -2), std::make_pair(Z, -2));

  // prioritize move that checks
  for (auto m : validMoves) {
    Position first = m.first;
    vector<Position> second = m.second;
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (b->inCheck(!isWhite)) {
        // if this moves checks opponent,
        // play this move
        b->reverseMove(undoMove, false);
        ans.first = first;
        ans.second = s;
        return ans;
      }
      b->reverseMove(undoMove, false);
    }
  }

  vector<PotentialMoves> movesList;

  for (auto move : validMoves) {
    PotentialMoves aMove;
    aMove.first = move.first;
    aMove.second = {};
    for (auto s : move.second) {
      if (b->getPiece(s).first != PieceType::Empty &&
          b->getPiece(s).second != isWhite) {
        // if this moves captures
        aMove.second.emplace_back(s);
      }
    }
    if (!aMove.second.empty()) {
      movesList.emplace_back(aMove);
    }
  }

  if (!movesList.empty()) {
    // if there are ways to capture, choose a random capturing move
    return ComputerPlayer::pickRandomMove(movesList);
  } else {
    // else return a random move
    return ComputerPlayer::pickRandomMove(validMoves);
  }
}
