#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"

int main() {
  Board b;
  // Board* b_ptr = &b;
  // Board* b2 = new Board();
  // *b2 = *b_ptr;
  HumanPlayer hp;
  RoboPlayer rp;

  Game g(&b, &hp, &rp);

  g.playGame();
}
