#ifndef GUI_H
#define GUI_H

#include "window.h"
#include "textdisplay.h"
#include <memory>

class GUI {
    Xwindow window;
    
public:
    GUI();
    void update(std::shared_ptr<TextDisplay> textDisplay);
    ~GUI();
};

#endif

