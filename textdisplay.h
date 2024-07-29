#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include <iostream>
#include "observer.h"
using namespace std;

class TextDisplay : public Observer {
    vector<vector<char>> display;
    
    public:
        TextDisplay(); //ctor
        void notify(Square&) override; //concrete override implementation of the pure virtual method notify in observer.
        friend ostream& operator<<(ostream&, const TextDisplay&);
        char atPos(int, int);
        ~TextDisplay(); //dtor, will change to virtual when there's gui
};

#endif
