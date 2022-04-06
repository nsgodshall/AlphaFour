#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"
#include "TranspositionTable.h"

int main() {
  RoboPlayer rp;
  HumanPlayer hp;
  Board b;

  Game g(&b, &rp, &hp);

  g.playGame();
  // benchmark();  
}
