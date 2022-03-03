#include "Player.h"
#include "Board.h"

Player::Player(Board *b)
: m_board(b)
{}

HumanPlayer::HumanPlayer(Board *b)
: Player(b)
{}