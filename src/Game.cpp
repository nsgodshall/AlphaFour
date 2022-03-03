#include <iostream>

#include "Board.h"
#include "Player.h"
#include "Game.h"

Game::Game(Board *b, Player *p1, Player *p2)
: m_b(b), m_p1(p1), m_p2(p2)
{
  m_p1->setAsFirstPlayer();
}

void Game::playGame(){
  std::cout << "Beginning of Game";

  while(m_b->getWinner() == -1){
    interactiveMove(m_p1);
    if (m_b->getWinner() != -1)
      break;
    interactiveMove(m_p2);
    
  }
}

void Game::interactiveMove(Player* p){
    m_b->displayHumanReadable();

    int colToPlay;
    if (p->isFirstPlayer())
      std::cout << "Player 1 (1-7): ";
    else
      std::cout << "Player 2 (1-7): ";
    std::cin >> colToPlay;

    while (!(m_b->addToken(colToPlay - 1))){
      std::cout << "Invalid move! Choose col (1-7): ";
      std::cin >> colToPlay;
    }
  
}