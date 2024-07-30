#include "types.h"

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

char XlocationToChar(xlocation xl) {
  switch (xl) {
    case A:
      return 'A';
    case B:
      return 'B';
    case C:
      return 'C';
    case D:
      return 'D';
    case E:
      return 'E';
    case F:
      return 'F';
    case G:
      return 'G';
    case H:
      return 'H';
    default:
      return '?';
  }
}
