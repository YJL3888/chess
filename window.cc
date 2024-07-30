#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

// REFERENCE: This entire file is the same as  the assignment 3 question 3 window.cc file (except the drawString)

Xwindow::Xwindow(int width, int height) : width(width), height(height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0, (XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10] = {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

    cmap = DefaultColormap(d, DefaultScreen(d));
    for (int i = 0; i < 10; ++i) {
        if (!XParseColor(d, cmap, color_vals[i], &xcolour)) {
            cerr << "Bad colour: " << color_vals[i] << endl;
        }
        if (!XAllocColor(d, cmap, &xcolour)) {
            cerr << "Bad colour: " << color_vals[i] << endl;
        }
        colours[i] = xcolour.pixel;
    }

    XSetForeground(d, gc, colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d, True);
    usleep(2500);
    XSelectInput(d, w, ExposureMask);
    XFlush(d);
    XEvent event;
    XNextEvent(d, &event); // Hang until the window is ready.
    XSelectInput(d, w, 0);
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

// Below is for debugging purposes
// void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
//     std::cout << "fillRectangle called with: x=" << x << ", y=" << y
//               << ", width=" << width << ", height=" << height
//               << ", colour=" << colour << std::endl;

//     if (x < 0 || y < 0 || width <= 0 || height <= 0 || colour < 0 || colour >= 10) {
//         std::cerr << "Invalid parameters for fillRectangle" << std::endl;
//         return;
//     }

//     XSetForeground(d, gc, colours[colour]);
//     XFillRectangle(d, w, gc, x, y, width, height);
//     XSetForeground(d, gc, colours[Black]);
// }

void Xwindow::drawString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    Font f = XLoadFont(d, "6x13");
    XTextItem ti;
    ti.chars = const_cast<char *>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f;
    XDrawText(d, w, gc, x, y, &ti, 1);
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);
}

void Xwindow::drawImage(int x, int y, const std::string &filename) {
    Pixmap pixmap;
    XpmAttributes attributes;
    attributes.valuemask = XpmSize;
    int result = XpmReadFileToPixmap(d, w, const_cast<char *>(filename.c_str()), &pixmap, nullptr, &attributes);
    if (result != XpmSuccess) {
        std::cerr << "Error loading image: " << filename << std::endl;
        return;
    }
    XCopyArea(d, pixmap, w, gc, 0, 0, attributes.width, attributes.height, x, y);
    XFreePixmap(d, pixmap);
}
