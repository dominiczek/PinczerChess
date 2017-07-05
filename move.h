#ifndef MOVE_H
#define MOVE_H

#include "allMoves.h"
#include "constants.h"

struct Move {
	PIECE_T piece;
	U64 maskFrom;
	U64 maskTo;
	int promotion;
	int castle;
	
	U64 enPessant;
};

class MovesList {

public:
	Move moves[256];
	Move captures[128];
private:
	Move *movesHead = moves;
	Move *capturesHead = captures;
public:
	inline void addMove(const Move &move) {
		*movesHead++=move;
	}
	inline void addCapture(const Move &move) {
		*capturesHead++=move;
	}
	inline int getMovesSize() {
		return movesHead - moves;
	}
	inline int getCapturesSize() {
		return capturesHead - captures;
	}
};

Move* fromString(char* str);

inline Move createMove(const PIECE_T piece, const U64 from, const U64 to) {
	Move move;
	
	move.piece = piece;
	move.maskFrom = from;
	move.maskTo = to;

	move.castle = 0;
	move.enPessant = 0;
	move.promotion = 0;
	
	return move;	
}

inline Move createMove(const PIECE_T piece, const U64 from, const U64 to, const U64 enPessant) {
	Move move;
	
	move.piece = piece;
	move.maskFrom = from;
	move.maskTo = to;
	
	move.castle = 0;
	move.enPessant = enPessant;
	move.promotion = 0;
	
	return move;	
}

inline Move createPromotionMove(const PIECE_T piece, const U64 from, const U64 to, const int promotion) {
	Move move;
	
	move.piece = piece;
	move.maskFrom = from;
	move.maskTo = to;

	move.castle = 0;
	move.enPessant = 0;
	move.promotion = promotion;
	
	return move;	
}
#endif
