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
