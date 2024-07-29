#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(bool isWhite) : Player(isWhite) {}

ComputerPlayer::~ComputerPlayer() {}

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
  randomMove.second = Moves.at(random).second.at(Moves.size());
  return Move(randomMove.first, randomMove.second);
}
