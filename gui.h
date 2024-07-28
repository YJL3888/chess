#ifndef GUI_H
#define GUI_H
#include "gui.h"
using namespace std;

class TextDisplay;

class GUI {
    void drawBoard();
    int updateCount;
    
    public:
        GUI();
        void drawPiece(char, int, int);
        void update(shared_ptr<TextDisplay> display) {}
        virtual ~GUI();
};

#endif
