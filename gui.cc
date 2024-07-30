
#include "gui.h"
#include <iostream>

GUI::GUI() : window(400, 400) { // Initialize the window with a 400x400 size
}

void GUI::update(std::shared_ptr<TextDisplay> textDisplay) {
    // Clear the window by filling it with white color
    window.fillRectangle(0, 0, 400, 400, Xwindow::White);

    // Draw the grid
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int x = j * 50; // Each square is 50x50 pixels
            int y = i * 50;
            char piece = textDisplay->atPos(i, j);
            
            // Draw the square
            if ((i + j) % 2 == 0) {
                window.fillRectangle(x, y, 50, 50, Xwindow::White); // White square
            } else {
                window.fillRectangle(x, y, 50, 50, Xwindow::Black); // Black square
            }
            
            // Draw the piece
            if (piece != ' ' && piece != '_') {
                std::string pieceStr(1, piece);
                window.drawString(x + 20, y + 30, pieceStr, Xwindow::Red); // Centering text within square
            }
        }
    }
}

GUI::~GUI() {
    // Implementation of GUI destructor if needed
}
