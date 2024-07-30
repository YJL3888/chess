#include "level2.h"

Level2::Level2(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level2 constructor
}

Level2::~Level2() {}

Move Level2::chooseMove(Board* b, vector<PotentialMoves> validMoves) {
  // vector<PotentialMoves> moves = b->allPotentialMoves(isWhite);
  // vector<PotentialMoves> allMoves =
  //     ComputerPlayer::getValidMoves(moves, b, isWhite);

  Move check = ComputerPlayer::checkingMoves(b, isWhite);
  if (check.first.second != -2) {
    return check;
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
