#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>

#include "attacks.h"
#include "move.h"

using namespace std;

const bool WHITE = 0;
const bool BLACK = 1;

const int KING = 0;
const int QUEEN = 1;
const int ROOK = 2;
const int BISHOP = 3;
const int KNIGHT = 4;
const int PAWN = 5;

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
	
	Attacks attacks;
};

const int firstPawnRankShift[2] = {8, 48};
const int promotionRankShift[2] = {48, 8};

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


inline bool generateAttacksMap(const ChessBoard& board, Attacks &attacksMap) {
	
	for(int i=0;i<64;i++) {
		attacksMap.attacks[i] =0;
	}

	U64 opositeKing = board.pieces2[!board.sideToMove][KING];
	
	SQUARE_T toMove;
	U64 attacks;

	bool sideToMove = board.sideToMove;
	
	
	U64 queensToMove = board.pieces2[sideToMove][QUEEN];
	while(queensToMove) {
		toMove = popFirstPiece2(&queensToMove);
		attacks = getQueenAttacks(board.allPieces, toMove);
		if(attacks&opositeKing) {
			return true;
		}
		addPieceAttacks(attacksMap, toMove, attacks);
	}
	
	U64 bishopsToMove = board.pieces2[sideToMove][BISHOP];
	while(bishopsToMove) {
		toMove=popFirstPiece2(&bishopsToMove);
		attacks = getBishopAttacks(board.allPieces, toMove);
		if(attacks&opositeKing) {
			return true;
		}
		addPieceAttacks(attacksMap, toMove, attacks);
	}

	U64 rooksToMove = board.pieces2[sideToMove][ROOK];
	while(rooksToMove) {
		toMove=popFirstPiece2(&rooksToMove);
		attacks = getRookAttacks(board.allPieces, toMove);
		if(attacks&opositeKing) {
			return true;
		}
		addPieceAttacks(attacksMap, toMove, attacks);
	}

	U64 knightsToMove = board.pieces2[sideToMove][KNIGHT];
	while(knightsToMove) {
		toMove=popFirstPiece2(&knightsToMove);
		attacks = getKnightAttacks(toMove);
		if(attacks&opositeKing) {
			return true;
		}
		addPieceAttacks(attacksMap, toMove, attacks);
	}

	U64 pawnsToMove = board.pieces2[sideToMove][PAWN];
	
	addPawnsAttacks(attacksMap, pawnsToMove, sideToMove);

	attacks = board.attacks.rightPawnAttacks | board.attacks.leftPawnAttacks;

	if(attacks & opositeKing) {
		return true;
	}

	U64 kingToMove = board.pieces2[sideToMove][KING];
	toMove=popFirstPiece2(&kingToMove);

	attacks = getKingAttacks(toMove);
	
	if(attacks&opositeKing) {
		return true;
	}
	addPieceAttacks(attacksMap, toMove, attacks);

	return false;
}


inline void addPiece(ChessBoard &board, const U64 mask, const int piece, bool side) {
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][piece] |= mask;
}

inline void removePiece(ChessBoard &board, const U64 mask, const int piece, const bool side) {
	board.pieces[side] ^= mask;
	board.allPieces ^= mask;
	board.pieces2[side][piece] ^= mask;
}

inline void conditionalRemovePiece(ChessBoard &board, U64 mask, const int piece, const bool side, bool condition) {
	mask*=condition;
	board.pieces[side] ^= mask;
	board.allPieces ^= mask;
	board.pieces2[side][piece] ^= mask;
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

//inline bool isCheck(const ChessBoard &board, SQUARE_T sqr) {
//	return board.attacks.attackedBy[sqr]&board.pieces[!board.sideToMove];
//}

inline int getPieceToAddForPawn(int piece, int promotion) {
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

	int pieceToAdd = move.promotion ? move.promotion : move.piece;
	
	removePiece(copy, move.maskFrom, move.piece, board.sideToMove);
	addPiece(copy, move.maskTo, pieceToAdd, board.sideToMove);

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

	int pieceToAdd = move.promotion ? move.promotion : move.piece;

	conditionalRemovePiece(copy, board.enPessantPawn, PAWN, !board.sideToMove, move.piece == PAWN && move.maskTo == board.enPessantSqr);
	removePiece(copy, move.maskFrom, move.piece, board.sideToMove);
	addPiece(copy, move.maskTo, pieceToAdd, board.sideToMove);

	copy.sideToMove = !board.sideToMove;
	return copy;
}




void printBitMap(U64 bitMap, char c);


enum FIELD {A1=0, B1, C1, D1, E1, F1, G1, H1, A2, B2, C2, D2, E2, F2, G2, H2,
			A3, B3, C3, D3, E3, F3, G3, H3, A4, B4, C4, D4, E4, F4, G4, H4,
			A5, B5, C5, D5, E5, F5, G5, H5, A6, B6, C6, D6, E6, F6, G6, H6,
			A7, B7, C7, D7, E7, F7, G7, H7, A8, B8, C8, D8, E8, F8, G8, H8};
			

extern char movesCodes[65][3];			
			



#endif
