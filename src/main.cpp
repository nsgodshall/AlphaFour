#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "TranspositionTable.h"
#include "globals.h"

int main(int argc, char** argv) {
  RoboPlayer rp;
  HumanPlayer hp;
  Board b;
  // std::cout << gs;
  // std::cout << "Computing...";
  // rp.preCompute(&b);

  playFromGameString(&gs, &b, false);
  // b.displayHumanReadable();
  // std::cout << rp.getMove(&b);
}
