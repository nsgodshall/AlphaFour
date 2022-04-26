#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "TranspositionTable.h"
#include "globals.h"

int main() {
  RoboPlayer rp;
  HumanPlayer hp;
  Board b;
  Game g(&b, &rp, &hp);

  g.playGame();
  // benchmark();
}
