#include "gui.h"

#include <iostream>

GUI::GUI() : window(400, 400) {  // Initialize the window with a 400x400 size
  loadPieceImages();
}

void GUI::loadPieceImages() {
  pieceImages['P'] = "pictures/pawnw.xpm";
  pieceImages['R'] = "pictures/rookw.xpm";
  pieceImages['N'] = "pictures/knightw.xpm";
  pieceImages['B'] = "pictures/bishopw.xpm";
  pieceImages['Q'] = "pictures/queenw.xpm";
  pieceImages['K'] = "pictures/kingw.xpm";
  pieceImages['p'] = "pictures/pawnb.xpm";
  pieceImages['r'] = "pictures/rookb.xpm";
  pieceImages['n'] = "pictures/knightb.xpm";
  pieceImages['b'] = "pictures/bishopb.xpm";
  pieceImages['q'] = "pictures/queenb.xpm";
  pieceImages['k'] = "pictures/kingb.xpm";
}

std::string GUI::getUnicodePiece(char piece) {
  switch (piece) {
    case 'K':
      return "\u2654";  // White King
    case 'Q':
      return "\u2655";  // White Queen
    case 'R':
      return "\u2656";  // White Rook
    case 'B':
      return "\u2657";  // White Bishop
    case 'N':
      return "\u2658";  // White Knight
    case 'P':
      return "\u2659";  // White Pawn
    case 'k':
      return "\u265A";  // Black King
    case 'q':
      return "\u265B";  // Black Queen
    case 'r':
      return "\u265C";  // Black Rook
    case 'b':
      return "\u265D";  // Black Bishop
    case 'n':
      return "\u265E";  // Black Knight
    case 'p':
      return "\u265F";  // Black Pawn
    default:
      return " ";
  }
}

void GUI::update(std::shared_ptr<TextDisplay> textDisplay, int drawImage) {
  // Clear the window by filling it with white color
  window.fillRectangle(0, 0, 400, 400, Xwindow::White);

  // Draw the grid
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      int x = j * 50;  // Each square is 50x50 pixels
      int y = i * 50;
      char piece = textDisplay->atPos(i, j);

      if (drawImage == 2) {
        // Draw the square
        if ((i + j) % 2 == 0) {
          window.fillRectangle(x, y, 50, 50, Xwindow::White);  // White square
        } else {
          window.fillRectangle(x, y, 50, 50, Xwindow::Green);  // Green square
        }

        // Draw the piece
        if (piece != ' ' && piece != '_') {
          auto it = pieceImages.find(piece);
          if (it != pieceImages.end()) {
            window.drawImage(x, y, it->second);
          }
        }
      } else {
        // Draw the square
        if ((i + j) % 2 == 0) {
          window.fillRectangle(x, y, 50, 50, Xwindow::White);  // White square
        } else {
          window.fillRectangle(x, y, 50, 50, Xwindow::Black);  // Black square
        }

        // Draw the piece
        if (piece != ' ' && piece != '_') {
          std::string pieceStr(1, piece);
          window.drawString(x + 20, y + 30, pieceStr,
                            Xwindow::Red);  // Centering text within square
        }
      }
    }
  }
}

GUI::~GUI() {
  // Implementation of GUI destructor if needed
}
