#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

Game::Game(Board *b, Player *p1, Player *p2) : m_b(b), m_p1(p1), m_p2(p2) {
  m_p1->setAsFirstPlayer();
}

void Game::playGame() {
  std::cout << "Beginning of Game";
  while (m_b->getWinner() == 0) {

    // Get move from first player
    if (m_p1->isInterctive()) interactiveMove(m_p1);
    else m_p1->getMove();

    // Check if player 1 played a winning move
    if (m_b->getWinner() != 0)
      break;

    // Get move from second player
    if (m_p2->isInterctive()) interactiveMove(m_p2);
    else m_p2->getMove();
  }
}

void Game::interactiveMove(Player *p) {
  // Display the current game state
  m_b->displayHumanReadable();

  int colToPlay;

  // Prompt the player to move to select a column
  if (p->isFirstPlayer())
    std::cout << "Player 1 (1-7): ";
  else
    std::cout << "Player 2 (1-7): ";
  std::cin >> colToPlay;

  // Attempt to add a token to the selected column, if the selected move is invalid, prompt the player to select a new column
  while (!(m_b->addToken(colToPlay - 1))) {
    std::cout << "Invalid move! Choose col (1-7): ";
    std::cin >> colToPlay;
  }
}