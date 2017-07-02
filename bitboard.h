#ifndef BITBOARD
#define BITBOARD

typedef unsigned int SQUARE_T;
typedef unsigned long long U64;


const U64 TWO_TO_63 = 9223372036854775808;
const U64 FULL_FIRST_RANK = 255;

const U64 RANKS_A_TO_G = 18374403900871474942;
const U64 RANKS_B_TO_H = 9187201950435737471;

inline U64 moveForward(const U64 sqrMask, const int delta, const bool side) {
	return side? sqrMask >> delta : sqrMask << delta;
}

inline U64 moveBackward(const U64 sqrMask, const int delta, const bool side) {
	return side? sqrMask << delta : sqrMask >> delta;
}

inline U64 moveBackward(const U64 sqrMask, const int deltaWhite, const int deltaBlack, const bool side) {
	return side? sqrMask << deltaBlack : sqrMask >> deltaWhite;
}

inline U64 moveForward(const U64 sqrMask, const int deltaWhite, const int deltaBlack, const bool side) {
	return side? sqrMask >> deltaBlack : sqrMask << deltaWhite;
}

inline SQUARE_T getFirstPiece2(const U64 &board) {
	return __builtin_ctzll(board);
}

inline U64 getFirstPieceMask(const U64 &board) {
	return board & (~(board - 1LL));
}

inline U64 getLastPieceMask(const U64 &board) {
	return TWO_TO_63 >> __builtin_clzll(board);
}

inline SQUARE_T getLastPiece2(const U64 &board) {
	return 63 - __builtin_clzll(board);
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


//inline U64 getPiecesOnRank2(U64 board, int rank) {
//	return board & (FULL_FIRST_RANK<<(rank*8));
//}

inline U64 getPiecesOnRank3(U64 board, int rankShift) {
	return board & (FULL_FIRST_RANK<<(rankShift));
}


#endif
