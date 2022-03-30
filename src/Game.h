#ifndef GAME_INCLUDED
#define GAME_INCLUDED

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

  void promptForMove(Player *p);
};

#endif // GAME_INCLUDED