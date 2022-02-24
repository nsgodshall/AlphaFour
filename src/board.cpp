#include "board.h"

board::board() : m_position_bm(0), m_nonEmpty_bm(0), m_moves(0) {
  // initialize the bottom bitmap by changing the every spot in the bottom row
  // to be 1
  for (int c = 0; c < NUM_COLS; c++) {
    m_bottom_bm |= uint64_t(1) << bitmapDirectory(
                       0, c); // binary number = (binary number OR [temp
                              // variable left shifted n places])
  }

  m_key_bm = m_position_bm + m_nonEmpty_bm + m_bottom_bm;
  
  // DEBUGGING BELOW
  // DEBUGGING ABOVE
}

// TODO: Check if the requested column is full.
bool board::addToken(int col) {
  // first check to see if the requested move is valid
  std::cout << "Valid col: " << validColumn(col) << std::endl;

  if (!validColumn(col))
    return false;

  // OR to player position with the non empty tokens to change player
  m_position_bm ^= m_nonEmpty_bm; 
  // update game state
  m_nonEmpty_bm |= m_nonEmpty_bm + getBottom_bm(col);
  m_moves++;

  // DEBUGGING BELOW
  visualizeBitmap(m_nonEmpty_bm);
  std::cout << "Is there a winner?: " << checkIfWinner() << std::endl;  
  // DEBUGGING ABOVE

  return true;
}

int board::bitmapDirectory(int row, int col) {
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

bool board::validColumn(int col) {
  // Check if column is in bounds
  if (col < 0 || col >= NUM_COLS)
    return false;

  // AND the new top row bitmap with the non empty bitmap to see if the
  // requested column has an empty space avaliable. If they are both 1 then that column is full 
  if (((getTop_bm(col) & m_nonEmpty_bm) >> bitmapDirectory(NUM_ROWS - 1, col)) != 0)
    return false;

  // If it passes these tests, then a token may be placed in the requested
  // column
  return true;
}

uint64_t board::getTop_bm(int col){
  return (uint64_t(1) << bitmapDirectory(NUM_ROWS - 1, col));
}

uint64_t board::getBottom_bm(int col){
  return (uint64_t(1) << bitmapDirectory(0, col));
}

bool board::checkIfWinner(){
  // NGL this is just kinda magic to me -Nick
  uint64_t m = m_position_bm & (m_position_bm >> (NUM_ROWS + 1));
  // Horizontal
  if (m & (m >> (2*(NUM_ROWS + 1))))
    return true;
  
  // Diagonal 1
  m = m_position_bm & (m_position_bm >> NUM_ROWS);
  if (m & (m >> (2*NUM_ROWS)))
    return true;

  // Diagonal 2
  m = m_position_bm & (m_position_bm >> NUM_ROWS+2);
  if (m & (m >> (2*NUM_ROWS+2)))
    return true;
  
  // Vertical
  m = m_position_bm & (m_position_bm >> 1);
  if (m & (m >> 2))
    return true;
  
  return false;
}