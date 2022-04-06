#include "Board.h"

Board::Board() : m_position_bm(0), m_nonEmpty_bm(0), m_moves(0), m_winner(0) {
  // initialize the bottom bitmap by changing the every spot in the bottom row
  // to be 1
  for (int c = 0; c < NUM_COLS; c++) {
    m_bottom_bm |= uint64_t(1) << bitmapDirectory(
                       0, c); // binary number = (binary number OR [temp
                              // variable left shifted n places])
  }

  m_key_bm = m_position_bm + m_nonEmpty_bm + m_bottom_bm;
}

void Board::displayHumanReadable() const {
  int gridLoc(0);
  char gameToken, oppToken;

  if (firstPlayerToMove()) {
    gameToken = 'X';
    oppToken = 'O';
  } else {
    gameToken = 'O';
    oppToken = 'X';
  }

  // top row
  std::cout << "+-+-+-+-+-+-+-+" << std::endl;

  for (int i = NUM_ROWS - 1; i >= 0; i--) {
    for (int j = 0; j < NUM_COLS; j++) {
      gridLoc = bitmapDirectory(i, j);
      std::cout << "|";
      if (!getBit(m_nonEmpty_bm, gridLoc))
        std::cout << " ";
      else if (getBit(m_position_bm, gridLoc))
        std::cout << gameToken;
      else
        std::cout << oppToken;
    }
    std::cout << "|" << std::endl;
    std::cout << "+-+-+-+-+-+-+-+" << std::endl;
  }
  std::cout << " 1 2 3 4 5 6 7" << std::endl;
}

bool Board::firstPlayerToMove() const {
  if (m_moves % 2 == 1)
    return true;
  return false;
}

bool Board::addToken(int col) {
  // first check to see if the requested move is valid
  if (!validColumn(col))
    return false;

  // OR to player position with the non empty tokens to change player
  // update game state
  m_nonEmpty_bm |= m_nonEmpty_bm + getBottom_bm(col);
  m_moves++;
  m_position_bm ^= m_nonEmpty_bm;
  checkIfWinner(m_position_bm);

  return true;
}

int Board::bitmapDirectory(int row, int col) const {
  // ensure row index is valid
  if (row < 0 || row >= NUM_ROWS + 1)
    return -1;

  // ensure col index is valid
  else if (col < 0 || col >= NUM_COLS)
    return -1;

  // return 1D index
  else
    return col * (NUM_ROWS + 1) + row;
}

bool Board::validColumn(int col) const {
  // make sure that the Board is not full
  if (m_moves >= NUM_ROWS * NUM_COLS)
    return false;

  // make sure that there is no winner
  if (m_winner != 0)
    return false;

  // Check if column is in bounds
  if (col < 0 || col >= NUM_COLS)
    return false;

  // AND the new top row bitmap with the non empty bitmap to see if the
  // requested column has an empty space avaliable. If they are both 1 then that
  // column is full
  if (((getTop_bm(col) & m_nonEmpty_bm) >>
       bitmapDirectory(NUM_ROWS - 1, col)) != 0)
    return false;

  // If it passes these tests, then a token may be placed in the requested
  // column
  return true;
}

bool Board::isWinningMove(int col) const {
  Board b2 = *this;
  b2.addToken(col);
  if (b2.getWinner() == 0)
    return 0;
  return 1;
}

uint64_t Board::getTop_bm(int col) const {
  return (uint64_t(1) << bitmapDirectory(NUM_ROWS - 1, col));
}

uint64_t Board::getBottom_bm(int col) const {
  return (uint64_t(1) << bitmapDirectory(0, col));
}

void Board::checkIfWinner(uint64_t pos) {
  // NGL this is just kinda magic to me -Nick

  // declare variable to store the potential winner, this is the player who
  // played last, i.e. NOT the player who is to play
  int potWinner(-1);
  if (firstPlayerToMove())
    potWinner = 1;

  uint64_t m = pos & (pos >> (NUM_ROWS + 1));

  // Horizontal
  if (m & (m >> (2 * (NUM_ROWS + 1)))) {
    m_winner = potWinner;
    return;
  }

  // Diagonal 1
  m = pos & (pos >> NUM_ROWS);
  if (m & (m >> (2 * NUM_ROWS))) {
    m_winner = potWinner;
    return;
  }

  // Diagonal 2
  m = pos & (pos >> (NUM_ROWS + 2));
  if (m & (m >> (2 * (NUM_ROWS + 2)))) {
    m_winner = potWinner;
    return;
  }

  // Vertical
  m = pos & (pos >> 1);
  if (m & (m >> 2)) {
    m_winner = potWinner;
    return;
  }

  return;
}