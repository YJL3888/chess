#include "level4.h"

Level4::Level4(bool isWhite) : ComputerPlayer(isWhite) {
  // Implementation of Level4 constructor
}

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
        // if this moves captures
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
      if (!(std::find(opponentCaptures.begin(), opponentCaptures.end(),
                      second) != opponentCaptures.end())) {
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
  vector<PotentialMoves> allMoves = b->allPotentialMoves(isWhite);
  for (auto m : allMoves) {
    Position first = m.first;
    vector<Position> second = m.second;
    for (auto s : second) {
      Move makeMove = std::make_pair(first, s);
      Move undoMove = std::make_pair(s, first);
      b->testMove(makeMove, false);
      if (b->inCheck(!isWhite)) {
        // if this moves checks opponent,
        // play this move
        Move ans;
        b->reverseMove(undoMove, false);
        ans.first = first;
        ans.second = s;
        return ans;
      }
      b->reverseMove(undoMove, false);
    }
  }

  vector<PotentialMoves> lv3 = lv3list(b, validMoves);
  vector<PotentialMoves> movesList = lv2list(b, lv3);
  for (auto move : movesList) {
    std::vector<Position> second = move.second;
    for (int i = 0; i < movesList.size() - 1; i++) {
      for (int j = 0; j < movesList.size() - i - 1; j++) {
        if (b->getPiece(second[j]).first > b->getPiece(second[j + 1]).first) {
          std::swap(second[j], second[j + 1]);
        }
      }
    }
  }
  for (int i = 0; i < movesList.size() - 1; i++) {
    for (int j = 0; j < movesList.size() - i - 1; j++) {
      if (b->getPiece(movesList[j].second[0]).first >
          b->getPiece(movesList[j + 1].second[0]).first) {
        std::swap(movesList[j], movesList[j + 1]);
      }
    }
  }

  Move theMove;
  if (!movesList.empty()) {
    theMove.first = movesList[movesList.size() - 1].first;
    vector<Position> second = movesList[movesList.size() - 1].second;
    theMove.second = second[second.size() - 1];
    return theMove;
  } else {
    return lv3Move(b, validMoves);
  }
}

// Move Level4::chooseMove(Board* b, vector<PotentialMoves> validMoves) {
//   vector<PotentialMoves> opponentMoves = b->allPotentialMoves(!isWhite);
//   vector<PotentialMoves> safeMoves;
//   vector<Position> opponentCaptures;
//   // all the positions where opponent can potential capture, TO AVOID
//   for (auto opMove : opponentMoves) {
//     for (auto second : opMove.second) {
//       opponentCaptures.emplace_back(second);
//     }
//   }

//   for (auto move : validMoves) {
//     PotentialMoves aMove;
//     aMove.first = move.first;
//     aMove.second = {};
//     for (auto second : move.second) {
//       if (!(std::find(opponentCaptures.begin(), opponentCaptures.end(),
//                       second) != opponentCaptures.end())) {
//         aMove.second.emplace_back(second);
//       }
//     }
//     if (!aMove.second.empty()) {
//       safeMoves.emplace_back(aMove);
//     }
//   }
//   Move check;
//   for (auto move : safeMoves) {
//     Position first = move.first;
//     vector<Position> second = move.second;
//     for (auto s : second) {
//       Move makeMove = std::make_pair(first, s);
//       Move undoMove = std::make_pair(s, first);
//       b->testMove(makeMove, false);
//       if (b->inCheck(!isWhite)) {
//         b->reverseMove(undoMove, false);
//         check.first = first;
//         check.second = s;
//         return check;
//       }
//       b->reverseMove(undoMove, false);
//     }
//   }
//   // move if there is a safe move to check.

//   vector<PotentialMoves> movesList;
//   // Lv4 -> lv2
//   for (auto move : validMoves) {
//     PotentialMoves aMove;
//     aMove.first = move.first;
//     aMove.second = {};
//     for (auto s : move.second) {
//       if (b->getPiece(s).first != PieceType::Empty &&
//           b->getPiece(s).second != isWhite) {
//         // if this moves captures
//         aMove.second.emplace_back(s);
//       }
//     }
//     if (!aMove.second.empty()) {
//       movesList.emplace_back(aMove);
//     }
//   }

//   for (auto move : movesList) {
//     std::vector<Position> second = move.second;
//     for (int i = 0; i < movesList.size() - 1; i++) {
//       for (int j = 0; j < movesList.size() - i - 1; j++) {
//         if (b->getPiece(second[j]).first > b->getPiece(second[j + 1]).first)
//         {
//           std::swap(second[j], second[j + 1]);
//         }
//       }
//     }
//   }
//   for (int i = 0; i < movesList.size() - 1; i++) {
//     for (int j = 0; j < movesList.size() - i - 1; j++) {
//       if (b->getPiece(movesList[j].second[0]).first >
//           b->getPiece(movesList[j + 1].second[0]).first) {
//         std::swap(movesList[j], movesList[j + 1]);
//       }
//     }
//   }

//   Move theMove;

//   // if we can avoid capture and capture
//   if (!movesList.empty()) {
//     theMove.first = movesList[movesList.size() - 1].first;
//     vector<Position> second = movesList[movesList.size() - 1].second;
//     theMove.second = second[second.size() - 1];
//     return theMove;
//   } else {
//     // if can't avoid capture, capture the most valuable piece
//     // validmoves -> lv4->lv2

//     vector<PotentialMoves> capturesList;
//     for (auto move : validMoves) {
//       PotentialMoves aMove;
//       aMove.first = move.first;
//       aMove.second = {};
//       for (auto s : move.second) {
//         if (b->getPiece(s).first != PieceType::Empty &&
//             b->getPiece(s).second != isWhite) {
//           // if this moves captures
//           aMove.second.emplace_back(s);
//         }
//       }
//       if (!aMove.second.empty()) {
//         capturesList.emplace_back(aMove);
//       }
//     }

//     for (auto move : capturesList) {
//       std::vector<Position> second = move.second;
//       for (int i = 0; i < movesList.size() - 1; i++) {
//         for (int j = 0; j < movesList.size() - i - 1; j++) {
//           if (b->getPiece(second[j]).first > b->getPiece(second[j +
//           1]).first) {
//             std::swap(second[j], second[j + 1]);
//           }
//         }
//       }
//     }
//     for (int i = 0; i < capturesList.size() - 1; i++) {
//       for (int j = 0; j < capturesList.size() - i - 1; j++) {
//         if (b->getPiece(capturesList[j].second[0]).first >
//             b->getPiece(capturesList[j + 1].second[0]).first) {
//           std::swap(capturesList[j], capturesList[j + 1]);
//         }
//       }
//     }

//     if (!capturesList.empty()) {
//       theMove.first = capturesList[capturesList.size() - 1].first;
//       vector<Position> second = capturesList[capturesList.size() - 1].second;
//       theMove.second = second[second.size() - 1];
//     } else {
//       if (!safeMoves.empty()) {
//         return ComputerPlayer::pickRandomMove(safeMoves);
//       } else {
//         return ComputerPlayer::pickRandomMove(validMoves);
//       }
//     }
//   }
// }