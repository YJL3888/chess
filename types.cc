#include "types.h"

xlocation chartoXlocation(char c) {
  xlocation x;
  switch (c) {
    case '1':
      x = A;
      break;
    case '2':
      x = B;
      break;
    case '3':
      x = C;
      break;
    case '4':
      x = D;
      break;
    case '5':
      x = E;
      break;
    case '6':
      x = F;
      break;
    case '7':
      x = G;
      break;
    case '8':
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
