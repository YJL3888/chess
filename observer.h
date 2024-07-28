#ifndef OBSERVER_H
#define OBSERVER_H

class Square;
class Observer {
    public:
        virtual void notify(Square&) = 0;
};

#endif
