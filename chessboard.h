#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>

#include "attacks.h"
#include "move.h"

using namespace std;



class ChessBoard {
	
public:
	U64 all_pieces;
	U64 pieces[2];
	
	U64 pieces2[2][6];
	bool sideToMove;

	bool castleKingW;
	bool castleQueenW;
	bool castleKingB;
	bool castleQueenB;
	
	U64 enPessantSqr;

	ChessBoard() {

	}

	inline ChessBoard makeMove(const Move& move) const {

		ChessBoard copy = createCopy(*this);

		copy.removePiece(move.maskFrom, move.piece, sideToMove);
		copy.addPiece(move.maskTo, move.piece, sideToMove);

		copy.enPessantSqr = move.enPessant;

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

	inline ChessBoard makeCapture(const Capture& move) const {

		ChessBoard copy = createCopy(*this);


		copy.take(move.maskTo, !sideToMove, move.capturedPiece);

		PIECE_T pieceToAdd = move.promotion ? move.promotion : move.piece;

		if(move.piece == PAWN && move.maskTo == enPessantSqr) {
			copy.removePiece(moveForward(enPessantSqr, 8, !sideToMove), PAWN, !sideToMove);
		}

		copy.removePiece(move.maskFrom, move.piece, sideToMove);
		copy.addPiece(move.maskTo, pieceToAdd, sideToMove);

		copy.enPessantSqr = 0;

		copy.sideToMove = !sideToMove;

		return copy;
	}

	inline PIECE_T getOppositePiece(const U64 sqrMask) const {
		if(pieces2[!sideToMove][PAWN] & sqrMask) {
			return PAWN;
		}
		if(pieces2[!sideToMove][KNIGHT] & sqrMask) {
			return KNIGHT;
		}
		if(pieces2[!sideToMove][BISHOP] & sqrMask) {
			return BISHOP;
		}
		if(pieces2[!sideToMove][QUEEN] & sqrMask) {
			return QUEEN;
		}
		if(pieces2[!sideToMove][ROOK] & sqrMask) {
			return ROOK;
		}

		return 0;
	}

	inline U64 allPieces() const {
		return all_pieces;
	}

	inline U64 opositePieces() const {
		return pieces[!sideToMove];
	}

	inline U64 opositePieces(PIECE_T piece) const {
		return pieces2[!sideToMove][piece];
	}

	inline U64 opositeKing() const {
		return pieces2[!sideToMove][KING];
	}

	inline U64 myPieces(PIECE_T piece) const {
		return pieces2[sideToMove][piece];
	}


private:

	inline ChessBoard createCopy(const ChessBoard &board) const {
		ChessBoard copy;
		copy.all_pieces = all_pieces;

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
		all_pieces += mask;
		pieces2[side][piece] += mask;
	}

	inline void removePiece(const U64 mask, const PIECE_T piece, const bool side) {
		pieces[side] -= mask;
		all_pieces -= mask;
		pieces2[side][piece] -= mask;
	}

	inline void take(U64 mask, bool side, PIECE_T capturedPiece) {
		all_pieces &= ~mask;
		pieces[side] &= all_pieces;
		pieces2[side][capturedPiece] &= all_pieces;
	}

};

void printChessBoard(const ChessBoard &chessBoard);
void printBitMap(U64 bitMap, char c);

inline ChessBoard createNewBoard() {
	ChessBoard board;
	board.all_pieces = 0;
	
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
	
	board.enPessantSqr = 0;
	
	return board;
}

void addNewPawn(ChessBoard &board, int square, bool side);
void addNewKnight(ChessBoard &board, int square, bool side);
void addNewBishop(ChessBoard &board, int square, bool side);
void addNewRook(ChessBoard &board, int square, bool side);
void addNewQueen(ChessBoard &board, int square, bool side);
void addNewKing(ChessBoard &board, int square, bool side);


bool isOccupated(U64 mask, U64 board); 


void printBitMap(U64 bitMap, char c);

extern char movesCodes[65][3];			
			



#endif
