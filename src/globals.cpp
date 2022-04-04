#include "globals.h"

void visualizeBitmap(uint64_t bm) {
  for (int r = NUM_ROWS; r >= 0; r--) {
    for (int c = 0; c < NUM_COLS; c++) {
      int linear_index = c * (NUM_ROWS + 1) + r;

      if (((bm >> linear_index) & uint64_t(1)) == 1)
        std::cout << 1;
      else
        std::cout << 0;
      std::cout << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void playFromGameString(std::string *gs, Board *b, bool verbose) {
  // Attempt to place a token for each number in the gamestring
  for (int i = 0; i < gs->length(); i++) {
    // the specific char must be cast to a int literal
    int col = int(gs->at(i) - '0');
    b->addToken(col);
    if (verbose) {
      b->displayHumanReadable();
    }
    switch (b->getWinner()) {
    case 0:
      std::cout << "There is no winner" << std::endl;
      break;
    case -1:
      std::cout << "Player X has won" << std::endl;
      break;
    case 1:
      std::cout << "Player O has won" << std::endl;
      break;
    }
    std::cout << std::endl;
  }

  return;
}

bool getBit(uint64_t bm, int n) { return ((bm >> n) & 1); }

void benchmark(){
  Board b;
  RoboPlayer rp1;
  auto start = std::chrono::high_resolution_clock::now(); // START DEBUG TIMER
  for (int d = 0; d < NUM_COLS*NUM_ROWS; d++){
    rp1.getMoveTime(&b, d);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "DEPTH: " << d << ", DURATION: " << duration.count()/ 1000000.0 << " seconds"
           << std::endl;
    if (duration.count() > 10000000){
      break;
    }
  }

}