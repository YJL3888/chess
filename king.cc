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
    // bool colour = b->getPiece(p).second;

    Position potentialPos;

    for(int i = -1;  i <= 1; i++){
        for(int j = -1; j <= 1; j++){
        if(i != 0 || j != 0){
                potentialPos.first = static_cast<xlocation>(x+i);
				potentialPos.second = y+j;
                if(static_cast<int>(potentialPos.first) >= 1 && static_cast<int>(potentialPos.first) <= 8 && potentialPos.second >= 1 && potentialPos.second <= 8){
                    if(static_cast<int>(b->getPiece(potentialPos).first) == 0 || b->getPiece(p).second != b->getPiece(potentialPos).second){ // Empty or captures the opponent
                        locations.push_back(potentialPos); 
                    }
				}
            }
        }
    }

    // castling 
    Position p1;
    Position p2;
    Position p3;

	p1.second = y;
	p2.second = y;
	p3.second = y;

    potentialPos.first = static_cast<xlocation>(x+1);
    potentialPos.second = y;
	
    p1.first = static_cast<xlocation>(7);
    p2.first = static_cast<xlocation>(8);
    if(isFirstMove && b->isFirstMove(p2) && x == 5 && static_cast<int>(b->getPiece(potentialPos).first) == 0 && static_cast<int>(b->getPiece(p1).first) == 0 && static_cast<int>(b->getPiece(p2).first) == 2){
        bool check =checkCastling(b, p1, potentialPos, p);
        if(check){
            locations.emplace_back(p1);
        }
    }

    p1.first = static_cast<xlocation>(1);
    p2.first = static_cast<xlocation>(2);
    p3.first = static_cast<xlocation>(3);

    potentialPos.first = static_cast<xlocation>(x-1);
    potentialPos.second = y;

    if(isFirstMove && b->isFirstMove(p1) && x == 5 && static_cast<int>(b->getPiece(potentialPos).first) == 0 && 
        static_cast<int>(b->getPiece(p3).first) == 0 && static_cast<int>(b->getPiece(p2).first) == 0 && static_cast<int>(b->getPiece(p1).first) == 2){
        bool check = checkCastling(b, p2, potentialPos, p);
        if(check){
            locations.emplace_back(p3);
        }
    }

    return locations;

}

bool King::checkCastling(Board* b, Position& p1, Position& potentialPos, Position& p){
    bool check1;
    bool check2;
    bool check3;
    bool side = piece.second;
    check1 = b->inCheck(side);
    b->testMove({p, potentialPos});
    check2 = b->inCheck(side);
    b->reverseMove({potentialPos, p});
    b->testMove({p, p1});
    check3 = b->inCheck(side);
    b->reverseMove({p1, p});
    return !check1 && !check2 && !check3;
}
