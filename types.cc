#include "types.h"

xlocation chartoXlocation(char c){
    xlocation x;
    switch(c){
        case 'A':
            x = A;
            break;
        case 'B':
            x = B;
            break;
        case 'C':
            x = C;
            break;
        case 'D':
            x = D;
            break;
        case 'E':
            x = E;
            break;
        case 'F':
            x = F;
            break;
        case 'G':
            x = G;
            break;
        case 'H':
            x = H;
            break;
    }
    return x;
}
