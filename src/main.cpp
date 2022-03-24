#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"

int main() {
  Board b;
  HumanPlayer hp;
  RoboPlayer rp;

  Game g(&b, &hp, &rp);

  g.playGame();
}
