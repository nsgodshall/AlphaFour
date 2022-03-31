#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <array>
#include <cstdlib> // for std::rand()
#include <ctime>   // for random seed

class Board;

// Base player class
class Player {
public:
  // Variable to store whether a given player object is the first to play
  bool m_firstPlayer;

  Player(bool interactive);

  // accessors
  inline bool isFirstPlayer() const { return m_firstPlayer; }
  inline bool isInterctive() const { return m_isInteractive; }

  // mutators
  void setAsFirstPlayer();

  virtual int getMove(Board *b) = 0;

private:
  bool m_isInteractive;
};

// Class for a player whos moves are dictated by human input
class HumanPlayer : public Player {
public:
  HumanPlayer();
  int getMove(Board *b);
};

// Class for a player where moves are dictated by minimax algoritm
class RoboPlayer : public Player {
public:
  RoboPlayer();
  int getMove(Board *b);

private:
  // Probably going to delete the two negaMax algorithms
  int negaMax(Board *b);
  int negaMax(Board *b, int alpha, int beta);

  // Minimax algorithm without alpha-beta pruning
  int miniMax(Board *b, bool maxPlayer, int depth);

  // Minimax algorithm with alpha-beta pruning
  int miniMax(Board& b, bool maxPlayer, int depth, int alpha, int beta);

  std::array<int, 7> colOrder = {3, 2, 4, 1, 5, 0, 6};
};

#endif // PLAYER_INCLUDED