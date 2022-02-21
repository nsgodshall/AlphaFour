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
