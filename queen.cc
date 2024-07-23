#include "queen.h"

using namespace std;

Queen::Queen(bool colour): ChessPiece(colour){
    piece.first = PieceType::Queen;
}

vector<Position> Queen::validMoves(Position p, Board* b){
    vector<Position> locations;
    // Moves in any of the eight possible directions, any distance, but cannot move past any piece that blocks its path.
    ChessPiece::diagonal(p, b, locations);
    ChessPiece::rowCol(p, b, locations);
    return locations;
}

Piece Queen::getPiece(){
    return piece;
}
