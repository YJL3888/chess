#include "player.h"

Player::Player(bool isWhite) : isWhite(isWhite) {}

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
      bool stillInCheck = b->inCheck(opponent);
      b->reverseMove(undoMove, false);
      if (!stillInCheck) {
        return false;  // not in checkmate
      }
    }
  }
  return true;  // if all moves leads to check, checkmate!
}

bool Player::isStaleMate(Board* b, bool isWhite) {
  vector<PotentialMoves> Moves = b->allPotentialMoves(isWhite);

  for (auto move : Moves) {
    for (auto second : move.second) {
      if (!b->inCheck(isWhite) &&
          b->getPiece(second).first == PieceType::King) {
        // king should not be in check
        return false;
      }
    }
  }
  return true;  // king not in check & no legal move
}

bool Player::twoKingsLeft(Board* b, bool isWhite) {
  vector<PotentialMoves> Moves = b->allPotentialMoves(isWhite);
  vector<PotentialMoves> opponent = b->allPotentialMoves(!isWhite);
  int pieceCount = 0;
  for (auto move : Moves) {
    if (b->getPiece(move.first).first != PieceType::Empty &&
        b->getPiece(move.first).first != PieceType::King) {
      pieceCount++;
    }
  }
  for (auto move : opponent) {
    if (b->getPiece(move.first).first != PieceType::Empty &&
        b->getPiece(move.first).first != PieceType::King) {
      pieceCount++;
    }
  }

  // std::cout << "Piece count is " << pieceCount << "\n";

  if (pieceCount == 0) {
    return true;  // Only two kings are left on the board
  }
  return false;
}
