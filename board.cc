#include "board.h"
#include "chesspiece.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "square.h"
#include "textdisplay.h"
#include "gui.h"
#include <string>
#include <memory>
#include "iostream"
#include "types.h"
using namespace std;

/*
Board constructor - sets up the board with squares and textdisplay.
TODO - Not tested yet.
*/
Board::Board(): squares{}, textDisplay {make_shared<TextDisplay>()} { // later add: gui{new GUI()}
    for (int i = 1; i <= 8; ++i) {
        squares.push_back({
            Square(Position(A,i), nullptr, textDisplay),
            Square(Position(B,i), nullptr, textDisplay),
            Square(Position(C,i), nullptr, textDisplay),
            Square(Position(D,i), nullptr, textDisplay),
            Square(Position(E,i), nullptr, textDisplay),
            Square(Position(F,i), nullptr, textDisplay),
            Square(Position(G,i), nullptr, textDisplay),
            Square(Position(H,i), nullptr, textDisplay),
        });
    }
    // add this for GUI: gui->update(textDisplay);
}

Board::~Board(){
    // delete gui;
    // delete td;
}

/*
operator<< overload, friend in Board Class.
Outputs the board. 
TODO - will need the textDisplay set up.
TODO - Not tested yet.
*/
ostream& operator<<(std::ostream& out, const Board& b){
    out << *(b.textDisplay);
    return out;
    // b.gui->update(b.textDisplay);
    // return out << *b.textDisplay;
}

/*
TODO - not tested yet
Return type: bool = true if white goes first, otherwise black goes first.
Parameters: istream& in, bool printBoard (determines whether or not to print after modification)
--------------------------------------------------------------------------------------------------
This method read input from istream, process them to set up board, 
including adding piece ("+ K e1"), removing piece ("- e1"), and setup done ("done") 
to check validity.
*/
bool Board::commandIntepreter(istream& in, bool printBoard) {
    string arg1, arg2, arg3;
    bool white = true;
    bool valid = false;
    do {
        in >> arg1;
        if (in.eof()) break;

        if (arg1 == "+") { // adding a piece: + K e1
            in >> arg2 >> arg3;
            if (arg2.size() == 1 && 
                (toupper(arg2[0]) == 'P' || toupper(arg2[0]) == 'B' || 
                 toupper(arg2[0]) == 'N' || toupper(arg2[0]) == 'R' || 
                 toupper(arg2[0]) == 'Q' || toupper(arg2[0]) == 'K') && 
                 arg3.size() == 2 && 
                 'A' <= toupper(arg3[0]) && toupper(arg3[0]) <= 'H' && 
                 '1' <= arg3[1] && arg3[1] <= '8') { // if condition checking for valid adding piece command
                
                shared_ptr<ChessPiece> piece;
                switch (arg2[0]) {
                    case 'P': piece = std::make_shared<Pawn>(true); break;
                    case 'R': piece = std::make_shared<Rook>(true); break;
                    case 'N': piece = std::make_shared<Knight>(true); break;
                    case 'B': piece = std::make_shared<Bishop>(true); break;
                    case 'Q': piece = std::make_shared<Queen>(true); break;
                    case 'K': piece = std::make_shared<King>(true); break;

                    case 'p': piece = std::make_shared<Pawn>(false); break;
                    case 'r': piece = std::make_shared<Rook>(false); break;
                    case 'n': piece = std::make_shared<Knight>(false); break;
                    case 'b': piece = std::make_shared<Bishop>(false); break;
                    case 'q': piece = std::make_shared<Queen>(false); break;
                    case 'k': piece = std::make_shared<King>(false); break;
                }
                squares[arg3[1] - '1'][toupper(arg3[0]) - 'A'].setState(piece);
                if (printBoard) {
                    cout << *this;
                }
            } else {
                cout << "Invalid input, should follow format + K e1." << endl;
            }
        } 

        else if (arg1 == "-") { // removing a piece: - e1
            in >> arg2;
            if (arg2.size() == 2 && 
                'A' <= toupper(arg2[0]) && toupper(arg2[0]) < 'H' && 
                '1' <= arg2[1] && arg2[1] <= '8') {

                if (squares[arg2[1] - '1'][toupper(arg2[0]) - 'A'].getState() != nullptr) {
                    std::shared_ptr<ChessPiece> nullchess(nullptr);
                    squares[arg2[1] - '1'][toupper(arg2[0]) - 'A'].setState(nullchess);
                    if(printBoard){
                        std::cout << *this;
                    }
                }
            } else {
                cout << "Invalid input, should follow format - e1." << endl;
            }
        }

        else if (arg1 == "p") { // set starting player
            in >> arg2;
            if (arg2 == "white") { white = true; } 
            else if (arg2 == "black") { white = false; }
            else { cout << "Invalid input, only accept either \"= white\" or \"= black\"." <<endl; }
        }

        else if(arg1 == "done") { // end setup phase - check if setup is valid
            valid = true;
            
            // rule NO.1: all pawns cannot be in first and last rows.
            for (int i = 0; i < 8; i++) {
                if (squares[0][i].getPiece().first == PieceType::Pawn || 
                    squares[7][i].getPiece().first == PieceType::Pawn) {
                    std::cout << "Invalid setup, pawns cannot be in the first and last rows" << endl;
                    valid = false;
                }
            }

            // rule NO.2: there can only be 1 king for each player. 
            int numWKing = 0;
            int numBKing = 0;
            for (const auto& row : squares) {
                for (const auto& square : row) {
                    auto pieceType = square.getPiece();
                    if (pieceType.first == PieceType::King) {
                        if (pieceType.second == 1) numWKing++;
                        else if (pieceType.second == 0) numBKing++;
                    }
                }
            }
            if (numWKing != 1 || numBKing != 1) {
                cout << "Invalid setup, there must be 1 king for each side" << endl;
                valid = false;
            }

            // rule NO.3: either king cannot be in check.
            if (inCheck(0) || inCheck(1)) {
                cout << "Invalid setup, a king is in check" << endl;
                valid = false;
            }
        } else { cout << "Invalid command" << endl; }
    } while (arg1 != "done" || !valid);

    return white;
}

void Board::castling(Move move) {
    // Move is of type: pair<pair<xlocation, int>, pair<xlocation, int>>
    // basically (x1, y1), (x2, y2)
    shared_ptr<ChessPiece> nextPiece = nullptr;

    int kingRow = move.first.second - 1;
    int kingStartCol = static_cast<int>(move.first.first) - 1;
    int kingEndCol = static_cast<int>(move.second.first) - 1;

    // Perform king-side castling
    if (kingEndCol == kingStartCol + 2) {
        // // Move the king
        // squares[kingRow][kingEndCol].setState(squares[kingRow][kingStartCol].getState());
        // squares[kingRow][kingStartCol].setState(emptyState);

        // // Move the rook
        // squares[kingRow][kingEndCol - 1].setState(squares[kingRow][7].getState());
        // squares[kingRow][7].setState(emptyState);
        
        squares[kingRow][7].setState(nextPiece); // we used the swap instead of simply assigning in setState
        squares[kingRow][5].setState(nextPiece);
    } 
    // Perform queen-side castling
    else if (kingEndCol == kingStartCol - 2) {
        // // Move the king
        // squares[kingRow][kingEndCol].setState(squares[kingRow][kingStartCol].getState());
        // squares[kingRow][kingStartCol].setState(emptyState);

        // // Move the rook
        // squares[kingRow][kingEndCol + 1].setState(squares[kingRow][0].getState());
        // squares[kingRow][0].setState(emptyState);
        
        squares[kingRow][0].setState(nextPiece);
        squares[kingRow][3].setState(nextPiece);
    }
}

void Board::enPassant(Move move) {
    // Move is of type: pair<pair<xlocation, int>, pair<xlocation, int>>
    // basically (x1, y1), (x2, y2)
    // shared_ptr<ChessPiece> nextState = nullptr;
    shared_ptr<ChessPiece> emptyState = nullptr;

    int startX = static_cast<int>(move.first.first);
    int startY = move.first.second;
    int endX = static_cast<int>(move.second.first);
    int endY = move.second.second;

    Piece beginPeice = squares[startY-1][startX-1].getPiece();
    Piece endPiece = squares[endY-1][endX-1].getPiece();
    Piece temp;

    // Move the capturing pawn to the destination square
    // squares[startY][startX].setState(nextState);
    // squares[endY][endX].setState(nextState);

    // Remove the captured pawn
    // if (squares[endY][endX].getState()->getPiece().second) { // White pawn capturing
    //     squares[endY - 1][endX].setState(emptyState);
    // } else { // Black pawn capturing
    //     squares[endY + 1][endX].setState(emptyState);
    // }

    if(beginPeice.first == PieceType::Pawn && endPiece.first == PieceType::Empty && (startX+1 == endX || startX-1 == endX) && (startY+1 == endY || startY-1 == endY)){
        if(beginPeice.second == 0){
            temp = squares[endY][endX-1].getPiece();
            if(temp.first == PieceType::Pawn){
                squares[endY][endX-1].setState(emptyState);
            }
        }
        else{
            temp = squares[endY-2][endX-1].getPiece();
            if(temp.first == PieceType::Pawn){
                squares[endY-2][endX-1].setState(emptyState);
            }
        }
    }
}

void Board::promote(Position pos, char c){
    shared_ptr<ChessPiece> newPiece;
    switch(c) {
        case 'Q':
            newPiece = make_shared<Queen>(Queen(getPiece(pos).second)); break;
        case 'N':
            newPiece = make_shared<Knight>(Knight(getPiece(pos).second)); break;
        case 'R':
            newPiece = make_shared<Rook>(Rook(getPiece(pos).second)); break;
        case 'B':
            newPiece = make_shared<Bishop>(Bishop(getPiece(pos).second)); break;
        default: break;
    }
    squares[pos.second-1][pos.first-1].setState(newPiece);
}


Piece Board::getPiece(Position p){
    return squares[p.second-1][(static_cast<int>(p.first))-1].getPiece();
}

bool Board::isFirstMove(Position p){
    return squares[p.second-1][(static_cast<int>(p.first))-1].getNumMoves() == 0;
}

Move Board::previousMove(){
    if(moveHistory.size() > 0){
        return moveHistory.back();
    }
    return {{static_cast<xlocation>(1),0},{static_cast<xlocation>(1),0}}; // the default
}

int Board::numMoves(Position p){
    return squares[p.second-1][(static_cast<int>(p.first))-1].getNumMoves();
}

std::vector<PotentialMoves> Board::allPotentialMoves(bool colour){
    // std::cout << "The colour is " << colour << " in all Potential Moves" << std::endl;
    vector<PotentialMoves> potentialMoves;
    for(vector<Square>& line: squares){
        for(Square& square: line){
            if(square.getPiece().first != PieceType::Empty && square.getPiece().second == colour){
                potentialMoves.push_back({square.getPosition(), square.getPossibleMoves(this)});
            }
        }
    }

    // testing purpose
    // std::cout << "I am in allPotentialMoves" << std::endl;
    // for(const auto& moves: potentialMoves){
    //     std::cout << "Move from Position " << moves.first.first << " " << moves.first.second << " to Positions: " << std::endl;
    //     for(const auto& end: moves.second){
    //     std::cout << end.first << " " << end.second << std::endl;
    //     }
    // }
    return potentialMoves;
}


bool Board::inCheck(bool colour){ //return if colour is in check
    vector<PotentialMoves> potentialMoves = allPotentialMoves(!colour);
    for(const PotentialMoves& moves : potentialMoves){
        if(getPiece(moves.first).second != colour){
            for(const Position& destination: moves.second){
                if(getPiece(destination).first == PieceType::King && getPiece(destination).second == colour){
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::testMove(Move move, bool update){ // this is mainly used in king
    if(!update){
        squares[move.first.second-1][(static_cast<int>(move.first.first))-1].minusMoves();
        squares[move.first.second-1][(static_cast<int>(move.first.first))-1].minusMoves();
    }
    squares[move.second.second-1][(static_cast<int>(move.second.first))-1].check();
    nextMove(move, update);
}

void Board::reverseMove(Move move, bool update){ // reverse the move and switch back to actual piece instead of temp - used in king
    nextMove(move, false);
    if(update){
        squares[move.first.second-1][(static_cast<int>(move.first.first))-1].minusMoves();
        if(moveHistory.size() > 0){
            moveHistory.pop_back();     
        }
    }
    squares[move.first.second-1][(static_cast<int>(move.first.first))-1].undoCheck();
}

void Board::nextMove(Move move, bool update){ // this is a helper function
    shared_ptr<ChessPiece> nextPiece = nullptr;
    int y = move.first.second-1;
    int x = (static_cast<int>(move.first.first))-1;
    if(update){
        moveHistory.push_back(move);
        enPassant(move);
        if(squares[y][x].getPiece().first == PieceType::King){
            castling(move);
        }
    }
    squares[y][x].setState(nextPiece);
    squares[move.second.second-1][(static_cast<int>(move.second.first))-1].setState(nextPiece);
}
