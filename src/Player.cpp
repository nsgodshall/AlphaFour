#include "Player.h"

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
RoboPlayer::RoboPlayer() : Player(false), T(99999) { T.load(); }

int RoboPlayer::getMove(Board *b){
  int maxScore = -999;
  int maxCol = 0;
  int depth(minDepth);

  Clock c; 
  c.start();
  while (1){
    for (auto it = colOrder.begin(); it != colOrder.end(); it++){
      Board b2 = *b;
      if (b->validColumn(*it)){
        if (b->isWinningMove(*it))
          return *it;
        b2.addToken(*it);

        // int score = solve(b2, minDepth);
        int score = miniMax(b2, false, depth, -999, 999);
        // std::cout << *it + 1 << ", " << score << std::endl;
        if (score > maxScore){
          maxScore = score;
          maxCol = *it;
        }
      }
    }
    if (c.timeNow() > CUTOFF_TIME || depth > 41) break;
    depth++;
  }
  minDepth = depth;
  // std::cout << minDepth << std::endl;
  // std::cout << c.timeNow()/1000000.0 << std::endl;
  if (maxScore > 0){
    std::cout << "I will win" << std::endl;
  }
  if (maxScore < 0){
    std::cout << "I will lose" << std::endl;
  }
  return maxCol;
}

int RoboPlayer::solve(Board &b, int d){

  int min = -(NUM_COLS*NUM_ROWS - b.getNumMoves())/2;
  int max = (NUM_COLS*NUM_ROWS+1 - b.getNumMoves())/2;

  while (min < max){
    int med = min + (max - min)/2;
    if (med <= 0 && min/2 < med)
      med = min/2;
    else if (med >= 0 && max/2 > med) 
      med = max/2;
    int r = miniMax(b, false, d, med, med + 1);
    if (r <= med)
      max = r;
    else 
      min = r;  
  }
  return min;

}

int RoboPlayer::miniMax(Board &b, bool maxPlayer, int depth, int alpha,
                        int beta) {
  // Base case, hopefully this can be removed once optimized, or it can be used
  // as a proxy for difficulty
  if (depth <= 0) {
    return 0;
  }

  // Draw game
  if (b.getNumMoves() == NUM_ROWS * NUM_COLS) {
    return 0;
  }

  // Maximizing player
  if (maxPlayer) {
    // Check if maximizing player has a winning move
    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
      if (b.validColumn(*it) && b.isWinningMove(*it)) {
        return (NUM_COLS * NUM_ROWS + 1 - b.getNumMoves()) / 2;
      }
    }

    // Initilize score to negative infinity
    int score = -999;
    if (int val = T.get(b.getKey())) {
      score = val + Board::MIN_SCORE - 1;
      if (score >= beta)
        return score;
    }

    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
      if (b.validColumn(*it)) {
        // Create a duplicate of current game state to add a test move to
        Board b2 = b;
        b2.addToken(*it);

        // recursively run minimax
        score = std::max(score, miniMax(b2, false, depth - 1, alpha, beta));

        // If the current score is greater than beta, prune this branch
        if (score >= beta)
          break;

        alpha = std::max(alpha, score);
      }
    }
    T.put(b.getKey(), alpha - Board::MIN_SCORE + 1);
    return score;
  }

  // Minimizing player implementations
  else {
    // See if the minimizing player has a winning move
    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {
      if (b.validColumn(*it) && b.isWinningMove(*it)) {
        return -(NUM_COLS * NUM_ROWS + 1 - b.getNumMoves()) / 2;
      }
    }

    // initialize score of minimizing player to positive infinty
    int score = 999;
    if (int val = T.get(b.getKey())) {
        score = -(val + Board::MIN_SCORE - 1);
      if (score <= alpha)
        return score;
    }

    for (auto it = colOrder.begin(); it != colOrder.end(); it++) {

      if (b.validColumn(*it)) {
        // Create dupliate board and add test move
        Board b2 = b;
        b2.addToken(*it);

        // recursively run minimax
        score = std::min(score, miniMax(b2, true, depth - 1, alpha, beta));

        if (score <= alpha)
          break;

        beta = std::min(beta, score);
      }
    }
    T.put(b.getKey(), score);

    return score;
  }
}