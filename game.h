#ifndef GAME_H
#define GAME_H

#include <vector>
#include "board.h"
#include "player.h"
#include "computerplayer.h"
#include "humanplayer.h"

class Game {
  private:
    Board* b;
    Player* p1;
    Player* p2;
    bool isWhite;
    bool checkmate;
    bool startGame;
    float p1Score, p2Score;
    void endGame(char);
    Player* ComputerDifficulty(int difficulty, bool isWhite);

  public:
    Game();
    virtual ~Game();
    void play();
    void undo();
    void redo();
    // void ComputerDifficulty(int difficulty, Player*& computerPlayer, bool isWhite);
};

#endif
