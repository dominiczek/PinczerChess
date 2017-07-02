#ifndef ATTACKS
#define ATTACKS

#include "allMoves.h"

struct Attacks {
	U64 rightPawnAttacks = 0;
	U64 leftPawnAttacks = 0;

	U64 attacks[64] = {0};


//	U64 attackedBy[64] = {0};
};


//inline void removePieceAttacks(Attacks &attacks, SQUARE_T sqr) {
//	U64 oldAttacks = attacks.attacks[sqr];
//	
//	attacks.attacks[sqr] = 0;
//	
//	SQUARE_T attack;
//	
//	while(oldAttacks) {
//		attack=popFirstPiece2(&oldAttacks);
//		attacks.attackedBy[attack] ^=1LL<<sqr;
//	}
//	
//	U64 oldAttackers = attacks.attackedBy[sqr];
//	
//	SQUARE_T oldAttacker;
//	while(oldAttackers) {
//		oldAttacker=popFirstPiece2(&oldAttackers);
//		//re-generat attacks for oldAttacker 
//	}	
//};


inline void addPieceAttacks( Attacks &attacks, SQUARE_T sqr, U64 pieceAttacks) {
	attacks.attacks[sqr] = pieceAttacks;
	
//	SQUARE_T attack;
//	
//	U64 atttackMask = (1LL<<sqr);
//	
//	while(pieceAttacks) {
//		attack=popFirstPiece2(&pieceAttacks);
//		attacks.attackedBy[attack] |= atttackMask;
//	}
};

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


inline U64 getRookAttacks(const U64 allPieces, const SQUARE_T sqr) {
	const U64 (* moves) = rookMoves[sqr];
		
	U64 legalMoves = getAttacksOnPositiveDirection(allPieces, moves[ROOK_N]);

	legalMoves|=getAttacksOnPositiveDirection(allPieces, moves[ROOK_E]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[ROOK_S]);
	legalMoves|=getAttacksOnNegativeDirection(allPieces, moves[ROOK_W]);

	return legalMoves;
}

inline U64 getKnightAttacks(const SQUARE_T sqr) {
	return knightMoves[sqr];
}

inline U64 getKingAttacks(const SQUARE_T sqr) {
	return kingMoves[sqr];
}

inline void addPawnsAttacks( Attacks &attacks, U64 pawnsToMove, bool sideToMove) {
	attacks.rightPawnAttacks = getPawnAttacksRight(pawnsToMove, sideToMove);
	attacks.leftPawnAttacks = getPawnAttacksLeft(pawnsToMove, sideToMove);
}

#endif

