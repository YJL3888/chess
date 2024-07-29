#include "textdisplay.h"
#include "square.h"
using namespace std;

/*
creates 8*8 spaces grid for display.
*/
TextDisplay::TextDisplay() {
    for (int i = 0; i < 8; i++) {
        display.push_back(vector<char>(8, ' '));
    }
}

void TextDisplay::notify(Square& s) {
    Position posXY = s.getPosition();
    char character;
    switch(s.getPiece().first) {
        case PieceType::Pawn: character = 'P'; break;
        case PieceType::Rook: character = 'R'; break;
        case PieceType::Knight: character = 'N'; break;
        case PieceType::Bishop: character = 'B'; break;
        case PieceType::Queen: character = 'Q'; break;
        case PieceType::King: character = 'K'; break;
        default: character = (posXY.first + posXY.second) % 2 == 1 ? ' ' : '_'; // show underline for a black/shaded square to create checker.
    }
    if (s.getPiece().second == 0 && character <= 'Z' && character >= 'A') {
        character += 32; //convert to lower case letters for black player.
    }
    display[8-posXY.second][posXY.first-1] = character; //display[y][x] = char
}

char TextDisplay::atPos(int i, int j) { return display.at(i).at(j); }

ostream& operator<<(ostream& out, const TextDisplay& textDisplay) {
    int size = 8;
    for (auto row: textDisplay.display) {
        out << size << " "; // lowest row is 1.
        size--;
        for (auto column: row) {
            out << column; // prints the square.
        }
        out << endl; // new line after each row.
    }
    out << endl << "  abcdefgh\n\n" << endl; // prints the bottom row index.
    return out;
}

TextDisplay::~TextDisplay() {
    // Implementation of TextDisplay destructor
}
