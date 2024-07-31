#ifndef GAME_H
#define GAME_H

#include <vector>
#include "board.h"
#include "player.h"
#include "computerplayer.h"
#include "humanplayer.h"

class Game {
  private:
    std::unique_ptr<Board> b;
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;
    bool isWhite;
    bool checkmate;
    bool startGame;
    float p1Score, p2Score;
    void endGame(char);
    std::unique_ptr<Player> ComputerDifficulty(int difficulty, bool isWhite);
    int totalMoves = 0;

  public:
    Game();
    virtual ~Game();
    void play();
    void undo();
    void redo();
    // void ComputerDifficulty(int difficulty, Player*& computerPlayer, bool isWhite);
};

#endif
