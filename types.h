#ifndef TYPE_H_
#define TYPE_H_
#include <utility>
#include <vector>
using namespace std;

enum class PieceType {
  Empty = 0,
  Pawn = 1,
  Rook = 2,
  Knight = 3,
  Bishop = 4,
  Queen = 5,
  King = 6
};

enum xlocation {
  A = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5,
  F = 6,
  G = 7,
  H = 8,
  Y = -1,  // Stalemate
  Z = -2   // Checkmate
};

enum class PlayerType {
    human,
    computer
};

typedef pair<PieceType, bool> Piece;  // the type of the piece + the colour of
                                      // the piece (0 black, 1 white)
typedef pair<xlocation, int>
    Position;  // the 2D location to represent a position
typedef pair<Position, Position>
    Move;  // Move from the first position to the second position

struct PotentialMoves {  // all the potential moves of a player
  Position first;
  vector<Position> second;
};

#endif
