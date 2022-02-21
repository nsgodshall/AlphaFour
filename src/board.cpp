#include "board.h"

board::board() : m_nonEmpty_bm(0) {
  // initialize the bottom bitmap by changing the every spot in the bottom row
  // to be 1
  for (int c = 0; c < NUM_COLS; c++) {
    m_bottom_bm |= uint64_t(1) << bitmapDirectory(
                       0, c); // binary number = (binary number OR [temp
                              // variable left shifted n places])
  }

  // qDEBUGGING BELOW
  validColumn(6);
  // DEBUGGING ABOVE
}

// TODO: Check if the requested column is full.
bool board::addToken(int col, bool firstPlayer) {

  // Check if requested column is a valid move
  if (col < 0 || col >= NUM_COLS)
    return false;

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

  // Create a bitmap where the toprow in column col is '1'
  uint64_t top_bm = (uint64_t(1) << (bitmapDirectory(NUM_ROWS - 1, col)));

  // AND the new top row bitmap with the non empty bitmap to see if the
  // requested column has an empty space avaliable
  if (((top_bm & m_nonEmpty_bm) >> bitmapDirectory(NUM_ROWS - 1, col)) == 0)
    return false;

  // If it passes these tests, then a token may be placed in the requested
  // column
  return true;
}