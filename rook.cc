#include "rook.h"

using namespace std;

Rook::Rook(bool colour): ChessPiece{colour}{
    piece.first = PieceType::Rook;
}

vector<Position> Rook::validMoves(Position p, Board* b){
    // Moves in any of the four vertical/horizontal directions, any distance, but cannot move past any piece that blocks its path
    vector<Position> locations;
    ChessPiece::rowCol(p, b, locations);
    return locations;
}

Piece Rook::getPiece(){
    return piece;
}
