#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "TranspositionTable.h"
#include "globals.h"

int main(int argc, char** argv) {
  RoboPlayer rp;
  HumanPlayer hp;
  Board b;
  std::string gs = argv[1];
  // std::cout << gs;

  playFromGameString(&gs, &b, false);
  // b.displayHumanReadable();
  std::cout << rp.getMove(&b);
}
