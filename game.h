#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Board.h"
#include "Player.h"
class Game {
 private:
  board* b;
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