#include "board.h"

board::board(){
    //initialize the bottom bitmap by changing the every spot in the bottom row to be 1
    for (int c = 0; c < NUM_COLS; c++){
        std::cout << bitmap_directory(0, c) << std::endl;
    }
}

int board::bitmap_directory(int row, int col){
    // ensure row index is valid
    if (row < 0 || row >= NUM_ROWS + 1)
        return -1;

    // ensure col index is valid
    else if (col < 0 || col >= NUM_COLS)
        return -1;

    // return 1D index
    else 
        return col*(NUM_ROWS + 1) + row;
}