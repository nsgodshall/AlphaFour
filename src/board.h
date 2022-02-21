#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <stdint.h> // for declaring uint64_t

#include "globals.h"

class board {
public:
  board();

  // Places a token in the requested column for the specified player. Returns
  // false if requested move is invalid
  bool addToken(int col, bool firstPlayer);

private:
  uint64_t
      m_position_bm; // 64-bit variable storing location of player 2's tokens
  uint64_t m_nonEmpty_bm; // 64-bit variable identifying non-empty cells
  uint64_t m_bottom_bm;   // 64-bit variable identifying bottom of board
  uint64_t m_key_bm;      // 64-bit variable that is sum of previous three and
                          // uniquely identifies gamestate

  // returns 1D index of gamestate bitmap given 2D coordinates (row 0, col 0)
  // identifies the bottom left location, returns -1 if an invalid coordinate is
  // given
  int bitmapDirectory(int row, int col);

  // returns true if a token can be placed in a column
  bool validColumn(int col);
};

#endif // BOARD_INCLUDED