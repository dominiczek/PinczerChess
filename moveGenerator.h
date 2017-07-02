#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <iostream>
#include "chessboard.h"
#include "allMoves.h"
#include "move.h"

using namespace std;


inline void generateMovesAndCaptures(const ChessBoard &board, const U64 sqrMask, const int piece, const U64 attacks, MovesList &moveList);
inline int getFirstPawnRank(bool side);
inline int getPromotionRank(bool side);

inline void generatePawnMoves(const ChessBoard &board, const U64 pawns, MovesList &moveList);
inline void generateFirstRankPawnMoves(const ChessBoard &board, const U64 pawns, MovesList &moveList);
inline void generatePawnPromotions(const ChessBoard &board, const U64 pawns, MovesList &moveList);
inline void generatePawnCaptures(const ChessBoard &board, const U64 pawns, MovesList &moveList);



void generateAllMoves(const ChessBoard &board, MovesList &moveList) {
	
	SQUARE_T toMove;
	U64 attacks;

	U64 sqrMask;
	
	int firstPawnRank = getFirstPawnRank(board.sideToMove);
	int promotionRank = getPromotionRank(board.sideToMove);
	
	U64 pawnsToMove = board.pieces2[board.sideToMove][PAWN];
	U64 firstRankPawns = getPiecesOnRank3(pawnsToMove, firstPawnRank);
	U64 promotionPawns = getPiecesOnRank3(pawnsToMove, promotionRank);

	pawnsToMove^=promotionPawns;

	generatePawnCaptures(board, pawnsToMove, moveList);

	pawnsToMove^=firstRankPawns;

	generateFirstRankPawnMoves(board, firstRankPawns, moveList);
	generatePawnMoves(board, pawnsToMove, moveList);
	generatePawnPromotions(board, promotionPawns, moveList);
	
	U64 bishopsToMove = board.pieces2[board.sideToMove][BISHOP];
	while(bishopsToMove) {
		sqrMask=popFirstPiece3(bishopsToMove, toMove);
		//attacks = getBishopAttacks(board.allPieces, toMove);
		attacks = board.attacks.attacks[toMove];
		generateMovesAndCaptures(board, sqrMask, BISHOP, attacks, moveList);
	}

	U64 rooksToMove = board.pieces2[board.sideToMove][ROOK];
	while(rooksToMove) {
		sqrMask=popFirstPiece3(rooksToMove, toMove);
		//attacks = getRookAttacks(board.allPieces, toMove);
		attacks = board.attacks.attacks[toMove];
		generateMovesAndCaptures(board, sqrMask, ROOK, attacks, moveList);
	}

	U64 queensToMove = board.pieces2[board.sideToMove][QUEEN];
	while(queensToMove) {
		sqrMask=popFirstPiece3(queensToMove, toMove);
		//attacks = getQueenAttacks(board.allPieces, toMove);
		attacks = board.attacks.attacks[toMove];
		generateMovesAndCaptures(board, sqrMask, QUEEN, attacks, moveList);
	}

	U64 knightsToMove = board.pieces2[board.sideToMove][KNIGHT];
	while(knightsToMove) {
		sqrMask=popFirstPiece3(knightsToMove, toMove);
		//attacks = getKnightAttacks(toMove);
		attacks = board.attacks.attacks[toMove];
		generateMovesAndCaptures(board, sqrMask, KNIGHT, attacks, moveList);
	}

	U64 kingToMove = board.pieces2[board.sideToMove][KING];
	toMove=getFirstPiece2(kingToMove);

	attacks = getKingAttacks(toMove);
	//attacks = board.attacks.attacks[toMove];
	generateMovesAndCaptures(board, kingToMove, KING, attacks, moveList);

	//return moveList - move_list_head;
}

inline U64 getPawnMoves(const U64 sqrMask, const int delta, const bool side) {
	return side? sqrMask >> delta : sqrMask << delta;
}

inline int getFirstPawnRank(bool side) {
	return side*40 + 8;
}

inline int getPromotionRank(bool side) {
	return !side * 40 + 8;
}

inline void generatePawnMoves(const ChessBoard &board, const U64 pawns, MovesList &moveList) {

	U64 move;

	U64 pawnsToMove = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 8, board.sideToMove);
		addMove(moveList, createMove(PAWN, from, move));
	}
}

inline void generateFirstRankPawnMoves(const ChessBoard &board, const U64 pawns, MovesList &moveList) {

	U64 move;

	U64 pawnMoves = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;
	U64 moveByTwoSqr;// = moveForward(pawnMoves, 8, board.sideToMove) & ~board.allPieces;
	while(pawnMoves) {
		move = popFirstPiece3(pawnMoves);
		U64 from = moveBackward(move, 8, board.sideToMove);
		addMove(moveList, createMove(PAWN, from, move));
		moveByTwoSqr = moveForward(move, 8, board.sideToMove);
		if(moveByTwoSqr & ~board.allPieces) {
			addMove(moveList, createMove(PAWN, from, moveByTwoSqr, move));
		}
	}

}

inline void generatePawnCaptures(const ChessBoard &board, const U64 pawns, MovesList &moveList) {

	U64 toCapture = board.pieces[!board.sideToMove] | board.enPessantSqr;
	U64 move;

	U64 pawnsToMove = board.attacks.leftPawnAttacks & toCapture;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 9, 7, board.sideToMove);
		addCapture(moveList, createMove(PAWN, from, move));
	}

	pawnsToMove = board.attacks.rightPawnAttacks & toCapture;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 7, 9, board.sideToMove);
		addCapture(moveList, createMove(PAWN, from, move));
	}
}

inline void generatePawnPromotions(const ChessBoard &board, const U64 pawns, MovesList &moveList) {

	U64 move;

	if(!pawns) {
		return;
	}

	U64 pawnsToMove = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 8, board.sideToMove);

		addMove(moveList, createPromotionMove(PAWN, from, move, QUEEN));
		addMove(moveList, createPromotionMove(PAWN, from, move, ROOK));
		addMove(moveList, createPromotionMove(PAWN, from, move, KNIGHT));
		addMove(moveList, createPromotionMove(PAWN, from, move, BISHOP));
	}

	pawnsToMove = moveForward(pawns & RANKS_B_TO_H, 9, 7, board.sideToMove) & (board.pieces[!board.sideToMove]);

	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 9, 7, board.sideToMove);

		addCapture(moveList, createPromotionMove(PAWN, from, move, QUEEN));
		addCapture(moveList, createPromotionMove(PAWN, from, move, ROOK));
		addCapture(moveList, createPromotionMove(PAWN, from, move, KNIGHT));
		addCapture(moveList, createPromotionMove(PAWN, from, move, BISHOP));
	}

	pawnsToMove = moveForward(pawns & RANKS_A_TO_G, 7, 9, board.sideToMove) & (board.pieces[!board.sideToMove]);

	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 7, 9, board.sideToMove);

		addCapture(moveList, createPromotionMove(PAWN, from, move, QUEEN));
		addCapture(moveList, createPromotionMove(PAWN, from, move, ROOK));
		addCapture(moveList, createPromotionMove(PAWN, from, move, KNIGHT));
		addCapture(moveList, createPromotionMove(PAWN, from, move, BISHOP));
	}
}



inline void generateMovesAndCaptures(const ChessBoard &board, const U64 sqrMask, const int piece, const U64 attacks, MovesList &moveList) {
	U64 legalMoves = attacks & (attacks^board.allPieces);;
	U64 captures = attacks & board.pieces[!board.sideToMove];

	U64 to;
	while(captures) {
		to = popFirstPiece3(captures);
		addCapture(moveList, createMove(piece, sqrMask, to));
	}
	while(legalMoves) {
		to = popFirstPiece3(legalMoves);
		addMove(moveList, createMove(piece, sqrMask, to));
	}

//	U64 legalMoves = attacks & ~board.pieces[board.sideToMove];
//	while(legalMoves) {
//		U64 to = popFirstPiece3(legalMoves);
//
//		addMove(moveList, createMove(piece, sqrMask, to,  to & board.pieces[!board.sideToMove]));
////		*moveList++ =createMove(piece, sqrMask, to,  to & board.pieces[!board.sideToMove]) ;
//	}

	//return moveList;
}

#endif
