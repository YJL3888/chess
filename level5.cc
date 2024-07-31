#include "level5.h"

#include <algorithm>
#include <limits>

Level5::Level5(bool isWhite) : ComputerPlayer(isWhite) {}

Level5::~Level5() {}

int Level5::evaluateBoard(Board* b, bool isWhite) {
  std::vector<PotentialMoves> whiteMoves = b->allPotentialMoves(true);
  std::vector<PotentialMoves> blackMoves = b->allPotentialMoves(false);

  int score = 0;

  for (const auto& move : whiteMoves) {
    Piece piece = b->getPiece(move.first);
    if (piece.first != PieceType::Empty) {
      int pieceValue = 0;
      switch (piece.first) {
        case PieceType::Pawn:
          pieceValue = 1;
          break;
        case PieceType::Knight:
          pieceValue = 3;
          break;
        case PieceType::Bishop:
          pieceValue = 3;
          break;
        case PieceType::Rook:
          pieceValue = 5;
          break;
        case PieceType::Queen:
          pieceValue = 9;
          break;
        case PieceType::King:
          pieceValue = 1000;
          break;
        default:
          break;
      }
      score += piece.second == true ? pieceValue : -pieceValue;
    }
  }

  for (const auto& move : blackMoves) {
    Piece piece = b->getPiece(move.first);
    if (piece.first != PieceType::Empty) {
      int pieceValue = 0;
      switch (piece.first) {
        case PieceType::Pawn:
          pieceValue = 1;
          break;
        case PieceType::Knight:
          pieceValue = 3;
          break;
        case PieceType::Bishop:
          pieceValue = 3;
          break;
        case PieceType::Rook:
          pieceValue = 5;
          break;
        case PieceType::Queen:
          pieceValue = 9;
          break;
        case PieceType::King:
          pieceValue = 1000;
          break;
        default:
          break;
      }
      score += piece.second == false ? pieceValue : -pieceValue;
    }
  }

  return isWhite ? score : -score;
}

int Level5::minimax(Board* b, int depth, bool maximizingPlayer, bool isWhite,
                    int alpha, int beta) {
  if (depth == 0) {
    return evaluateBoard(b, isWhite);
  }

  if (isCheckMate(b, !maximizingPlayer)) {
    return maximizingPlayer ? -10000 : 10000;
  }

  if (isStaleMate(b, !maximizingPlayer) || twoKingsLeft(b, !maximizingPlayer)) {
    return 0;
  }

  std::vector<PotentialMoves> allMoves = b->allPotentialMoves(maximizingPlayer);
  std::vector<PotentialMoves> validMoves =
      ComputerPlayer::getValidMoves(allMoves, b, maximizingPlayer);

  if (maximizingPlayer) {
    int maxEval = std::numeric_limits<int>::min();
    for (const auto& move : validMoves) {
      for (const auto& pos : move.second) {
        Move makeMove = std::make_pair(move.first, pos);
        Move undoMove = std::make_pair(pos, move.first);
        b->testMove(makeMove, false);
        int eval = minimax(b, depth - 1, false, isWhite, alpha, beta);
        b->reverseMove(undoMove, false);
        maxEval = std::max(maxEval, eval);
        alpha = std::max(alpha, eval);
        if (beta <= alpha) {
          break;
        }
      }
    }
    return maxEval;
  } else {
    int minEval = std::numeric_limits<int>::max();
    for (const auto& move : validMoves) {
      for (const auto& pos : move.second) {
        Move makeMove = std::make_pair(move.first, pos);
        Move undoMove = std::make_pair(pos, move.first);
        b->testMove(makeMove, false);
        int eval = minimax(b, depth - 1, true, isWhite, alpha, beta);
        b->reverseMove(undoMove, false);
        minEval = std::min(minEval, eval);
        beta = std::min(beta, eval);
        if (beta <= alpha) {
          break;
        }
      }
    }
    return minEval;
  }
}

Move Level5::chooseMove(Board* b, std::vector<PotentialMoves> validMoves) {
  int bestEval = std::numeric_limits<int>::min();
  Move bestMove;

  for (const auto& move : validMoves) {
    for (const auto& pos : move.second) {
      Move makeMove = std::make_pair(move.first, pos);
      Move undoMove = std::make_pair(pos, move.first);
      b->testMove(makeMove, false);
      int eval = minimax(b, 2, false, isWhite, std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max());
      b->reverseMove(undoMove, false);
      if (eval > bestEval) {
        bestEval = eval;
        bestMove = makeMove;
      }
    }
  }
  return bestMove;
}
