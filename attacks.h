#ifndef ATTACKS
#define ATTACKS

#include "allMoves.h"
#include "constants.h"

inline U64 getQueenAttacks(const U64 allPieces, const SQUARE_T sqr);

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
//TEST :)



inline bool checkCaptureOnPositiveDirection(const U64 pieces, const U64 movesOnDir, const U64 attackers) {

	if(movesOnDir & attackers) {
		U64 potentialBlockers = movesOnDir & pieces;
		return potentialBlockers ? (attackers & getFirstPieceMask(potentialBlockers)): 0;
	}
	return false;
};

inline bool checkCaptureOnNegativeDirection(const U64 allPieces, const U64 movesOnDir, const U64 attackers) {

	if(movesOnDir & attackers) {
		U64 potentialBlockers = movesOnDir & allPieces;
		return potentialBlockers ? attackers & getLastPieceMask(potentialBlockers): 0;
	}
	return false;
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


template <bool sideToMove>
inline U64 getPawnAttacks(const U64 pawns);

template <>
inline U64 getPawnAttacks<WHITE>(const U64 pawns) {

	U64 captures =  (pawns & RANKS_A_TO_G) << 7;
	captures |= (pawns & RANKS_B_TO_H) <<9;
	return captures;
}

template <>
inline U64 getPawnAttacks<BLACK>(const U64 pawns) {

	U64 captures =  (pawns & RANKS_A_TO_G) >> 9;
	captures |= (pawns & RANKS_B_TO_H) >>7;
	return captures;
}

template <bool sideToMove>
inline U64 getPawnAttacksLeft(const U64 pawns);

template <>
inline U64 getPawnAttacksLeft<WHITE>(const U64 pawns) {
	return (pawns & RANKS_B_TO_H) <<9;
}

template <>
inline U64 getPawnAttacksLeft<BLACK>(const U64 pawns) {
	return (pawns & RANKS_B_TO_H) >>7;
}

template <bool sideToMove>
inline U64 getPawnBackwardMoveLeft(const U64 pawn);

template <>
inline U64 getPawnBackwardMoveLeft<WHITE>(const U64 pawn) {
	return pawn >>9;
}

template <>
inline U64 getPawnBackwardMoveLeft<BLACK>(const U64 pawn) {
	return pawn <<7;
}

template <bool sideToMove>
inline U64 getPawnAttacksRight(const U64 pawns);

template <>
inline U64 getPawnAttacksRight<WHITE>(const U64 pawns) {
	return (pawns & RANKS_A_TO_G) << 7;
}

template <>
inline U64 getPawnAttacksRight<BLACK>(const U64 pawns) {
	return (pawns & RANKS_A_TO_G) >> 9;
}

template <bool sideToMove>
inline U64 getPawnBackwardMoveRight(const U64 pawn);

template <>
inline U64 getPawnBackwardMoveRight<WHITE>(const U64 pawn) {
	return pawn >> 7;
}

template <>
inline U64 getPawnBackwardMoveRight<BLACK>(const U64 pawn) {
	return pawn << 9;
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

inline U64 getKnightAttacks(const SQUARE_T sqr) {
	return knightMoves[sqr];
}

inline U64 getKingAttacks(const SQUARE_T sqr) {
	return kingMoves[sqr];
}

#endif

