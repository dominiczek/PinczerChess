#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>

#include "attacks.h"
#include "move.h"

using namespace std;



class ChessBoard {
	
public:
	U64 allPieces;
	U64 pieces[2];
	
	U64 pieces2[2][6];
	bool sideToMove;

	bool castleKingW;
	bool castleQueenW;
	bool castleKingB;
	bool castleQueenB;
	
	U64 enPessantSqr;
	U64 enPessantPawn;


	inline ChessBoard makeMove(const Move& move) const {

		ChessBoard copy = createCopy(*this);

		copy.removePiece(move.maskFrom, move.piece, sideToMove);
		copy.addPiece(move.maskTo, move.piece, sideToMove);

		copy.enPessantSqr = move.enPessant;
		copy.enPessantPawn = move.maskTo;

		copy.sideToMove = !sideToMove;

		return copy;
	}

	inline ChessBoard makePromotion(const Move& move) const {

		ChessBoard copy = createCopy(*this);

		copy.removePiece(move.maskFrom, PAWN, sideToMove);
		copy.addPiece(move.maskTo, move.promotion, sideToMove);

		copy.enPessantSqr = 0;

		copy.sideToMove = !sideToMove;

		return copy;
	}

	inline ChessBoard makeCapture(const Move& move) const {

		ChessBoard copy = createCopy(*this);


		copy.take(move.maskTo, !sideToMove);

		PIECE_T pieceToAdd = move.promotion ? move.promotion : move.piece;

		copy.conditionalRemovePiece(enPessantPawn, PAWN, !sideToMove, move.piece == PAWN && move.maskTo == enPessantSqr);
		copy.removePiece(move.maskFrom, move.piece, sideToMove);
		copy.addPiece(move.maskTo, pieceToAdd, sideToMove);

		copy.enPessantSqr = 0;

		copy.sideToMove = !sideToMove;

		return copy;
	}

private:

	inline ChessBoard createCopy(const ChessBoard &board) const {
		ChessBoard copy;
		copy.allPieces = allPieces;

		copy.pieces[WHITE] = pieces[WHITE];
		copy.pieces[BLACK] = pieces[BLACK];

		for(int i=0; i<6;i++) {
			copy.pieces2[WHITE][i] = pieces2[WHITE][i];
		}
		for(int i=0; i<6;i++) {
			copy.pieces2[BLACK][i] = pieces2[BLACK][i];
		}

		return copy;
	}

	inline void addPiece(const U64 mask, const PIECE_T piece,const bool side) {
		pieces[side] += mask;
		allPieces += mask;
		pieces2[side][piece] += mask;
	}

	inline void removePiece(const U64 mask, const PIECE_T piece, const bool side) {
		pieces[side] -= mask;
		allPieces -= mask;
		pieces2[side][piece] -= mask;
	}

	inline void conditionalRemovePiece(U64 mask, const PIECE_T piece, const bool side, bool condition) {
		mask*=condition;
		pieces[side] -= mask;
		allPieces -= mask;
		pieces2[side][piece] -= mask;
	}

	inline void take(U64 mask, bool side) {
		allPieces &= ~mask;
		pieces[side] &= allPieces;
		pieces2[side][QUEEN] &= allPieces;
		pieces2[side][ROOK] &= allPieces;
		pieces2[side][BISHOP] &= allPieces;
		pieces2[side][KNIGHT] &= allPieces;
		pieces2[side][PAWN] &= allPieces;
	}

};

void printChessBoard(const ChessBoard &chessBoard);
void printBitMap(U64 bitMap, char c);

inline ChessBoard createNewBoard() {
	ChessBoard board;
	board.allPieces = 0;
	
	for(int i=0;i<2;i++) {
		board.pieces[i] = 0;
		board.pieces2[i][KING] = 0;
		board.pieces2[i][QUEEN] = 0;
		board.pieces2[i][KNIGHT] = 0;
		board.pieces2[i][ROOK] = 0;
		board.pieces2[i][BISHOP] = 0;
		board.pieces2[i][PAWN] = 0;
	}
	
	board.sideToMove = 0;
	
	board.enPessantPawn = 0;
	board.enPessantSqr = 0;
	
	return board;
}

void addNewPawn(ChessBoard &board, int square, bool side);
void addNewKnight(ChessBoard &board, int square, bool side);
void addNewBishop(ChessBoard &board, int square, bool side);
void addNewRook(ChessBoard &board, int square, bool side);
void addNewQueen(ChessBoard &board, int square, bool side);
void addNewKing(ChessBoard &board, int square, bool side);


inline void generateMovesAndCaptures(const ChessBoard &board, const U64 sqrMask, const int piece, const U64 attacks, MovesList &moveList) {
	if(!attacks) {
		return;
	}

	U64 legalMoves = attacks & (attacks^board.allPieces);;
	U64 captures = attacks & board.pieces[!board.sideToMove];

	U64 to;
	while(captures) {
		to = popFirstPiece3(captures);
		moveList.addCapture(Move(piece, sqrMask, to));
	}
	while(legalMoves) {
		to = popFirstPiece3(legalMoves);
		moveList.addMove(Move(piece, sqrMask, to));
	}
}


inline bool generateAttacksMap(const ChessBoard& board, MovesList& movesList) {
	
	U64 opositeKing = board.pieces2[!board.sideToMove][KING];
	
	SQUARE_T toMove;
	U64 attacks;
	U64 sqrMask;

	bool sideToMove = board.sideToMove;
	
	U64 queensToMove = board.pieces2[sideToMove][QUEEN];
	while(queensToMove) {
		sqrMask=popFirstPiece3(queensToMove, toMove);
		attacks = getQueenAttacks(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}

		generateMovesAndCaptures(board, sqrMask, QUEEN, attacks, movesList);
	}
	
	U64 bishopsToMove = board.pieces2[sideToMove][BISHOP];
	while(bishopsToMove) {
		sqrMask=popFirstPiece3(bishopsToMove, toMove);
		attacks = getBishopAttacks(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
		generateMovesAndCaptures(board, sqrMask, BISHOP, attacks, movesList);
	}

	U64 rooksToMove = board.pieces2[sideToMove][ROOK];
	while(rooksToMove) {
		sqrMask=popFirstPiece3(rooksToMove, toMove);
		attacks = getRookAttacks(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
		generateMovesAndCaptures(board, sqrMask, ROOK, attacks, movesList);
	}

	U64 knightsToMove = board.pieces2[sideToMove][KNIGHT];
	while(knightsToMove) {
		sqrMask=popFirstPiece3(knightsToMove, toMove);
		attacks = getKnightAttacks(toMove);
		if(attacks & opositeKing) {
			return true;
		}
		generateMovesAndCaptures(board, sqrMask, KNIGHT, attacks, movesList);
	}

	U64 pawnsToMove = board.pieces2[sideToMove][PAWN];
	attacks = getPawnAttacks(pawnsToMove, sideToMove);

	if(attacks & opositeKing) {
//		printChessBoard(board);
		return true;
	}

	U64 kingToMove = board.pieces2[sideToMove][KING];
	toMove=getFirstPiece2(kingToMove);

	attacks = getKingAttacks(toMove);
	
	if(attacks&opositeKing) {
		return true;
	}

	generateMovesAndCaptures(board, kingToMove, KING, attacks, movesList);

	return false;
}



inline bool checkAttacks(const ChessBoard& board, MovesList& movesList) {

	U64 opositeKing = board.pieces2[!board.sideToMove][KING];

	SQUARE_T toMove;
	U64 attacks;

	bool sideToMove = board.sideToMove;

	U64 queensToMove = board.pieces2[sideToMove][QUEEN];
	while(queensToMove) {
		toMove=popFirstPiece2(&queensToMove);
		attacks = getQueenCaptures(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
	}

	U64 bishopsToMove = board.pieces2[sideToMove][BISHOP];
	while(bishopsToMove) {
		toMove=popFirstPiece2(&bishopsToMove);
		attacks = getBishopCaptures(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
	}

	U64 rooksToMove = board.pieces2[sideToMove][ROOK];
	while(rooksToMove) {
		toMove=popFirstPiece2(&rooksToMove);
		attacks = getRookCaptures(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
	}

	U64 knightsToMove = board.pieces2[sideToMove][KNIGHT];
	while(knightsToMove) {
		toMove=popFirstPiece2(&knightsToMove);
		attacks = getKnightAttacks(toMove);
		if(attacks & opositeKing) {
			return true;
		}
	}

	U64 pawnsToMove = board.pieces2[sideToMove][PAWN];

	attacks = getPawnAttacks(pawnsToMove, sideToMove);
	if(attacks & opositeKing) {
//		printChessBoard(board);
		return true;
	}

	U64 kingToMove = board.pieces2[sideToMove][KING];
	toMove=getFirstPiece2(kingToMove);


	attacks = getKingAttacks(toMove);

	if(attacks & opositeKing) {
		return true;
	}

	return false;
}

bool isOccupated(U64 mask, U64 board); 


inline int getPieceToAddForPawn(PIECE_T piece, int promotion) {
	return piece*(!promotion) + promotion;
}

inline int getFirstPawnRank(bool side) {
	return side*40 + 8;
}

inline int getPromotionRank(bool side) {
	return !side * 40 + 8;
}


void printBitMap(U64 bitMap, char c);


extern char movesCodes[65][3];			
			



#endif
