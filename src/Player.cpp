#include "Player.h"
#include "Board.h"
#include "globals.h"

// FOR DEBUGGING
#include <chrono>

Player::Player(bool interactive) : m_firstPlayer(false), m_isInteractive(interactive) 
{
  std::srand(std::time(nullptr));
}

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
  for (int d = 1; d < 2; d++){
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int c = 0; c < NUM_COLS; c++){
      Board* b2 = new Board();
      *b2 = *b;
      b2->addToken(c);
      std::cout << "Col: " << c << ", score: " << negaMax(11, b2,   NUM_ROWS*NUM_COLS, -NUM_ROWS*NUM_COLS) << std::endl;
      delete b2;
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "DEPTH: " << 12 << " DURATION: " << duration.count() << " microseconds" << std::endl;
  }
  return std::rand()%7;
}

int RoboPlayer::negaMax(int depth, Board *b, int alpha, int beta){
  // Depth, for debugging purposes
  if (depth <= 0){
    return -NUM_ROWS*NUM_COLS;
  }
  // Check for a drawn game 
  if (b->getNumMoves() == NUM_ROWS*NUM_COLS)
    return 0; 

  if (b->getWinner())
    return (NUM_ROWS*NUM_COLS - b->getNumMoves()); 
  

  int max = -NUM_ROWS*NUM_COLS;
  if(beta > max) {
    beta = max;                     // there is no need to keep beta above our max possible score.
    if(alpha >= beta) return beta;  // prune the exploration if the [alpha;beta] window is empty.
  }

  for (int c = 0; c < NUM_COLS; c++){
    Board* b2 = new Board();
    *b2 = *b;
  
    b2->addToken(c);
    int score = -negaMax(depth - 1, b2, alpha, beta);

    if(score >= beta) return score;  // prune the exploration if we find a possible move better than what we were looking for.
    if(score > alpha) alpha = score; // reduce the [alpha;beta] window for next exploration, as we only 
      // need to search for a position that is better than the best so far.
    b2 = nullptr;
    delete b2;
  }
  return alpha; 
}