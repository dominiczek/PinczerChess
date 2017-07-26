#ifndef MOVESGENERATOR_H_
#define MOVESGENERATOR_H_

inline void generateMovesAndCaptures(const ChessBoard &board, const U64 sqrMask,
		const int piece, const U64 attacks, MovesList &moveList) {

	if (!attacks) {
		return;
	}

	U64 captures = attacks & board.opositePieces();
	U64 legalMoves = attacks - (attacks & board.all_pieces);

	U64 to;
	while (captures) {
		to = popFirstPiece3(captures);
		moveList.addCapture(Move(piece, sqrMask, to));
	}
	while (legalMoves) {
		to = popFirstPiece3(legalMoves);
		moveList.addMove(Move(piece, sqrMask, to));
	}
}

inline bool isSquareAttacked(U64 sqrMask, const ChessBoard& board) {
	SQUARE_T sqr = getFirstPiece2(sqrMask);

	U64 attacks = kingMoves[sqr];
	if (attacks & board.myPieces(KING)) {
		return true;
	}

	U64 pawnsToMove = board.pieces2[board.sideToMove][PAWN];

	attacks = getPawnAttacks(pawnsToMove, board.sideToMove);
	if (attacks & sqrMask) {
		return true;
	}

	const U64 (*moves) = queenMoves[sqr];

	U64 queenAndRook = board.myPieces(ROOK) | board.myPieces(QUEEN);
	U64 queenAndBishop = board.myPieces(BISHOP) | board.myPieces(QUEEN);

	if (checkCaptureOnPositiveDirection(board.allPieces(), moves[N], queenAndRook)) {
		return true;
	}
	if (checkCaptureOnPositiveDirection(board.allPieces(), moves[NE], queenAndBishop)) {
		return true;
	}
	if (checkCaptureOnPositiveDirection(board.allPieces(), moves[E], queenAndRook)) {
		return true;
	}
	if (checkCaptureOnNegativeDirection(board.allPieces(), moves[SE], queenAndBishop)) {
		return true;
	}
	if (checkCaptureOnNegativeDirection(board.allPieces(), moves[S], queenAndRook)) {
		return true;
	}
	if (checkCaptureOnNegativeDirection(board.allPieces(), moves[SW], queenAndBishop)) {
		return true;
	}
	if (checkCaptureOnNegativeDirection(board.allPieces(), moves[W], queenAndRook)) {
		return true;
	}
	if (checkCaptureOnPositiveDirection(board.allPieces(), moves[NW], queenAndBishop)) {
		return true;
	}

	attacks = knightMoves[sqr];
	if (attacks & board.myPieces(KNIGHT)) {
		return true;
	}

	return false;
}

inline void generateMovesPromotion(const ChessBoard& board, MovesList& movesList) {

	U64 opositeKing = board.opositeKing();

	SQUARE_T toMove;
	U64 attacks;
	U64 sqrMask;

	bool sideToMove = board.sideToMove;

	U64 queensToMove = board.pieces2[sideToMove][QUEEN];
	while (queensToMove) {
		sqrMask = popFirstPiece3(queensToMove, toMove);
		attacks = getQueenAttacks(board.all_pieces, toMove);
		generateMovesAndCaptures(board, sqrMask, QUEEN, attacks, movesList);
	}

	U64 bishopsToMove = board.pieces2[sideToMove][BISHOP];
	while (bishopsToMove) {
		sqrMask = popFirstPiece3(bishopsToMove, toMove);
		attacks = getBishopAttacks(board.all_pieces, toMove);
		generateMovesAndCaptures(board, sqrMask, BISHOP, attacks, movesList);
	}

	U64 rooksToMove = board.pieces2[sideToMove][ROOK];
	while (rooksToMove) {
		sqrMask = popFirstPiece3(rooksToMove, toMove);
		attacks = getRookAttacks(board.all_pieces, toMove);
		generateMovesAndCaptures(board, sqrMask, ROOK, attacks, movesList);
	}

	U64 knightsToMove = board.pieces2[sideToMove][KNIGHT];
	while (knightsToMove) {
		sqrMask = popFirstPiece3(knightsToMove, toMove);
		attacks = getKnightAttacks(toMove);
		generateMovesAndCaptures(board, sqrMask, KNIGHT, attacks, movesList);
	}

	U64 pawnsToMove = board.pieces2[sideToMove][PAWN];
	attacks = getPawnAttacks(pawnsToMove, sideToMove);

	U64 kingToMove = board.pieces2[sideToMove][KING];
	toMove = getFirstPiece2(kingToMove);

	attacks = getKingAttacks(toMove);

	generateMovesAndCaptures(board, kingToMove, KING, attacks, movesList);
}

//inline bool iterate(PIECE_T piece, const ChessBoard& chessBoard, MovesList& movesList) {
//
//	U64 board = chessBoard.pieces2[chessBoard.sideToMove][piece];
//	if(board) {
//		SQUARE_T toMove;
//		U64 sqrMask=getFirstPiece3(board, toMove);
//		U64 attacks = getQueenAttacks(chessBoard.allPieces(), toMove);
//		if(attacks & chessBoard.opositeKing()) {
//			return true;
//		}
//
//		generateMovesAndCaptures(chessBoard, sqrMask, piece, attacks, movesList);
//	}
//}

inline void generateMoves(const ChessBoard& board, MovesList& movesList) {

	//U64 opositeKing = board.opositeKing();

	SQUARE_T toMove;
	U64 attacks;
	U64 sqrMask;

	bool sideToMove = board.sideToMove;

	U64 queensToMove = board.pieces2[sideToMove][QUEEN];
	if (queensToMove) {
		//sqrMask=getFirstPiece3(queensToMove, toMove);
		toMove = getFirstPiece2(queensToMove);
		attacks = getQueenAttacks(board.all_pieces, toMove);
		generateMovesAndCaptures(board, queensToMove, QUEEN, attacks,
				movesList);
	}

	U64 bishopsToMove = board.pieces2[sideToMove][BISHOP];
	if (bishopsToMove) {
		sqrMask = popFirstPiece3(bishopsToMove, toMove);
		attacks = getBishopAttacks(board.all_pieces, toMove);
		generateMovesAndCaptures(board, sqrMask, BISHOP, attacks, movesList);
		if (bishopsToMove) {
			toMove = getFirstPiece2(bishopsToMove);
			attacks = getBishopAttacks(board.all_pieces, toMove);
			generateMovesAndCaptures(board, bishopsToMove, BISHOP, attacks,
					movesList);
		}
	}

	U64 rooksToMove = board.pieces2[sideToMove][ROOK];
	if (rooksToMove) {
		sqrMask = popFirstPiece3(rooksToMove, toMove);
		attacks = getRookAttacks(board.all_pieces, toMove);
		generateMovesAndCaptures(board, sqrMask, ROOK, attacks, movesList);
		if (rooksToMove) {
			toMove = getFirstPiece2(rooksToMove);
			attacks = getRookAttacks(board.all_pieces, toMove);
			generateMovesAndCaptures(board, rooksToMove, ROOK, attacks, movesList);
		}
	}

	U64 knightsToMove = board.pieces2[sideToMove][KNIGHT];
	if (knightsToMove) {
		sqrMask = popFirstPiece3(knightsToMove, toMove);
		attacks = getKnightAttacks(toMove);
		generateMovesAndCaptures(board, sqrMask, KNIGHT, attacks, movesList);
		if (knightsToMove) {
			toMove = getFirstPiece2(knightsToMove);
			attacks = getKnightAttacks(toMove);
			generateMovesAndCaptures(board, knightsToMove, KNIGHT, attacks, movesList);
		}
	}

	U64 pawnsToMove = board.pieces2[sideToMove][PAWN];
	attacks = getPawnAttacks(pawnsToMove, sideToMove);

	U64 kingToMove = board.pieces2[sideToMove][KING];
	toMove = getFirstPiece2(kingToMove);

	attacks = getKingAttacks(toMove);

	generateMovesAndCaptures(board, kingToMove, KING, attacks, movesList);
}

#endif
