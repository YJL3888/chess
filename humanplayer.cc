#include "humanplayer.h"

#include <iostream>

#include "types.h"

HumanPlayer::HumanPlayer(bool isWhite) : Player(isWhite) {};

Move HumanPlayer::getMove(Board* b) {
  string first;
  string second;
  Move move;
  while (cin >> first >> second) {
    if (!(first.size() == 2 && second.size() == 2) &&
        ('A' > toupper(first.at(0)) || toupper(first.at(0) > 'H')) &&
        ('A' > toupper(second.at(0)) || toupper(second.at(0) > 'H'))) {
      if (!cin) {
        return move;
      }
      cout << "ERROR! Command should be in the format move a1 a2." << "\n";
      cin >> first;
      continue;
    }
  }
}

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