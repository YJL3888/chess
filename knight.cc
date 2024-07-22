
#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(bool colour): ChessPiece{colour} {
    piece.first = PieceType::Knight;
}

Piece Knight::getPiece(){
    return piece;
}

vector<Position> Knight::validMoves(Position p, Board* b){
    // If it sits on square (x, y), it can move to square (x±2, y±1) or (x±1, y±2). Can “jump over” any piece that blocks its path.
    vector<Position> locations;
    int x = static_cast<int>(p.first);
    int y = p.second;

    bool xplus2 = x+2<=8;
    bool xminus2 = x-2>=1;
    bool yplus1 = y+1<=8;
    bool yminus1 = y-1>=1;

    bool yplus2 = y+2<=8;
    bool yminus2 = y-2>=1;
    bool xplus1 = x+1<=8;
    bool xminus1 = x-1>=1;

    Position potentialPos;
    
    if(xplus2 && yplus1){
        potentialPos.first = static_cast<xlocation>(x+2);
        potentialPos.second = y+1; 
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){ // Empty or captures the opponent
            locations.push_back(potentialPos); 
        }
    }

    if(xplus2 && yminus1){
        potentialPos.first = static_cast<xlocation>(x+2);
        potentialPos.second = y-1;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }

    if(xminus2 && yplus1){
        potentialPos.first = static_cast<xlocation>(x-2);
        potentialPos.second = y+1;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }

    if(xminus2 && yminus1){
        potentialPos.first = static_cast<xlocation>(x-2);
        potentialPos.second = y-1;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }

    if(xplus1 && yplus2){
        potentialPos.first = static_cast<xlocation>(x+1);
        potentialPos.second = y+2;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }   

    if(xplus1 && yminus2){
        potentialPos.first = static_cast<xlocation>(x+1);
        potentialPos.second = y-2;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }

    if(xminus1 && yplus2){
        potentialPos.first = static_cast<xlocation>(x-1);
        potentialPos.second = y+2;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }

    if(xminus1 && yminus2){
        potentialPos.first = static_cast<xlocation>(x-1);
        potentialPos.second = y-2;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos); 
        }
    }

    return locations;

}