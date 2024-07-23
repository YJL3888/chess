#include "king.h"
#include "board.h"

using namespace std;

King::King(bool colour): ChessPiece{colour}{
    piece.first = PieceType::King;
}

Piece King::getPiece(){
    return piece;
} 

vector<Position> King::validMoves(Position p, Board* b){
    // Moves one square in any direction.
    // It is not legal to make any move that puts your king in check
    // Also need to check castling

    vector<Position> locations;
    int x = static_cast<int>(p.first);
    int y = p.second;
    bool colour = b->getPiece(p).second;

    Position potentialPos;

    // if(y+1 <= 8){
    //     // middle top
    //     potentialPos.first = p.first;
    //     potentialPos.second = y+1;

    //     if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){ // Empty or captures the opponent
    //         locations.push_back(potentialPos); 
    //     }
    // }

    // if(y-1 >= 1){
    //     // middle bottom
    //     potentialPos.first = p.first;
    //     potentialPos.second = y-1;

    //     if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){ // Empty or captures the opponent
    //         locations.push_back(potentialPos); 
    //     }
    // }

    // if(x+1 <= 8){
    //     // top right
    //     if(y+1<=8){
    //         potentialPos.first = static_cast<xlocation>(x+1);
    //         potentialPos.second = y+1;
    //         if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){ // Empty or captures the opponent
    //             locations.push_back(potentialPos); 
    //         }
    //     }
    //     // bottom right
    //     if(y-1>=1){

    //     }

    //     // middle right AIYA this is driving me crazy

    // }

    // if(x-1 >= 1){
    //     // top left
    //     if(y+1 <= 8){

    //     }
    //     // bottom right
    //     if(y-1 >= 1){

    //     }

    //     // middle right 

    // }

    return locations;

}
