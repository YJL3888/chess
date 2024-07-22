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
    // Also need to take into account of possible moves of en passant

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
        if(x+1<=8){
            // check for en passant
            potentialPos.first = static_cast<xlocation>(x+1);
            potentialPos.second = y; // this is the position of the opponent's pawn
            if(y-2 > 1 && b->numMoves(potentialPos) == 1 && static_cast<int>(b->getPiece(potentialPos).first) == 1 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                // in range + correct number of moves (1) + it's the opponent's pawn
                Move predictedmove = make_pair(make_pair(potentialPos.first, y-2), make_pair(potentialPos.first, y));
                if(predictedmove == b->previousMove()){
                    potentialPos.second = y-1;
                    locations.push_back(potentialPos);
                }
            }
            // normal capture
            potentialPos.second = y-1;
            if(static_cast<int>(b->getPiece(potentialPos).first) == 0 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                locations.push_back(potentialPos);
            }
            
        }
        if(x-1>=1){
            // check for en passant
            potentialPos.first = static_cast<xlocation>(x-1);
            potentialPos.second = y; // this is the position of the opponent's pawn
            if(y-2 > 1 && b->numMoves(potentialPos) == 1 && static_cast<int>(b->getPiece(potentialPos).first) == 1 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                // in range + correct number of moves (1) + it's the opponent's pawn
                Move predictedmove = make_pair(make_pair(potentialPos.first, y-2), make_pair(potentialPos.first, y));
                if(predictedmove == b->previousMove()){
                    potentialPos.second = y-1;
                    locations.push_back(potentialPos);
                }
            }
            // normal capture
            potentialPos.second = y-1;
            if(static_cast<int>(b->getPiece(potentialPos).first) == 0 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                locations.push_back(potentialPos);
            }
        }
    }

    if(colour && y+1<=8){ // white
        potentialPos.first = p.first;
        potentialPos.second = y+1; // this is the position of the opponent's pawn
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0){ // add if forward is empty
            locations.push_back(potentialPos);
            // if it's the first move, then it can move one more
            potentialPos.second = potentialPos.second+1;
            if(isFirstMove && y+2<=8 && static_cast<int>(b->getPiece(potentialPos).first) == 0){
                locations.push_back(potentialPos);
            }
        }
        // we now check the capturing move
        if(x+1<=8){
            // check for en passant
            potentialPos.first = static_cast<xlocation>(x+1);
            potentialPos.second = y; // this is the position of the opponent's pawn
            if(y+2 < 8 && b->numMoves(potentialPos) == 1 && static_cast<int>(b->getPiece(potentialPos).first) == 1 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                // in range + correct number of moves (1) + it's the opponent's pawn
                Move predictedmove = make_pair(make_pair(potentialPos.first, y+2), make_pair(potentialPos.first, y));
                if(predictedmove == b->previousMove()){
                    potentialPos.second = y+1;
                    locations.push_back(potentialPos);
                }
            }
            // normal capture
            potentialPos.second = y+1;
            if(static_cast<int>(b->getPiece(potentialPos).first) == 0 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                locations.push_back(potentialPos);
            }
        }
        if(x-1>=1){
            // check for en passant
            potentialPos.first = static_cast<xlocation>(x-1);
            potentialPos.second = y; // this is the position of the opponent's pawn
            if(y+2 < 8 && b->numMoves(potentialPos) == 1 && static_cast<int>(b->getPiece(potentialPos).first) == 1 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                // in range + correct number of moves (1) + it's the opponent's pawn
                Move predictedmove = make_pair(make_pair(potentialPos.first, y+2), make_pair(potentialPos.first, y));
                if(predictedmove == b->previousMove()){
                    potentialPos.second = y+1;
                    locations.push_back(potentialPos);
                }
            }
            // normal capture
            potentialPos.second = y+1;
            if(static_cast<int>(b->getPiece(potentialPos).first) == 0 && b->getPiece(p).second != b->getPiece(potentialPos).second){
                locations.push_back(potentialPos);
            }
        }
    }
}