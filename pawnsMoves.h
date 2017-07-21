#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <iostream>
#include "chessboard.h"
#include "allMoves.h"
#include "move.h"

using namespace std;


inline int getFirstPawnRank(bool side);
inline int getPromotionRank(bool side);

inline void generatePawnMoves(const ChessBoard &board, const U64 pawns, MovesList &moveList);
inline void generateFirstRankPawnMoves(const ChessBoard &board, const U64 pawns, const U64 firstRankPawns, MovesList &moveList);
inline void generatePawnPromotions(const ChessBoard &board, const U64 pawns, MovesList &moveList);
inline void generatePawnCaptures(const ChessBoard &board, const U64 pawns, MovesList &moveList);



void generatePawnsMoves(const ChessBoard &board, MovesList &moveList) {

	
	int firstPawnRank = getFirstPawnRank(board.sideToMove);
	int promotionRank = getPromotionRank(board.sideToMove);
	
	U64 pawnsToMove = board.pieces2[board.sideToMove][PAWN];
	U64 firstRankPawns = getPiecesOnRank(pawnsToMove, firstPawnRank);
	U64 promotionPawns = getPiecesOnRank(pawnsToMove, promotionRank);

	if(promotionPawns) {
		generatePawnPromotions(board, promotionPawns, moveList);
		pawnsToMove -= promotionPawns;
	}

	generatePawnCaptures(board, pawnsToMove, moveList);

	//pawnsToMove^=firstRankPawns;

	generateFirstRankPawnMoves(board, pawnsToMove, firstRankPawns, moveList);
	//generatePawnMoves(board, pawnsToMove, moveList);

}

void generatePawnMoves(const ChessBoard &board, const U64 pawns, MovesList &moveList) {
	U64 move;

	U64 pawnsMoves = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;
	while(pawnsMoves) {
		move = popFirstPiece3(pawnsMoves);
		U64 from = moveBackward(move, 8, board.sideToMove);
		moveList.addMove(Move(PAWN, from, move));
	}
}

void generateFirstRankPawnMoves(const ChessBoard &board, const U64 pawns, const U64 firstRanksPawn, MovesList &moveList) {
	U64 move;

	U64 pawnMoves = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;
	//U64 pawnMovesTwoSqr = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;

	U64 moveByTwoSqr;// = moveForward(pawnMoves, 8, board.sideToMove) & ~board.allPieces;
	while(pawnMoves) {
		move = popFirstPiece3(pawnMoves);
		U64 from = moveBackward(move, 8, board.sideToMove);
		moveList.addMove(Move(PAWN, from, move));
		if(from & firstRanksPawn) {
			moveByTwoSqr = moveForward(move, 8, board.sideToMove);
			if(moveByTwoSqr & ~board.allPieces) {
				moveList.addMove(Move(PAWN, from, moveByTwoSqr, move));
			}
		}
	}

}

void generatePawnCaptures(const ChessBoard &board, const U64 pawns, MovesList &moveList) {

	U64 toCapture = board.pieces[!board.sideToMove] | board.enPessantSqr;
	U64 move;

	U64 pawnsToMove = getPawnAttacksLeft(pawns, board.sideToMove) & toCapture;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 9, 7, board.sideToMove);
		moveList.addCapture(Move(PAWN, from, move));
	}

	pawnsToMove = getPawnAttacksRight(pawns, board.sideToMove) & toCapture;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 7, 9, board.sideToMove);
		moveList.addCapture(Move(PAWN, from, move));
	}
}

 void generatePawnPromotions(const ChessBoard &board, const U64 pawns, MovesList &moveList) {

	U64 move;
	U64 pawnsToMove = moveForward(pawns, 8, board.sideToMove) & ~board.allPieces;
	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 8, board.sideToMove);

		moveList.addPromotion(Move(PAWN, from, move, QUEEN));
		moveList.addPromotion(Move(PAWN, from, move, ROOK));
		moveList.addPromotion(Move(PAWN, from, move, KNIGHT));
		moveList.addPromotion(Move(PAWN, from, move, BISHOP));
	}

	pawnsToMove = moveForward(pawns & RANKS_B_TO_H, 9, 7, board.sideToMove) & (board.pieces[!board.sideToMove]);

	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 9, 7, board.sideToMove);

		moveList.addCapture(Move(PAWN, from, move, QUEEN));
		moveList.addCapture(Move(PAWN, from, move, ROOK));
		moveList.addCapture(Move(PAWN, from, move, KNIGHT));
		moveList.addCapture(Move(PAWN, from, move, BISHOP));
	}

	pawnsToMove = moveForward(pawns & RANKS_A_TO_G, 7, 9, board.sideToMove) & (board.pieces[!board.sideToMove]);

	while(pawnsToMove) {
		move = popFirstPiece3(pawnsToMove);
		U64 from = moveBackward(move, 7, 9, board.sideToMove);

		moveList.addCapture(Move(PAWN, from, move, QUEEN));
		moveList.addCapture(Move(PAWN, from, move, ROOK));
		moveList.addCapture(Move(PAWN, from, move, KNIGHT));
		moveList.addCapture(Move(PAWN, from, move, BISHOP));
	}
}

#endif
