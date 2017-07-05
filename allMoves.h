#ifndef ALL_MOVES
#define ALL_MOVES

#include "bitboard.h"
#include "constants.h"

extern const U64 bishopMoves[64][4];
extern const U64 rookMoves[64][4];
extern const U64 knightMoves[64];  
extern const U64 queenMoves[64][8];
extern const U64 kingMoves[64];


enum DIRECTION {N=0, NE, E, SE, S, SW, W, NW};
enum ROOK_DIRECTION {ROOK_N=0, ROOK_E, ROOK_S, ROOK_W};
enum BISHOP_DIRECTION {BISHOP_NE=0, BISHOP_SE, BISHOP_SW, BISHOP_NW};


#endif
