#include "humanplayer.h"

#include <iostream>

#include "types.h"

HumanPlayer::HumanPlayer(bool isWhite) : Player(isWhite) {};

Move HumanPlayer::getMove(Board* b) {}

bool HumanPlayer::isValidMove(Board* b, Move move) const {
  std::vector<PotentialMoves> potentialMoves = b->allPotentialMoves(isWhite);
  for (const auto& moves : potentialMoves) {
    if (moves.first == move.first) {
      for (const auto& end : moves.second) {
        if (end == move.second) {
          return true;
        }
      }
    }
  }
  return false;
}