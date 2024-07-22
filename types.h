#ifndef TYPE_H_
#define TYPE_H_
#include <utility>
using namespace std;

enum class PieceType{
    Empty = 0,
    Pawn = 1,
    Rook = 2,
    Knight = 3,
    Bishop = 4,
    Queen = 5,
    King = 6
};

enum xlocation{
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    F = 6,
    G = 7,
    H = 8
};

typedef pair<PieceType, bool> Piece; // the type of the piece + the colour of the piece
typedef pair<xlocation, int> Position; // the 2D location to represent a position

#endif