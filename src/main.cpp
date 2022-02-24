#include "board.h"
#include "globals.h"

int main() {
  board b;
  std::string game1 = "12233434454";
  playFromGameString(&game1, &b, 1);
    // b.addToken(1);
    // b.displayHumanReadable();
  return 0;
}
