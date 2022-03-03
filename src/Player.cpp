#include "Player.h"
#include "Board.h"

Player::Player() : m_firstPlayer(false) {}

void Player::setAsFirstPlayer() {
  m_firstPlayer = true;
  return;
}

HumanPlayer::HumanPlayer() : Player() {}
