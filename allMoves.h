#ifndef ALL_MOVES
#define ALL_MOVES

#include "bitboard.h"

extern const U64 bishopMoves[64][4];
extern const U64 rookMoves[64][4];
extern const U64 knightMoves[64];  
extern const U64 queenMoves[64][8];
extern const U64 kingMoves[64];
extern const U64 pawnCaptures[2][64];

extern short bishopMovesCount[64];// = {7,7,7,7,7,7,7,7, 7,9,9,9,9,9,9,7, 7,9,11,11,11,11,9,7, 7,9,11,13,13,11,9,7, 7,9,11,13,13,11,9,7, 7,9,11,11,11,11,9,7, 7,9,9,9,9,9,9,7, 7,7,7,7,7,7,7,7};
extern short queenMovesCount[64];// = {21,21,21,21,21,21,21,21, 21,23,23,23,23,23,23,21, 21,23,25,25,25,25,23,21, 21,23,25,27,27,25,23,21, 21,23,25,27,27,25,23,21, 21,23,25,25,25,25,23,21, 21,23,23,23,23,23,23,21, 21,21,21,21,21,21,21,21};
extern short kingMovesCount[64];// = {3,5,5,5,5,5,5,3, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 3,5,5,5,5,5,5,3};
extern short rookMovesCount[64];// = {14};
extern short knightMovesCount[64];// = {2,3,4,4,4,4,3,2, 3,4,6,6,6,6,4,3, 4,6,8,8,8,8,6,4, 4,6,8,8,8,8,6,4, 4,6,8,8,8,8,6,4, 4,6,8,8,8,8,6,4, 3,4,6,6,6,6,4,3, 2,3,4,4,4,4,3,2};

enum DIRECTION {N=0, NE, E, SE, S, SW, W, NW};
enum ROOK_DIRECTION {ROOK_N=0, ROOK_E, ROOK_S, ROOK_W};
enum BISHOP_DIRECTION {BISHOP_NE=0, BISHOP_SE, BISHOP_SW, BISHOP_NW};

extern DIRECTION bishopDirections[];// = {NE, SE, SW, NW};
extern DIRECTION rookDirections[];// = {N, E, S, W};
extern DIRECTION queenkDirections[];// = {N, NE, E, SE, S, SW, W, NW};
extern DIRECTION kingDirections[];// = {N, NE, E, SE, S, SW, W, NW};

#endif
