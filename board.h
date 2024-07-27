#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <iostream>
#include "square.h"
#include "types.h"
#include "textdisplay.h"
#include "gui.h"
using namespace std;

class Board {
  vector<vector<Square>> squares;
  shared_ptr<TextDisplay> textDisplay;
  unique_ptr<GUI> gui;

 public:
  Board();
  ~Board();

  bool commandIntepreter(istream&, bool);
  Piece getPiece(Position);
  bool isFirstMove(Position);
  Move previousMove(); // need this for en passant to verfiy the previous move of the opponent's pawn
  int numMoves(Position);

  vector<PotentialMoves> allPotentialMoves(bool); // returns all the potential moves of a player

  bool inCheck(bool); // check if this colour is in check
  void testMove(Move, bool=false); // bool is whether we perform this move or not, default is false
  void reverseMove(Move, bool=false);

  friend ostream& operator<<(ostream& out, const Board& b);

};

#endif
