#include "humanplayer.h"


#include <iostream>

#include "types.h"

class Board;

HumanPlayer::HumanPlayer(bool isWhite) : Player(isWhite) {};

HumanPlayer::~HumanPlayer() {}

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
      cout << "ERROR! Command should be in the format move a1 a2.\n";
      cin >> first;
      continue;
    }

    char firstLetter = toupper(first[0]);
    xlocation firstLetterxLoc = static_cast<xlocation>(firstLetter);

    char secondLetter = toupper(second[0]);
    xlocation secondLetterxLoc = static_cast<xlocation>(secondLetter);

    int firstNum = first[1] - '0';
    int secondNum = second[1] - '0';

    Position firstP = std::make_pair(firstLetterxLoc, firstNum);
    Position secondP = std::make_pair(secondLetterxLoc, secondNum);

    move = std::make_pair(firstP, secondP);

    if (isValidMove(b, move)) {
      b->testMove(move, true);
      if (b->inCheck(this->isWhite)) {
        cout << "Invalid Move, King in check!\n";
        Move revert = std::make_pair(secondP, firstP);
        b->reverseMove(revert, true);
        std::cin >> first;
        continue;
      }
      if (secondP.second == 1 || secondP.second == 8) {
        // pawn promotion
        if (b->getPiece(secondP).first == PieceType::Pawn) {
          while (cin >> first) {
            if (first == "Q" || first == "B" || first == "N" || first == "R") {
              b->promote(secondP, first[0]);
              break;
            } else {
              cout << "Invalid piece promotion, must be Queen (Q), Bishop (B), "
                      "Knight (N) or Rook (R)!\n";
            }
          }
        }
      }
      break;
    }

    std::cout << "Move is invalid, please retry!\n";
    std::cin >> second;
  }
  // check for endgame
  if (!std::cin.eof()) {
    if (b->inCheck(this->isWhite)) {
      if (isWhite) {
        std::cout << "White player is in check\n";
      } else {
        std::cout << "Black player is in check\n";
      }
      if (isCheckMate(b, this->isWhite)) {
        if (isStaleMate(b, this->isWhite)) {
          Move stalemate =
              std::make_pair(std::make_pair(Y, -1), std::make_pair(Y, -1));
          return stalemate;
        }
        Move checkmate =
            std::make_pair(std::make_pair(Z, -2), std::make_pair(Z, -2));
        return checkmate;
      }
    }
  }
  return move;
}
