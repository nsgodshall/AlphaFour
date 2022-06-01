#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Board.h"
#include "Clock.h"
#include "TranspositionTable.h"

#include <array> // For column exploration order array

class Board;

// Base player class
class Player  {
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
class CLI_Player : public Player {
public:
  CLI_Player();
  int getMove(Board *b);
};

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
  int getMoveTime(Board *b, unsigned int d);

private:
  // Probably going to delete the two negaMax algorithms
  int negaMax(Board *b);
  int negaMax(Board *b, int alpha, int beta);

  // Minimax algorithm without alpha-beta pruning
  int miniMax(Board *b, bool maxPlayer, int depth);

  // Minimax algorithm with alpha-beta pruning
  int miniMax(Board &b, bool maxPlayer, int depth, int alpha, int beta);
  int minDepth = 14;
  const int CUTOFF_TIME = 1000000*1; // make time per move in microseconds 

  int solve(Board &b, int depth);

  // Array that dictates the move order that moves are explored (starting with
  // col 3, ending with col 6)
  std::array<int, 7> colOrder = {3, 2, 4, 1, 5, 0, 6};

  // Declare variable for transposition table that will be used to store values
  // for certain game sgtate
  TranspositionTable T;
};

#endif // PLAYER_INCLUDED7