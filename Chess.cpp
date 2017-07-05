//============================================================================
// Name        :
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "chessboard.h"
#include "fenParser.h"
#include "moveGenerator.h"
#include "move.h"


using namespace std;

signed long long Perft(ChessBoard &board, MovesList &move_list, int depth) {

	depth--;

    signed long long nodes = 0;


    int s = move_list.getMovesSize();

    bool isIllegal;

    for (int i=0;i<s;i++) {
    	Move move = move_list.moves[i];
        ChessBoard copy = makeMove(board, move);
        MovesList new_move_list;

        if(depth) {
            isIllegal = generateAttacksMap(copy, new_move_list);
            if(isIllegal) {
       			continue;
    		}
            generateAllMoves(copy, new_move_list);
        	nodes += Perft(copy, new_move_list, depth);
        } else {
        	isIllegal = checkAttacks(copy, new_move_list);
			if(isIllegal) {
				continue;
			}
        	nodes++;
        }
//        printChessBoard(copy);
    }

    int s2 = move_list.getCapturesSize();

    for (int i=0;i<s2;i++) {
    	Move move = move_list.captures[i];
        ChessBoard copy = makeCapture(board, move);
        MovesList new_move_list;


        if(depth) {
			isIllegal = generateAttacksMap(copy, new_move_list);
			if(isIllegal) {
				continue;
			}
			generateAllMoves(copy, new_move_list);
			nodes += Perft(copy, new_move_list, depth);
		} else {
			isIllegal = checkAttacks(copy, new_move_list);
			if(isIllegal) {
				continue;
			}
			nodes++;
		}
      //  printChessBoard(copy);
    }

    if(s+s2 == 0) {
    	cout<<"MAT/PAT"<<endl;
    }

    return nodes;
}


void run() {
	ChessBoard board = createNewBoard();

	parseFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
//	parseFen(board, "rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR w KQkq -");
//	parseFen(board, "rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR w KQkq -");
//	parseFen(board, "8/2p5/3p4/KP6/5p1k/8/4P1P1/8 w - -");
	 //parseFen(board, "8/7p/p5pb/4k3/P1pPn3/8/P5PP/1rB2RK1 b - d3 0 28");
//	parseFen(board, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");//7 OK , 6 zle :(
	//  szach
//	parseFen(board, "8/2p5/3p4/KP5r/1R3p1k/6P1/4P3/8 b - -");
//	parseFen(board, "8/3K4/2p5/p2b2r1/5k2/8/8/1q6 b - -");//8 OK
	//parseFen(board, "r1bqkbnr/1ppp1ppp/p1n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq e6");

//	parseFen(board, "8/PPP4k/8/8/8/8/4Kppp/8 w - -");//8 OK, 6 zle :(
//	parseFen(board, "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

	cout<<"Move: "<<board.sideToMove<<endl;
	cout<<"init EN "<<board.enPessantSqr<<endl;
	printChessBoard(board);

	//cout<< getFirstPiece(board->king[WHITE])<<endl;
	//4 - 197,281
	//5  4,865,609 - OK
	//6  119060324 - OK


    MovesList move_list;
	generateAttacksMap(board, move_list);
    generateAllMoves(board, move_list);


	cout<<"Moves: "<<Perft(board, move_list, 6)<<endl;

//	printBitMap(1+(1<<8), '1');
}

int main() {
	clock_t tStart = clock();

	run();

	cout<<"Time taken: "<< ( ( (double) (clock() - tStart)) / CLOCKS_PER_SEC) <<" s.";
	return 0;
}
