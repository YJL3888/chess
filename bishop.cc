#include "bishop.h"

using namespace std;

Bishop::Bishop(bool colour): ChessPiece{colour} {
    piece.first = PieceType::Bishop;
}

vector<Position> Bishop::validMoves(Position p, Board* b){
    // Moves in any of the four diagonal directions, any distance, but cannot move past any piece that blocks its path
    vector<Position> locations;
    ChessPiece::diagonal(p, b, locations);
    return locations;
}

Piece Bishop::getPiece(){
    return piece;
}
