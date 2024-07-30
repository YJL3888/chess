#include "level3.h"

Level3::Level3(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level3 constructor
}

Level3::~Level3() {}

Move Level3::chooseMove(Board* b, vector<PotentialMoves> validMoves) {
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

  // prioritize check
  Move ans;
  for (auto m : safeMoves) {
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

  // prioritze captures, at random
  vector<PotentialMoves> movesList;
  for (auto move : safeMoves) {
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
  } else if (!safeMoves.empty()) {
    // if no safe moves that captures, any safe move
    return ComputerPlayer::pickRandomMove(safeMoves);
  } else {
    // else return a random move
    return ComputerPlayer::pickRandomMove(validMoves);
  }
}
