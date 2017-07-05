#ifndef ATTACKS
#define ATTACKS

#include "allMoves.h"
#include "constants.h"

inline U64 getAttacksOnPositiveDirection(const U64 allPieces, const U64 movesOnDir) {
	U64 potentialBlockers = movesOnDir & allPieces;

	if(potentialBlockers) {
		U64 blocker = getFirstPieceMask(potentialBlockers);
		U64 allowedSquares = blocker - 1;
		U64 legalMoves = movesOnDir & allowedSquares;

		legalMoves|=blocker;

		return legalMoves;
	}
	return movesOnDir;
};

inline U64 getAttacksOnNegativeDirection(const U64 allPieces, const U64 movesOnDir) {
	U64 potentialBlockers = movesOnDir & allPieces;
	
	if(potentialBlockers) {
		U64 blocker = getLastPieceMask(potentialBlockers);
		U64 allowedSquares = ~(blocker - 1);
		U64 legalMoves = movesOnDir & allowedSquares;

		return legalMoves;
	}
	return movesOnDir;
};

inline U64 getPawnAttacks(const U64 pawns, const bool side) {

	U64 captures = moveForward(pawns & RANKS_A_TO_G, 7 ,9, side);
	captures|=moveForward(pawns & RANKS_B_TO_H, 9, 7, side);
	return captures;
}

inline U64 getPawnAttacksRight(const U64 pawns, const bool side) {
	return moveForward(pawns & RANKS_A_TO_G, 7, 9, side);
}

inline U64 getPawnAttacksLeft(const U64 pawns, const bool side) {
	return moveForward(pawns & RANKS_B_TO_H, 9, 7, side);;
}

inline U64 getBishopAttacks(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = bishopMoves[sqr];
	
	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, moves[BISHOP_NE]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[BISHOP_SE]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[BISHOP_SW]);
	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[BISHOP_NW]);
	
	return legalMoves;
}

inline U64 getQueenAttacks(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = queenMoves[sqr];
	
	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, moves[N]);
	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[NE]);
	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[E]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[SE]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[S]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[SW]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[W]);
	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[NW]);

	return legalMoves;
};

const U64 attackN = 0x0101010101010100;
const U64 attackW = 0x7F00000000000000;
const U64 attackS = 0x0080808080808080;
const U64 attackE = 254;

inline U64 getRookAttacks(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = rookMoves[sqr];

	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, moves[ROOK_N]);

	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[ROOK_E]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[ROOK_S]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[ROOK_W]);

	return legalMoves;
}

//inline U64 getRookAttacks(const U64 allPieces, const SQUARE_T sqr) {
//	const U64 (* moves) = rookMoves[sqr];
//
//	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, 0x0101010101010100<<sqr);
//
//	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[ROOK_E]);
//	legalMoves|=getAttacksOnNegativeDirection(allPieces, 0x0080808080808080>>(63-sqr));
//	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[ROOK_W]);
//
//	return legalMoves;
//}

//inline U64 getRookAttacks(const U64 allPieces, const SQUARE_T sqr) {
//
//	const U64 attackN = 0x0101010101010100;
//	const U64 attackW = 0x7F00000000000000;
//	const U64 attackS = 0x0080808080808080;
//	const U64 attackE = 254;
//	//const U64 (* moves) = rookMoves[sqr];
//
//	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, attackN<<sqr);
//
//	legalMoves|=getAttacksOnPositiveDirection(allPieces, attackE<<sqr);
//	legalMoves|=getAttacksOnNegativeDirection(allPieces, attackS>>(63-sqr));
//	legalMoves|=getAttacksOnNegativeDirection(allPieces, attackW>>(63-sqr));
//
//	return legalMoves;
//}

inline U64 getKnightAttacks(const SQUARE_T sqr) {
	return knightMoves[sqr];
}

inline U64 getKingAttacks(const SQUARE_T sqr) {
	return kingMoves[sqr];
}

#endif

