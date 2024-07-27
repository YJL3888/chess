#include "chesspiece.h"
#include "board.h"

ChessPiece::ChessPiece(bool colour){
    piece.second = colour;
};

void ChessPiece::diagonal(Position p, Board* b, vector<Position>& locations){
    int x = static_cast<int>(p.first);
    int y = p.second;
    Position potentialPos;
    diagonalHelper(b, y-1, x-1, potentialPos, p, locations, false, false);
    diagonalHelper(b, y-1, x+1, potentialPos, p, locations, false, true);
    diagonalHelper(b, y+1, x-1, potentialPos, p, locations, true, false);
    diagonalHelper(b, y+1, x+1, potentialPos, p, locations, true, true);
}


void ChessPiece::rowCol(Position p, Board* b, vector<Position>& locations){
    int x = static_cast<int>(p.first);
    int y = p.second;
    Position potentialPos;
    rowColHelper(b, y-1, false, x, potentialPos, p, locations, false);
    rowColHelper(b, y+1, false, x, potentialPos, p, locations, true);
    rowColHelper(b, x-1, true, y, potentialPos, p, locations, false);
    rowColHelper(b, x+1, true, y, potentialPos, p, locations, true);
}

int ChessPiece::getNumMoves(){
    return numMoves;
}

void ChessPiece::incrementMoves(){
    numMoves++;
}

void ChessPiece::decrementMoves(){
    numMoves--;
}

void ChessPiece::diagonalHelper(Board* b, int row, int col, Position& potentialPos, Position& p, vector<Position>& locations, bool increaseRow, bool increaseCol){
    int r = row;
    int c = col;
    while(r <= 8 && c <= 8 && r >= 1 && c >= 1){
        potentialPos.first = static_cast<xlocation>(c);
        potentialPos.second = r;
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0){
            locations.push_back(potentialPos);
        }else if(b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos);
            break;
        }else{
            break;
        }
        if(increaseRow){
            ++r;
        }else{
            --r;
        }
        if(increaseCol){
            ++c;
        }else{
            --c;
        }

    }
}

void ChessPiece::rowColHelper(Board* b, int bound, bool changeFirst, int position1, Position& potentialPos, Position& p, vector<Position>& locations, bool increase){
    int i = bound;
    while(i >=  1 && i <= 8){
        if(changeFirst){    
            potentialPos.first = static_cast<xlocation>(i);
            potentialPos.second = position1;
        }else{
            potentialPos.first = static_cast<xlocation>(position1);
            potentialPos.second = i;
        }
        if(static_cast<int>(b->getPiece(potentialPos).first) == 0){
            locations.push_back(potentialPos);
        }else if(b->getPiece(p).second != b->getPiece(potentialPos).second){
            locations.push_back(potentialPos);
            break;
        }else{
            break;
        }
        if(increase){
            ++i;
        }else{
            --i;
        }
    }
}
