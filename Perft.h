#ifndef PERFT_H
#define PERFT_H

#include "move.h"
#include "pawnsMoves.h"
#include "movesGenerator.h"

signed long long PerftPromotion(const ChessBoard &board, MovesList &move_list, int depth);

signed long long Perft(const ChessBoard &board, MovesList &move_list, int depth) {

	depth--;

    signed long long nodes = 0;

    Move* moves = move_list.getPromotions();

    while(move_list.hasNextPromotion(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makePromotion(move);

        if(isSquareAttacked(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMovesPromotion(copy, new_move_list);
            generatePawnsMoves(copy, new_move_list);
        	nodes += PerftPromotion(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    moves = move_list.getMoves();

    while(move_list.hasNextMove(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makeMove(move);

        if(isSquareAttacked(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMoves(copy, new_move_list);
            generatePawnsMoves(copy, new_move_list);
        	nodes += Perft(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    Move* captures = move_list.getCaptures();

	while(move_list.hasNextCapture(captures)) {
    	Move move = *captures++;
        ChessBoard copy = board.makeCapture(move);

        if(isSquareAttacked(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
			generateMoves(copy, new_move_list);
			generatePawnsMoves(copy, new_move_list);
			nodes += Perft(copy, new_move_list, depth);
		} else {
			nodes++;
		}
      //  printChessBoard(copy);
    }
    return nodes;
}

signed long long PerftPromotion(const ChessBoard &board, MovesList &move_list, int depth) {

	depth--;

    signed long long nodes = 0;

    Move* moves = move_list.getPromotions();

    while(move_list.hasNextPromotion(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makePromotion(move);

        if(isSquareAttacked(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMovesPromotion(copy, new_move_list);
            generatePawnsMoves(copy, new_move_list);
        	nodes += PerftPromotion(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    moves = move_list.getMoves();


    while(move_list.hasNextMove(moves))  {
    	Move move = *moves++;
        ChessBoard copy = board.makeMove(move);

        if(isSquareAttacked(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
            generateMovesPromotion(copy, new_move_list);
            generatePawnsMoves(copy, new_move_list);
        	nodes += PerftPromotion(copy, new_move_list, depth);
        } else {
        	nodes++;
        }
//        printChessBoard(copy);
    }

    Move* captures = move_list.getCaptures();

	while(move_list.hasNextCapture(captures)) {
    	Move move = *captures++;
        ChessBoard copy = board.makeCapture(move);

        if(isSquareAttacked(copy.opositeKing(), copy)) {
        	continue;
        }

        if(depth) {
        	MovesList new_move_list;
			generateMovesPromotion(copy, new_move_list);
			generatePawnsMoves(copy, new_move_list);
			nodes += PerftPromotion(copy, new_move_list, depth);
		} else {
			nodes++;
		}
      //  printChessBoard(copy);
    }
    return nodes;
}


#endif
