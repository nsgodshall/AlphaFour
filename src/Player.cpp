#include "Player.h"
#include "Board.h"
#include "globals.h"

// FOR DEBUGGING
#include <chrono>

Player::Player(bool interactive)
    : m_firstPlayer(false), m_isInteractive(interactive) {
  std::srand(std::time(nullptr));
}

void Player::setAsFirstPlayer() {
  m_firstPlayer = true;
  return;
}

// HUMAN PLAYER IMPLEMENTAITONS

// Constructor
HumanPlayer::HumanPlayer() : Player(true) {}

int HumanPlayer::getMove(Board *b) {
  int col(0);
  b->displayHumanReadable();
  if (isFirstPlayer())
    std::cout << "Player X, ";
  else
    std::cout << "Player O, ";
  std::cout << "Enter a column to play (1-7): ";
  std::cin >> col;
  while (!b->validColumn(col - 1)) {
    std::cout << "Invalid Column";
    std::cout << "Enter a column to play (1-7): ";
    std::cin >> col;
  }
  return col - 1;
}
// ROBOT PLAYER IMPLEMENTATIONS

// Constructor
RoboPlayer::RoboPlayer() : Player(false) {}

int RoboPlayer::getMove(Board *b) {
  int maxCol = 0;
  int maxScore = -999;

  auto start = std::chrono::high_resolution_clock::now(); // START DEBUG TIMER

  // Iterate through each column
  for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
    // ensure move is valid before attempt
    if (b->validColumn(*it)) {
      if (b->isWinningMove(*it))
        return *it;
      // Create new board that is a copy of current game state to test moves
      // with
      Board *b2 = new Board();
      *b2 = *b;

      b2->addToken(*it);

      // int score = -negaMax(b2, 999, -999);
      int score = miniMax(b2, false, 50, -999, 999);
      if (score > maxScore) {
        maxScore = score;
        maxCol = *it;
      }

      std::cout << "Col: " << *it << ", score: " << score << std::endl;
      b2 = nullptr;
      delete b2;
    }
  }

  std::cout << "I would play column " << maxCol + 1 << std::endl;

  // END DEBUG TIMER, report time
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << " DURATION: " << duration.count() << " microseconds"
            << std::endl;

  return maxCol;
}

// int RoboPlayer::negaMax(Board *b){
//   if (b->getNumMoves() == NUM_ROWS*NUM_COLS){
//     return 0;
//   }

//   for (int i = 0; i < NUM_COLS; i++){
//     if (b->validColumn(c) && b->isWinningMove(c)){
//       return (NUM_COLS*NUM_ROWS + 1 - b->getNumMoves())/2;
//     }
//   }

//   int max = (NUM_ROWS*NUM_COLS - 1 - b->getNumMoves())/2;

//   for (int c = 0; c < NUM_COLS; c++){
//     if (b->validColumn(c)){
//       Board* b2 = new Board();
//       *b2 = *b;

//       b2->addToken(c);
//       int score = -negaMax(b2);
//       if (score > max) max = score;
//       b2 = nullptr;
//       delete b2;
//     }
//   }
//   return max;
// }

int RoboPlayer::negaMax(Board *b, int alpha, int beta) {
  // Check for a drawn game
  if (b->getNumMoves() == NUM_ROWS * NUM_COLS) {
    return 0;
  }

  for (int c = 0; c < NUM_COLS; c++) {
    if (b->validColumn(c) && b->isWinningMove(c)) {
      return (NUM_COLS * NUM_ROWS + 1 - b->getNumMoves()) / 2;
    }
  }

  int max = (NUM_ROWS * NUM_COLS - 1 - b->getNumMoves()) / 2;

  if (beta > max) {
    beta = max; // there is no need to keep beta above our max possible score.
    if (alpha >= beta)
      return beta; // prune the exploration if the [alpha;beta] window is empty.
  }

  for (int c = 0; c < NUM_COLS; c++) {
    if (b->validColumn(c)) {
      Board *b2 = new Board();
      *b2 = *b;

      b2->addToken(c);
      int score = -negaMax(b2, -alpha, -beta);

      if (score >= beta)
        return score; // prune the exploration if we find a possible move better
                      // than what we were looking for.

      if (score > alpha)
        alpha = score; // reduce the [alpha;beta] window for next exploration,
                       // as we only
      // need to search for a position that is better than the best so far.

      b2 = nullptr;
      delete b2;
    }
  }
  return alpha;
}

int RoboPlayer::miniMax(Board *b, bool maxPlayer, int depth) {
  // Base case, hopefully this can be removed once optimized, or it can be used
  // as a proxy for difficulty
  if (depth <= 0) {
    return 0;
  }

  // Draw game
  if (b->getNumMoves() == NUM_ROWS * NUM_COLS) {
    return 0;
  }

  // Maximizing player
  if (maxPlayer) {
    // Check if maximizing player has a winning move
    for (int c = 0; c < NUM_COLS; c++) {
      if (b->validColumn(c) && b->isWinningMove(c)) {
        return (NUM_COLS * NUM_ROWS + 1 - b->getNumMoves()) / 2;
      }
    }

    // Initilize score to negative infinity
    int score = -999;

    for (int c = 0; c < NUM_COLS; c++) {
      if (b->validColumn(c)) {
        // Create a duplicate of current game state to add a test move to
        Board *b2 = new Board;
        *b2 = *b;
        b2->addToken(c);

        // recursively run minimax
        score = std::max(score, miniMax(b2, false, depth - 1));

        b2 = nullptr;
        delete b2;
      }
    }
    return score;
  }

  // Minimizing player implementations
  else {
    // See if the minimizing player has a winning move
    for (int c = 0; c < NUM_COLS; c++) {
      if (b->validColumn(c) && b->isWinningMove(c)) {
        return -(NUM_COLS * NUM_ROWS + 1 - b->getNumMoves()) / 2;
      }
    }

    // initialize score of minimizing player to positive infinty
    int score = 999;

    for (int c = 0; c < NUM_COLS; c++) {

      if (b->validColumn(c)) {
        // Create dupliate board and add test move
        Board *b2 = new Board;
        *b2 = *b;
        b2->addToken(c);

        // recursively run minimax
        score = std::min(score, miniMax(b2, true, depth - 1));

        b2 = nullptr;
        delete b2;
      }
    }
    return score;
  }
}

int RoboPlayer::miniMax(Board *b, bool maxPlayer, int depth, int alpha,
                        int beta) {
  // Base case, hopefully this can be removed once optimized, or it can be used
  // as a proxy for difficulty
  if (depth <= 0) {
    return 0;
  }

  // Draw game
  if (b->getNumMoves() == NUM_ROWS * NUM_COLS) {
    return 0;
  }

  // Maximizing player
  if (maxPlayer) {
    // Check if maximizing player has a winning move
    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
      if (b->validColumn(*it) && b->isWinningMove(*it)) {
        return (NUM_COLS * NUM_ROWS + 1 - b->getNumMoves()) / 2;
      }
    }

    // Initilize score to negative infinity
    int score = -999;

    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
      if (b->validColumn(*it)) {
        // Create a duplicate of current game state to add a test move to
        Board *b2 = new Board;
        *b2 = *b;
        b2->addToken(*it);

        // recursively run minimax
        score = std::max(score, miniMax(b2, false, depth - 1, alpha, beta));

        // If the current score is greater than beta, prune this branch
        if (score >= beta)
          break;

        alpha = std::max(alpha, score);
        b2 = nullptr;
        delete b2;
      }
    }
    return score;
  }

  // Minimizing player implementations
  else {
    // See if the minimizing player has a winning move
    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
      if (b->validColumn(*it) && b->isWinningMove(*it)) {
        return -(NUM_COLS * NUM_ROWS + 1 - b->getNumMoves()) / 2;
      }
    }

    // initialize score of minimizing player to positive infinty
    int score = 999;

    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {

      if (b->validColumn(*it)) {
        // Create dupliate board and add test move
        Board *b2 = new Board;
        *b2 = *b;
        b2->addToken(*it);

        // recursively run minimax
        score = std::min(score, miniMax(b2, true, alpha, beta, depth - 1));

        if (score <= alpha)
          break;

        beta = std::min(beta, score);
        b2 = nullptr;
        delete b2;
      }
    }
    return score;
  }
}
