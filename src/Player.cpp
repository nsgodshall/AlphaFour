#include "Player.h"
#include "Board.h"
#include "globals.h"

Player::Player(bool interactive) : m_firstPlayer(false), m_isInteractive(interactive) {}

void Player::setAsFirstPlayer() {
  m_firstPlayer = true;
  return;
}


// HUMAN PLAYER IMPLEMENTAITONS

// Constructor
HumanPlayer::HumanPlayer() : Player(true) {}

int HumanPlayer::getMove(Board* b){
  int col(0);    
  b->displayHumanReadable();
  if (isFirstPlayer()) std::cout << "Player X, ";
  else std::cout << "Player O, ";
  std::cout << "Enter a column to play (1-7): ";
  std::cin >> col;
  while (!b->validColumn(col-1)) {
    std::cout << "Invalid Column";
    std::cout << "Enter a column to play (1-7): ";
    std::cin >> col;
  }
  return col-1;
}
// ROBOT PLAYER IMPLEMENTATIONS

// Constructor
RoboPlayer::RoboPlayer() : Player(false) {}

int RoboPlayer::getMove(Board* b){
  // for (int c = 0; c < NUM_COLS; c++){
  //   std::cout << "Col: " << c << ", score: " << negaMax(5, b);
  // }
  return 5;
}

int RoboPlayer::negaMax(int depth, Board *b){
  if (b->getWinner() != 0) 
    return (NUM_ROWS*NUM_COLS - b->getNumMoves()); 

  if (depth == 0){
    return NUM_ROWS*NUM_COLS - b->getNumMoves();
  }

  int max = -999;
  for (int c = 0; c < NUM_COLS; c++){
    Board b2_ = *b;
    Board* b2 = &b2_; 
  
    b2->addToken(c);
    int score = - negaMax(depth--, b2);
    if (score > max) max = score;
  }

  return max; 
}