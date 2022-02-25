#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <string>
#include <iostream>

class Board;

const int NUM_ROWS = 6; // Number of rows in game
const int NUM_COLS = 7; // Number of cols in game

void visualizeBitmap(uint64_t bm);

// Plays a game from a given gamestring (e.g. "435126")
void playFromGameString(std::string *gs, Board *b, bool verbose);

bool getBit(uint64_t bm, int n);
#endif // GLOBALS_INCLUDED