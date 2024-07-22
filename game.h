#ifndef GAME_H
#define GAME_H

#include <vector>

#include "board.h"
#include "player.h"
class Game {
 private:
  Board* b;
  Player* p1;
  Player* p2;
  std::vector<Board*> moveHistory;
  std::vector<Board*> redoHistory;

 public:
  Game();
  void play();
  void undo();
  void redo();
}

#endif