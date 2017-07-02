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

int illegalPositions = 0;


signed long long Perft(ChessBoard &board, int depth) {

	depth--;

    MovesList move_list;
    signed long long nodes = 0;


    generateAllMoves(board, move_list);

    int s = getMovesSize(move_list);

    bool isIllegal;

    for (int i=0;i<s;i++) {
    	Move move = move_list.moves[i];
        ChessBoard copy = makeMove(board, move);

        isIllegal = generateAttacksMap(copy, copy.attacks);

        if(isIllegal) {
   			continue;
		}
//		printChessBoard(copy);
        if(depth) {
        	nodes += Perft(copy, depth);
        } else {
        	nodes++;
        }
      //  printChessBoard(copy);
    }

    s = getCapturesSize(move_list);

    for (int i=0;i<s;i++) {
    	Move move = move_list.captures[i];
        ChessBoard copy = makeCapture(board, move);

        isIllegal = generateAttacksMap(copy, copy.attacks);

        if(isIllegal) {
   			continue;
		}
//		printChessBoard(copy);
        if(depth) {
        	nodes += Perft(copy, depth);
        } else {
        	nodes++;
        }
      //  printChessBoard(copy);
    }

    return nodes;
}


void run() {
	ChessBoard board = createNewBoard();

	parseFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq -");
//	parseFen(board, "rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR w KQkq -");
//	parseFen(board, "rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR w KQkq -");
//	parseFen(board, "8/2p5/3p4/KP6/5p1k/8/4P1P1/8 w - -");
	 //parseFen(board, "8/7p/p5pb/4k3/P1pPn3/8/P5PP/1rB2RK1 b - d3 0 28");
//	parseFen(board, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");//7 OK
	//  szach
//	parseFen(board, "8/2p5/3p4/KP5r/1R3p1k/6P1/4P3/8 b - -");
//	parseFen(board, "8/3K4/2p5/p2b2r1/5k2/8/8/1q6 b - -");//8 OK
	//parseFen(board, "r1bqkbnr/1ppp1ppp/p1n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq e6");

//	parseFen(board, "8/PPP4k/8/8/8/8/4Kppp/8 w - -");//8 OK
//	parseFen(board, "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

	cout<<"Move: "<<board.sideToMove<<endl;
	cout<<"init EN "<<board.enPessantSqr<<endl;
	printChessBoard(board);

	//cout<< getFirstPiece(board->king[WHITE])<<endl;
	//4 - 197,281
	//5  4,865,609 - OK
	//6  119060324 - OK

	generateAttacksMap(board, board.attacks);

	cout<<"Moves: "<<Perft(board, 6)<<endl;

//	printBitMap(getPawnAttacksRight(1LL<<8, 1), 'x');
//	printBitMap(1LL<<8, 'y');


}

int main() {
	clock_t tStart = clock();

	run();

	cout<<"Time taken: "<< ( ( (double) (clock() - tStart)) / CLOCKS_PER_SEC) <<" s.";
	return 0;
}
