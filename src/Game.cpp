#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

Game::Game(Board *b, Player *p1, Player *p2) : m_b(b), m_p1(p1), m_p2(p2) {
  m_p1->setAsFirstPlayer();
}

void Game::playGame() {
  std::cout << "Beginning of Game" << std::endl;
  while (1) {

    // Get move from first player
    promptForMove(m_p1);

    // Check if player 1 played a winning move
    if (m_b->getWinner()){
      m_b->displayHumanReadable();
      std::cout << "Congratulations, Player X!" << std::endl;
      break;
    }

    // Get move from second player
    promptForMove(m_p2);

    if (m_b->getWinner()){
      m_b->displayHumanReadable();
      std::cout << "Congratulations, Player O!" << std::endl;
      break;
    }
  }
}

void Game::promptForMove(Player* p){
  while(!m_b->addToken(p->getMove(m_b))){
    if(m_b->addToken(p->getMove(m_b)))
      break;
  }
  return;
}