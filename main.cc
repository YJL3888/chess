#include <cstdlib>
#include <ctime>

#include "game.h"

int main() {
  srand(time(0));

  Game game;
  game.play();
  return 0;
}
