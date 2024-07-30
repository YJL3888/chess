#ifndef GUI_H
#define GUI_H

#include <memory>
#include <unordered_map>
#include "window.h"
#include "textdisplay.h"

class GUI {
    Xwindow window;
    std::unordered_map<char, std::string> pieceImages;
    std::string getUnicodePiece(char piece);

public:
    GUI();
    void update(std::shared_ptr<TextDisplay> textDisplay);
    void loadPieceImages();
    ~GUI();
};

#endif
