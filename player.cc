#include "player.h"

bool Player::isCheckMate(Board* b, bool isWhite) {
  bool opponent = !isWhite;
  vector<PotentialMoves> opponentPotentialMoves =
      b->allPotentialMoves(opponent);

  for (auto move : opponentPotentialMoves) {
    Position first = move.first;
    vector<Position> second = move.second;
    for (auto end : second) {
      Move makeMove = std::make_pair(first, end);
      Move undoMove = std::make_pair(end, first);
      b->testMove(makeMove, false);
      if (!b->inCheck(opponent)) {
        b->reverseMove(undoMove, false);
        return false;  // not in checkmate
      }
      b->reverseMove(undoMove, false);
    }
  }
  return true;
}