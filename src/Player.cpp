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
  int maxCol = 0;
  int maxScore = -999;

  auto start = std::chrono::high_resolution_clock::now(); // START DEBUG TIMER

  // Iterate through each column
  for (int c = 0; c < NUM_COLS; c++){
    // ensure move is valid before attempt
    if (b->validColumn(c)){ 
      if (b->isWinningMove(c))
        return c;
      // Create new board that is a copy of current game state to test moves with
      Board* b2 = new Board();
      *b2 = *b;

      b2->addToken(c);

      int score = -negaMax(b2, 999, -999);

      if (score > maxScore) {
          maxScore = score;
          maxCol = c;
      }

      std::cout << "Col: " << c << ", score: " << score << " Is winning move: " << b->isWinningMove(c) <<std::endl;
      b2 = nullptr;
      delete b2;
    }
  }
  std::cout << "I would play column " << maxCol << std::endl;

  // END DEBUG TIMER, report time
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "DEPTH: " << d << " DURATION: " << duration.count() << " microseconds" << std::endl; 

  return maxCol;
}

int RoboPlayer::negaMax(Board *b){
  if (b->getNumMoves() == NUM_ROWS*NUM_COLS){
    return 0; 
  } 

  for (int c = 0; c < NUM_COLS; c++){
    if (b->validColumn(c) && b->isWinningMove(c)){
      return (NUM_COLS*NUM_ROWS + 1 - b->getNumMoves())/2;
    }
  }

  int max = (NUM_ROWS*NUM_COLS - 1 - b->getNumMoves())/2;

  for (int c = 0; c < NUM_COLS; c++){
    if (b->validColumn(c)){
      Board* b2 = new Board();
      *b2 = *b;
    
      b2->addToken(c);
      int score = -negaMax(b2);
      if (score > max) max = score;
      b2 = nullptr;
      delete b2;
    }
  }
  return max;
}

int RoboPlayer::negaMax(Board *b, int alpha, int beta){
  // Check for a drawn game 
  if (b->getNumMoves() == NUM_ROWS*NUM_COLS){
    return 0; 
  }

  for (int c = 0; c < NUM_COLS; c++){
    if (b->validColumn(c) && b->isWinningMove(c)){
      return (NUM_COLS*NUM_ROWS + 1 - b->getNumMoves())/2;
    }
  }

  int max = (NUM_ROWS*NUM_COLS - 1 - b->getNumMoves())/2;

  if (beta > max) {
    beta = max;                     // there is no need to keep beta above our max possible score.
    if(alpha >= beta) 
      return beta;  // prune the exploration if the [alpha;beta] window is empty.
  }

  for (int c = 0; c < NUM_COLS; c++){
    if (b->validColumn(c)){
      Board* b2 = new Board();
      *b2 = *b;
    
      b2->addToken(c);
      int score = -negaMax(b2, -alpha, -beta);

      if(score >= beta) 
        return score;  // prune the exploration if we find a possible move better than what we were looking for.
      if(score > alpha) 
        alpha = score; // reduce the [alpha;beta] window for next exploration, as we only 
        // need to search for a position that is better than the best so far.
      b2 = nullptr;
      delete b2;
    }
  }
  return alpha; 
}