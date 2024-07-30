#include "level4.h"

#include <algorithm>

Level4::Level4(bool isWhite) : ComputerPlayer(isWhite) {}

Level4::~Level4() {}

vector<PotentialMoves> Level4::lv2list(Board* b,
                                       std::vector<PotentialMoves> validMoves) {
  vector<PotentialMoves> movesList;
  for (auto move : validMoves) {
    PotentialMoves aMove;
    aMove.first = move.first;
    aMove.second = {};
    for (auto s : move.second) {
      if (b->getPiece(s).first != PieceType::Empty &&
          b->getPiece(s).second != isWhite) {
        aMove.second.emplace_back(s);
      }
    }
    if (!aMove.second.empty()) {
      movesList.emplace_back(aMove);
    }
  }
  return movesList;
}

Move Level4::lv2Move(Board* b, std::vector<PotentialMoves> validMoves) {
  Move ans;
  for (auto m : validMoves) {
    Position first = m.first;
    vector<Position> second = m.second;
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (b->inCheck(!isWhite)) {
        b->reverseMove(undoMove, false);
        ans.first = first;
        ans.second = s;
        return ans;
      }
      b->reverseMove(undoMove, false);
    }
  }

  vector<PotentialMoves> lv2 = lv2list(b, validMoves);
  if (!lv2.empty()) {
    return ComputerPlayer::pickRandomMove(lv2);
  } else {
    return ComputerPlayer::pickRandomMove(validMoves);
  }
}

vector<PotentialMoves> Level4::lv3list(Board* b,
                                       std::vector<PotentialMoves> validMoves) {
  vector<PotentialMoves> opponentMoves = b->allPotentialMoves(!isWhite);
  vector<PotentialMoves> safeMoves;
  vector<Position> opponentCaptures;

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
      if (std::find(opponentCaptures.begin(), opponentCaptures.end(), second) ==
          opponentCaptures.end()) {
        aMove.second.emplace_back(second);
      }
    }
    if (!aMove.second.empty()) {
      safeMoves.emplace_back(aMove);
    }
  }

  return lv2list(b, safeMoves);
}

Move Level4::lv3Move(Board* b, std::vector<PotentialMoves> validMoves) {
  vector<PotentialMoves> lv3 = lv3list(b, validMoves);

  if (!lv3.empty()) {
    return ComputerPlayer::pickRandomMove(lv3);
  } else {
    return lv2Move(b, validMoves);
  }
}

Move Level4::chooseMove(Board* b, vector<PotentialMoves> validMoves) {
  Move check = ComputerPlayer::checkingMoves(b, isWhite);
  if (check.first.second != -2) {
    // if check move exist, verify if it's safe.
    b->testMove(check, false);
    bool isSafe = !b->inCheck(isWhite);
    b->reverseMove(check, false);
    if (isSafe) {
      return check;
    }
  }

  vector<PotentialMoves> lv3 = lv3list(b, validMoves);
  vector<PotentialMoves> movesList = lv2list(b, lv3);

  for (auto& move : movesList) {
    auto& second = move.second;
    if (!second.empty()) {
      std::sort(second.begin(), second.end(), [b](Position a, Position bPos) {
        return b->getPiece(a).first > b->getPiece(bPos).first;
      });
    }
  }

  if (!movesList.empty()) {
    std::sort(movesList.begin(), movesList.end(),
              [b](PotentialMoves a, PotentialMoves bMove) {
                return b->getPiece(a.second[0]).first >
                       b->getPiece(bMove.second[0]).first;
              });
  }

  Move theMove;
  if (!movesList.empty()) {
    theMove.first = movesList.back().first;
    vector<Position> second = movesList.back().second;
    if (!second.empty()) {
      theMove.second = second.back();
      return theMove;
    }
  }
  return lv3Move(b, validMoves);
}
