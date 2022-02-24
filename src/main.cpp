#include "board.h"
#include "globals.h"

int main() {
  board b;
  std::string game1 = "1234";
  playFromGameString(&game1, &b);
  return 0;
}
