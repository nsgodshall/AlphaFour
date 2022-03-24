#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <stdint.h> // for declaring uint64_t

class Board {
public:
  Board();

  // Places a token in the requested column for the specified player. Returns
  // false if requested move is invalid
  bool addToken(int col);
  
  // Might not need this one
  // bool removeToken(int col);

  // Print a human readable version of the Board
  void displayHumanReadable();

  // Return TRUE if it is the first player's turn
  bool firstPlayerToMove();

  // Return 0 if there is no winner, -1 if the first player won, 1 if the second
  // player won.
  inline int getWinner() const { return m_winner; }

  inline int getNumMoves() const { return m_moves; }
private:
  uint64_t m_position_bm; // 64-bit variable storing location of the current
                          // player's tokens
  uint64_t m_nonEmpty_bm; // 64-bit variable identifying non-empty cells
  uint64_t m_bottom_bm;   // 64-bit variable identifying bottom of Board
  uint64_t m_key_bm;      // 64-bit variable that is sum of previous three and
                          // uniquely identifies gamestate
  int m_winner;

  int m_moves; // Keeps track of how many moves have been played

  // returns 1D index of gamestate bitmap given 2D coordinates (row 0, col 0)
  // identifies the bottom left location, returns -1 if an invalid coordinate is
  // given
  int bitmapDirectory(int row, int col);

  // returns true if a token can be placed in a column
  bool validColumn(int col);

  // return a bitmap with a 1 in the top row of the requested column
  uint64_t getTop_bm(int col);

  // return a bitmap with the bottom avaliable cell in the requested column
  uint64_t getBottom_bm(int col);

  // mutate the state of the m_winner
  void checkIfWinner(uint64_t pos);
};

#endif // BOARD_INCLUDED