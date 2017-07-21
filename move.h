#ifndef MOVE_H
#define MOVE_H

#include "allMoves.h"
#include "constants.h"

class Move {
public:

	U64 maskFrom;
	U64 maskTo;
	PIECE_T piece;
	U64 enPessant;
	int promotion;
	int castle;

	inline Move(const PIECE_T piece, const U64 from, const U64 to, const U64 enPessant = 0) {
		this->piece = piece;
		this->maskFrom = from;
		this->maskTo = to;

		this->castle = 0;
		this->enPessant = enPessant;
		this->promotion = 0;
	}

	inline Move(const PIECE_T piece, const U64 from, const U64 to, const int promotion) {
		this->piece = piece;
		this->maskFrom = from;
		this->maskTo = to;

		this->castle = 0;
		this->enPessant = 0;
		this->promotion = promotion;
	}

	Move() {

	}


};

class MovesList {

private:
	Move moves[256];
	Move captures[128];
	Move promotions[32];
	Move *movesHead = moves;
	Move *capturesHead = captures;
	Move *promotionsHead = promotions;
public:

	inline void addMove(const Move &move) {
		*movesHead++=move;
	}
	inline void addCapture(const Move &move) {
		*capturesHead++=move;
	}
	inline void addPromotion(const Move &move) {
		*promotionsHead++=move;
	}
	inline Move* getCaptures() {
		return captures;
	}
	inline Move* getMoves() {
		return moves;
	}
	inline Move* getPromotions() {
		return promotions;
	}
	inline bool hasNextMove(Move* current) {
		return movesHead != current;
	}
	inline bool hasNextCapture(Move* current) {
		return capturesHead != current;
	}
	inline bool hasNextPromotion(Move* current) {
		return promotionsHead != current;
	}
};

Move* fromString(char* str);


#endif
