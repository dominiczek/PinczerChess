#ifndef MOVE_H
#define MOVE_H

#include "allMoves.h"

struct Move {
	int piece;
	U64 maskFrom;
	U64 maskTo;
	int promotion;
	int castle;
	
	U64 enPessant;
};

struct MovesList {
	Move moves[256];
	Move *movesHead = moves;

	Move captures[128];
	Move *capturesHead = captures;
};

Move* fromString(char* str);

inline void addMove(MovesList &list,const Move &move) {
	*list.movesHead++=move;
}

inline int getMovesSize(const MovesList &list) {
	return list.movesHead - list.moves;
}

inline void addCapture(MovesList &list, const Move &move) {
	*list.capturesHead++=move;
}

inline int getCapturesSize(const MovesList &list) {
	return list.capturesHead - list.captures;
}

inline Move createMove(const int piece, const U64 from, const U64 to) {
	Move move;
	
	move.piece = piece;
	move.maskFrom = from;
	move.maskTo = to;

	move.castle = 0;
	move.enPessant = 0;
	move.promotion = 0;
	
	return move;	
}

inline Move createMove(const int piece, const U64 from, const U64 to, const U64 enPessant) {
	Move move;
	
	move.piece = piece;
	move.maskFrom = from;
	move.maskTo = to;
	
	move.castle = 0;
	move.enPessant = enPessant;
	move.promotion = 0;
	
	return move;	
}

inline Move createPromotionMove(const int piece, const U64 from, const U64 to, const int promotion) {
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
