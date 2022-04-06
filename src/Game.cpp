#include "Game.h"

Game::Game(Board *b, Player *p1, Player *p2) : m_b(b), m_p1(p1), m_p2(p2) {
  m_p1->setAsFirstPlayer(); // set player one as the first player
}

void Game::playGame() {
  std::cout << "Beginning of Game" << std::endl;

  // Run loop continously until a winner is found
  while (1) {

    // Get move from first player
    promptForMove(m_p1);

    // Check if player 1 played a winning move
    if (m_b->getWinner()) {
      m_b->displayHumanReadable();
      std::cout << "Congratulations, Player X!" << std::endl;
      break;
    }

    // Get move from second player
    promptForMove(m_p2);

    // Check if player 2 played a winning move
    if (m_b->getWinner()) {
      m_b->displayHumanReadable();
      std::cout << "Congratulations, Player O!" << std::endl;
      break;
    }
  }
}

void Game::promptForMove(Player *p) {

  // Continue prompting user for a move until they return a valid value
  while (!m_b->addToken(p->getMove(m_b))) {
    if (m_b->addToken(p->getMove(m_b)))
      break;
  }
  return;
}