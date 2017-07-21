#ifndef ALL_MOVES
#define ALL_MOVES

#include "bitboard.h"
#include "constants.h"

extern const U64 knightMoves[64];  
extern const U64 queenMoves[64][8];
extern const U64 kingMoves[64];

enum DIRECTION {N=0, NE, E, SE, S, SW, W, NW};


#endif
