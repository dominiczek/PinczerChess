#ifndef BITBOARD
#define BITBOARD

#include "constants.h"

const U64 TWO_TO_63 = 9223372036854775808;
const U64 FULL_FIRST_RANK = 255;

const U64 RANKS_A_TO_G = 18374403900871474942;
const U64 RANKS_B_TO_H = 9187201950435737471;

const U64 WHITE_FIRST_RANK_PAWNS = FULL_FIRST_RANK << 8;
const U64 BLACK_FIRST_RANK_PAWNS = FULL_FIRST_RANK << 48;

const U64 WHITE_PROMOTION_RANK_PAWNS = FULL_FIRST_RANK << 48;
const U64 BLACK_PROMOTION_RANK_PAWNS = FULL_FIRST_RANK << 8;

template <bool sideToMove>
inline U64 moveForward(const U64 sqrMask, const int delta);

template <>
inline U64 moveForward<BLACK>(const U64 sqrMask, const int delta) {
	return sqrMask >> delta;
}

template <>
inline U64 moveForward<WHITE>(const U64 sqrMask, const int delta) {
	return sqrMask << delta;
}

template <bool sideToMove>
inline U64 moveBackward(const U64 sqrMask, const int delta);

template <>
inline U64 moveBackward<BLACK>(const U64 sqrMask, const int delta) {
	return sqrMask << delta;
}

template <>
inline U64 moveBackward<WHITE>(const U64 sqrMask, const int delta) {
	return sqrMask >> delta;
}

inline U64 moveForward(const U64 sqrMask, const int delta, const bool side) {
	return side? sqrMask >> delta : sqrMask << delta;
}

inline SQUARE_T getFirstPiece2(const U64 &board) {
	return __builtin_ctzll(board);
}

inline U64 getFirstPieceMask(const U64 &board) {
	return board & (~(board - 1LL));
//	return board & (-board);
}

inline U64 getLastPieceMask(const U64 &board) {
	return TWO_TO_63 >> __builtin_clzll(board);
}


inline SQUARE_T popFirstPiece2(U64 *board) {
	SQUARE_T pos = __builtin_ctzll(*board);
	*board &= *board - 1LL;
	return pos;
}

inline U64 popFirstPiece3(U64 &board) {
	U64 old = board;
	board &= board - 1LL;
	return old - board;
}

inline U64 popFirstPiece3(U64 &board, SQUARE_T &pos) {
	pos = __builtin_ctzll(board);
	U64 old = board;
	board &= board - 1LL;
	return old - board;
}

inline U64 getFirstPiece3(const U64 board, SQUARE_T &pos) {
	pos = __builtin_ctzll(board);
	return board & (~(board - 1LL));
}



#endif
