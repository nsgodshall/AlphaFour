#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <bitset>
#include <string>
#include <iostream>

#include "board.h"

class board;

const int NUM_ROWS = 6; // Number of rows in game
const int NUM_COLS = 7; // Number of cols in game

void visualizeBitmap(uint64_t bm);

// Plays a game from a given gamestring (e.g. "435126")
void playFromGameString(std::string *gs, board *b);
#endif // GLOBALS_INCLUDED
