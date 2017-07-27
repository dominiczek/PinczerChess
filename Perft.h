#ifndef PERFT_H
#define PERFT_H

#include "move.h"
#include "pawnsMoves.h"
#include "movesGenerator.h"

template <bool sideToMove>
signed long long PerftPromotion(const ChessBoard &board, MovesList &move_list, int depth);

template <bool sideToMove>
signed long long Perft(const ChessBoard &board, MovesList &move_list, int depth) {

	depth--;

    signed long long nodes = 0;

    Move* moves = move_list.getPromotions();

    while(move_list.hasNextPromotion(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makePromotion(move);

        if(isSquareAttacked<!sideToMove>(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMovesPromotion<!sideToMove>(copy, new_move_list);
            generatePawnsMoves<!sideToMove>(copy, new_move_list);
        	nodes += PerftPromotion<!sideToMove>(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    moves = move_list.getMoves();

    while(move_list.hasNextMove(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makeMove(move);

        if(isSquareAttacked<!sideToMove>(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMoves<!sideToMove>(copy, new_move_list);
            generatePawnsMoves<!sideToMove>(copy, new_move_list);
        	nodes += Perft<!sideToMove>(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    Capture* captures = move_list.getCaptures();

	while(move_list.hasNextCapture(captures)) {
		Capture move = *captures++;
        ChessBoard copy = board.makeCapture(move);

        if(isSquareAttacked<!sideToMove>(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
			generateMoves<!sideToMove>(copy, new_move_list);
			generatePawnsMoves<!sideToMove>(copy, new_move_list);
			nodes += Perft<!sideToMove>(copy, new_move_list, depth);
		} else {
			nodes++;
		}
      //  printChessBoard(copy);
    }
    return nodes;
}

template <bool sideToMove>
signed long long PerftPromotion(const ChessBoard &board, MovesList &move_list, int depth) {

	depth--;

    signed long long nodes = 0;

    Move* moves = move_list.getPromotions();

    while(move_list.hasNextPromotion(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makePromotion(move);

        if(isSquareAttacked<!sideToMove>(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMovesPromotion<!sideToMove>(copy, new_move_list);
            generatePawnsMoves<!sideToMove>(copy, new_move_list);
        	nodes += PerftPromotion<!sideToMove>(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    moves = move_list.getMoves();


    while(move_list.hasNextMove(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makeMove(move);

        if(isSquareAttacked<!sideToMove>(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMovesPromotion<!sideToMove>(copy, new_move_list);
            generatePawnsMoves<!sideToMove>(copy, new_move_list);
        	nodes += PerftPromotion<!sideToMove>(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    Capture* captures = move_list.getCaptures();

	while(move_list.hasNextCapture(captures)) {
		Capture move = *captures++;
        ChessBoard copy = board.makeCapture(move);

        if(isSquareAttacked<!sideToMove>(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
			generateMovesPromotion<!sideToMove>(copy, new_move_list);
			generatePawnsMoves<!sideToMove>(copy, new_move_list);
			nodes += PerftPromotion<!sideToMove>(copy, new_move_list, depth);
		} else {
			nodes++;
		}
      //  printChessBoard(copy);
    }
    return nodes;
}


#endif
