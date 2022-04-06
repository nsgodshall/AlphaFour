#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Board.h"
#include "Player.h"
#include <iostream>

class Board;
class Player;

// Manages a game of connect4 given two player objects and a board object
class Game {
public:
  Game(Board *b, Player *p1, Player *p2);
  // begin the first move of the game and so on
  void playGame();

private:
  Board *m_b;
  Player *m_p1, *m_p2;

  // Prompt the user for a move until the return a valid column
  void promptForMove(Player *p);
};

#endif // GAME_INCLUDED