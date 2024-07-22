#include "pawn.h"
#include "board.h"
#include <vector>

using namespace std;

Pawn::Pawn(bool colour): ChessPiece{colour} {
    piece.first = PieceType::Pawn;
}

Piece Pawn::getPiece(){
    return piece;
}

vector<Position> Pawn::validMoves(Position p, Board* b){
    // Moves one square forward
    // Captures on the forward diagonals (one square)
    // A pawn, on its first move, may move either one square forward or two squares forward

    vector<Position> locations;
    int x = static_cast<int>(p.first);
    int y = p.second;
    bool colour = b->getPiece(p).second;

    Position potentialPos;

    // forward means going down for black players
    // forward means going up for white players

    if(!colour && y-1>=1){ // black
        potentialPos.first = p.first;
        potentialPos.second = y-1;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0){ // add if forward is empty
            locations.push_back(potentialPos);
            // if it's the first move, then it can move one more
            potentialPos.second = potentialPos.second-1;
            if(isFirstMove && y-2>=1 && static_cast<int>(b->getPiece(potentialPos).first) == 0){
                locations.push_back(potentialPos);
            }
        }
        // we now check the capturing move

    }

    if(colour && y+1<=8){ // white
        potentialPos.first = p.first;
        potentialPos.second = y+1;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0){ // add if forward is empty
            locations.push_back(potentialPos);
            // if it's the first move, then it can move one more
            potentialPos.second = potentialPos.second+1;
            if(isFirstMove && y+2<=8 && static_cast<int>(b->getPiece(potentialPos).first) == 0){
                locations.push_back(potentialPos);
            }
        }
    }
}