#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

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

  virtual int getMove(Board* b)=0;
private:
  bool m_isInteractive;
};

class HumanPlayer : public Player {
public:
  HumanPlayer();
  int getMove(Board* b);
};

class RoboPlayer : public Player{
public:
  RoboPlayer();
  int getMove(Board* b);
private: 
  int negaMax(int depth, Board *b);
};

#endif // PLAYER_INCLUDED