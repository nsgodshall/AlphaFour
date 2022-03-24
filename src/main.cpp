#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "globals.h"

int main() {
  Board b;
  std::string gs = "33";
  playFromGameString(&gs, &b, true); 
  b.removeToken(2);
}
