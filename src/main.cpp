#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"

int main() {
  Board b;
  HumanPlayer p1;
  HumanPlayer p2;
  Game g(&b, &p1, &p2);
  g.playGame();
}
