#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>

#include "attacks.h"
#include "move.h"

using namespace std;



struct ChessBoard {
	
	U64 allPieces;
	
	U64 pieces[2];
	
	U64 pieces2[2][6];
	
	bool castleKingW;
	bool castleQueenW;
	bool castleKingB;
	bool castleQueenB;
	
	bool sideToMove;
	U64 enPessantSqr;
	U64 enPessantPawn;


	inline void addPiece(const U64 mask, const PIECE_T piece,const bool side) {
		pieces[side] |= mask;
		allPieces |= mask;
		pieces2[side][piece] |= mask;
	}

	inline void removePiece(const U64 mask, const PIECE_T piece, const bool side) {
		pieces[side] ^= mask;
		allPieces ^= mask;
		pieces2[side][piece] ^= mask;
	}

	inline void conditionalRemovePiece(U64 mask, const PIECE_T piece, const bool side, bool condition) {
		mask*=condition;
		pieces[side] ^= mask;
		allPieces ^= mask;
		pieces2[side][piece] ^= mask;
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
	U64 legalMoves = attacks & (attacks^board.allPieces);;
	U64 captures = attacks & board.pieces[!board.sideToMove];

	U64 to;
	while(captures) {
		to = popFirstPiece3(captures);
		moveList.addCapture(createMove(piece, sqrMask, to));
	}
	while(legalMoves) {
		to = popFirstPiece3(legalMoves);
		moveList.addMove(createMove(piece, sqrMask, to));
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
		attacks = getQueenAttacks(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
	}

	U64 bishopsToMove = board.pieces2[sideToMove][BISHOP];
	while(bishopsToMove) {
		toMove=popFirstPiece2(&bishopsToMove);
		attacks = getBishopAttacks(board.allPieces, toMove);
		if(attacks & opositeKing) {
			return true;
		}
	}

	U64 rooksToMove = board.pieces2[sideToMove][ROOK];
	while(rooksToMove) {
		toMove=popFirstPiece2(&rooksToMove);
		attacks = getRookAttacks(board.allPieces, toMove);
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

inline void take(ChessBoard &board, U64 mask, bool side) {
	board.allPieces &= ~mask;
	board.pieces[side] &= board.allPieces;
	board.pieces2[side][QUEEN] &= board.allPieces;
	board.pieces2[side][ROOK] &= board.allPieces;
	board.pieces2[side][BISHOP] &= board.allPieces;
	board.pieces2[side][KNIGHT] &= board.allPieces;
	board.pieces2[side][PAWN] &= board.allPieces;
}

bool isOccupated(U64 mask, U64 board); 


inline int getPieceToAddForPawn(PIECE_T piece, int promotion) {
	return piece*(!promotion) + promotion;
}
 
inline ChessBoard makeMove(const ChessBoard& board, const Move& move) {
	ChessBoard copy;
	copy.allPieces = board.allPieces;

	copy.pieces[WHITE] = board.pieces[WHITE];
	copy.pieces[BLACK] = board.pieces[BLACK];
	
	for(int i=0; i<6;i++) {
		copy.pieces2[WHITE][i] = board.pieces2[WHITE][i];
		copy.pieces2[BLACK][i] = board.pieces2[BLACK][i];	
	}

	PIECE_T pieceToAdd = move.promotion ? move.promotion : move.piece;
	
	copy.removePiece(move.maskFrom, move.piece, board.sideToMove);
	copy.addPiece(move.maskTo, pieceToAdd, board.sideToMove);

	copy.enPessantSqr = move.enPessant;
	copy.enPessantPawn = move.maskTo;

	copy.sideToMove = !board.sideToMove;	
	return copy;
}

inline ChessBoard makeCapture(const ChessBoard& board, const Move& move) {
	ChessBoard copy;
	copy.allPieces = board.allPieces;

	copy.pieces[WHITE] = board.pieces[WHITE];
	copy.pieces[BLACK] = board.pieces[BLACK];

	for(int i=0; i<6;i++) {
		copy.pieces2[WHITE][i] = board.pieces2[WHITE][i];
		copy.pieces2[BLACK][i] = board.pieces2[BLACK][i];
	}

	copy.enPessantSqr = 0;

	take(copy, move.maskTo, !board.sideToMove);

	PIECE_T pieceToAdd = move.promotion ? move.promotion : move.piece;

	copy.conditionalRemovePiece(board.enPessantPawn, PAWN, !board.sideToMove, move.piece == PAWN && move.maskTo == board.enPessantSqr);
	copy.removePiece(move.maskFrom, move.piece, board.sideToMove);
	copy.addPiece(move.maskTo, pieceToAdd, board.sideToMove);

	copy.sideToMove = !board.sideToMove;
	return copy;
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
