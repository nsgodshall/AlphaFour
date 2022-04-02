#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"
#include "TranspositionTable.h"

int main() {
  // Board b;
  // // Board* b_ptr = &b;
  // // Board* b2 = new Board();
  // // *b2 = *b_ptr;
  // HumanPlayer hp;
  // RoboPlayer rp;

  // Game g(&b, &rp, &hp);

  // g.playGame();

  TranspositionTable T(100);
  uint64_t k(125213);
  std::cout << T.getIndex(k) << std::endl;
}
