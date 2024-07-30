#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(bool isWhite) : Player(isWhite) {}

ComputerPlayer::~ComputerPlayer() {}

Move ComputerPlayer::checkingMoves(Board* b, bool isWhite) {
  Move check = std::make_pair(std::make_pair(Z, -2), std::make_pair(Z, -2));
  vector<PotentialMoves> allMoves = b->allPotentialMoves(isWhite);
  for (auto move : allMoves) {
    Position first = move.first;
    vector<Position> second = move.second;
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (b->inCheck(!isWhite)) {
        b->reverseMove(undoMove, false);
        check.first = first;
        check.second = s;
        return check;
      }
      b->reverseMove(undoMove, false);
    }
  }
  return check;
}

bool ComputerPlayer::noMoves(vector<PotentialMoves> Moves) {
  for (auto m : Moves) {
    if (!m.second.empty()) {
      return false;
    }
  }
  return true;
}

Move ComputerPlayer::pickRandomMove(vector<PotentialMoves> Moves) {
  Move randomMove;
  if (ComputerPlayer::noMoves(Moves)) {
    Move staleMate =
        std::make_pair(std::make_pair(Y, -1), std::make_pair(Y, -1));
    return staleMate;
  }

  int random = rand() % Moves.size();

  while (Moves.at(random).second.empty()) {
    random = rand() % Moves.size();
  }

  randomMove.first = Moves.at(random).first;
  randomMove.second =
      Moves.at(random).second.at(rand() % Moves.at(random).second.size());
  return Move(randomMove.first, randomMove.second);
}

std::vector<PotentialMoves> ComputerPlayer::getValidMoves(
    std::vector<PotentialMoves> allMoves, Board* b, bool isWhite) {
  vector<PotentialMoves> validMoves;
  for (auto m : allMoves) {
    Position first = m.first;
    std::vector<Position> second = m.second;
    PotentialMoves currentMoves;
    currentMoves.first = first;
    currentMoves.second = {};
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (!b->inCheck(isWhite)) {
        currentMoves.second.emplace_back(s);
      }
      b->reverseMove(undoMove, false);
    }
    if (!currentMoves.second.empty()) {
      validMoves.emplace_back(currentMoves);
    }
  }
  return validMoves;
}

Move ComputerPlayer::getMove(Board* b) {
  vector<PotentialMoves> allMoves = b->allPotentialMoves(isWhite);
  // get all theoretical possible moves
  vector<PotentialMoves> validMoves =
      ComputerPlayer::getValidMoves(allMoves, b, isWhite);
  // get all moves that are valid

  // get next move depending on level, function is overriden by each level.
  Move move = chooseMove(b, validMoves);

  if (move.second.second == -1) {
    // stalemate
    return std::make_pair(std::make_pair(Y, -1), std::make_pair(Y, -1));
  }

  b->nextMove(move, true);

  if (b->inCheck(!isWhite)) {
    std::cout << (isWhite ? "White" : "Black") << " is in check" << endl;
  }

  if (isCheckMate(b, isWhite)) {
    if (isStaleMate(b, isWhite)) {
      // stalemate
      return std::make_pair(std::make_pair(Y, -1), std::make_pair(Y, -1));
    }

    // checkmate
    return std::make_pair(std::make_pair(Z, -2), std::make_pair(Z, -2));
  }

  if ((move.second.second == 8 || move.second.second == 1) &&
      b->getPiece(move.second).first == PieceType::Pawn) {
    // if piece has reached either end and it's a pawn, promotion to Queen
    b->promote(move.second, 'Q');
  }

  return move;
}
