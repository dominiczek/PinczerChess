#ifndef ATTACKS
#define ATTACKS

#include "allMoves.h"
#include "constants.h"

inline U64 getAttacksOnPositiveDirection(const U64 allPieces, const U64 movesOnDir) {
	U64 potentialBlockers = movesOnDir & allPieces;

//	return movesOnDir & (potentialBlockers^(potentialBlockers-1LL));
//
//
//	if(potentialBlockers) {
//		return movesOnDir & (potentialBlockers^(potentialBlockers-1LL));
//	}

	if(potentialBlockers) {
		U64 blocker = getFirstPieceMask(potentialBlockers);
		U64 allowedSquares = blocker - 1;
		U64 legalMoves = movesOnDir & allowedSquares;

		legalMoves|=blocker;

		return legalMoves;
		//return movesOnDir & (potentialBlockers^(potentialBlockers-1));

	}
	return movesOnDir;
};

inline U64 getCaptureOnPositiveDirection(const U64 allPieces, const U64 movesOnDir) {
	U64 potentialBlockers = movesOnDir & allPieces;

	if(potentialBlockers) {
		return getFirstPieceMask(potentialBlockers);
	}
	return 0;
};

inline U64 getCaptureOnNegativeDirection(const U64 allPieces, const U64 movesOnDir) {
	U64 potentialBlockers = movesOnDir & allPieces;

	if(potentialBlockers) {
		return getLastPieceMask(potentialBlockers);
	}
	return 0;
};

//inline U64 getAttacksOnPositiveDirection(const U64 allPieces, const U64 movesOnDir) {
//	U64 potentialBlockers = movesOnDir & allPieces;
//	return potentialBlockers ? (movesOnDir & (getFirstPieceMask(potentialBlockers) - 1))|getFirstPieceMask(potentialBlockers) : movesOnDir;
//};

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
	const U64 (* moves) = queenMoves[sqr];
	
	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, moves[NE]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[SE]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[SW]);
	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[NW]);
	
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

inline U64 getRookAttacks(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = queenMoves[sqr];

	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, moves[N]);
	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[E]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[S]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[W]);

	return legalMoves;
}


inline U64 getBishopCaptures(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = queenMoves[sqr];

	U64 legalMoves = getCaptureOnPositiveDirection(allPieces, moves[NE]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[SE]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[SW]);
	legalMoves|=getCaptureOnPositiveDirection(allPieces, moves[NW]);

	return legalMoves;
}

inline U64 getQueenCaptures(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = queenMoves[sqr];

	U64 legalMoves = getCaptureOnPositiveDirection(allPieces, moves[N]);
	legalMoves|=getCaptureOnPositiveDirection(allPieces, moves[NE]);
	legalMoves|=getCaptureOnPositiveDirection(allPieces, moves[E]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[SE]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[S]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[SW]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[W]);
	legalMoves|=getCaptureOnPositiveDirection(allPieces, moves[NW]);

	return legalMoves;
};

inline U64 getRookCaptures(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = queenMoves[sqr];

	U64 legalMoves = getCaptureOnPositiveDirection(allPieces, moves[N]);
	legalMoves|=getCaptureOnPositiveDirection(allPieces, moves[E]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[S]);
	legalMoves|=getCaptureOnNegativeDirection(allPieces, moves[W]);

	return legalMoves;
}

inline U64 getKnightAttacks(const SQUARE_T sqr) {
	return knightMoves[sqr];
}

inline U64 getKingAttacks(const SQUARE_T sqr) {
	return kingMoves[sqr];
}

#endif

