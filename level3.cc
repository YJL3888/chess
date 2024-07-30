#include "level3.h"

Level3::Level3(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level3 constructor
}

Level3::~Level3() {}

vector<PotentialMoves> Level3::lv2list(Board* b,
                                       std::vector<PotentialMoves> validMoves) {
  // returns all moves that can either capture or check
  std::vector<PotentialMoves> lv2Moves;

  for (auto move : validMoves) {
    PotentialMoves aMove;
    aMove.first = move.first;
    aMove.second = {};
    for (auto s : move.second) {
      if (b->inCheck(!isWhite)) {
        // if this moves checks
        aMove.second.emplace_back(s);
      }
    }
    if (!aMove.second.empty()) {
      lv2Moves.emplace_back(aMove);
    }
  }

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
      lv2Moves.emplace_back(aMove);
    }
  }

  return lv2Moves;  // all checks and capturing moves in valid moves
}

Move Level3::lv2Move(Board* b, std::vector<PotentialMoves> validMoves) {
  std::vector<PotentialMoves> lv2Moves = lv2list(b, validMoves);

  if (lv2Moves.empty()) {
    return ComputerPlayer::pickRandomMove(validMoves);
  }
  return ComputerPlayer::pickRandomMove(lv2Moves);
}

Move Level3::chooseMove(Board* b, vector<PotentialMoves> validMoves) {
  // Level 3 will check for all safe moves
  // then it will check for all checking and capturing moves from safe moves
  // if it exist, it will choose random from those
  // else if it exist it will choose random from safe moves
  // else it will choose random from valid moves
  vector<PotentialMoves> opponentMoves = b->allPotentialMoves(!isWhite);
  vector<PotentialMoves> safeMoves;

  vector<Position> opponentCaptures;
  // all the positions where opponent can potential capture, TO AVOID
  for (auto opMove : opponentMoves) {
    for (auto second : opMove.second) {
      opponentCaptures.emplace_back(second);
    }
  }

  for (auto move : validMoves) {
    PotentialMoves aMove;
    aMove.first = move.first;
    aMove.second = {};
    for (auto second : move.second) {
      if (!(std::find(opponentCaptures.begin(), opponentCaptures.end(),
                      second) != opponentCaptures.end())) {
        aMove.second.emplace_back(second);
      }
    }
    if (!aMove.second.empty()) {
      safeMoves.emplace_back(aMove);
    }
  }

  // safeMoves contain all moves that will avoid captures.
  // now we prioritize check and captures int hose moves.

  std::vector<PotentialMoves> movesList = lv2list(b, safeMoves);

  if (!movesList.empty()) {
    // if there are ways to capture, choose a random capturing move
    return ComputerPlayer::pickRandomMove(movesList);
  } else if (!safeMoves.empty()) {
    // if no safe moves that captures, any safe move
    return ComputerPlayer::pickRandomMove(safeMoves);
  } else {
    // else return a random move
    return ComputerPlayer::pickRandomMove(validMoves);
  }
}
