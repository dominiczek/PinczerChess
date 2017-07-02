
#include "chessboard.h"
#include "move.h"
#include "attacks.h"
#include <iostream>

using namespace std;


char movesCodes[65][3] = {"no",	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
								"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
								"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
								"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
};


void addNewPawn(ChessBoard &board, int square, bool side) {
	U64 mask = 1LL<<(square-1);
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][PAWN] |= mask;
}

void addNewKnight(ChessBoard &board, int square, bool side) {
	U64 mask = 1LL<<(square-1);
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][KNIGHT] |= mask;
}

void addNewBishop(ChessBoard &board, int square, bool side) {
	U64 mask = 1LL<<(square-1);
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][BISHOP] |= mask;
}

void addNewRook(ChessBoard &board, int square, bool side) {
	U64 mask = 1LL<<(square-1);
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][ROOK] |= mask;
}

void addNewQueen(ChessBoard &board, int square, bool side) {
	U64 mask = 1LL<<(square-1);
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][QUEEN] |= mask;
}

void addNewKing(ChessBoard &board, int square, bool side) {
	U64 mask = 1LL<<(square-1);
	board.pieces[side] |= mask;
	board.allPieces |= mask;
	board.pieces2[side][KING] |= mask;
}


bool isOccupated(int square, U64 board) {
	return 0; 
}

void printBitMap(U64 bitMap, char c) {
	
	for(int y=7; y >-1; y--) {
		for(int x=0; x<8; x++) {
			int index=8*y + x;
			
			U64 mask = 1LL<<index;
			
			if(mask & bitMap) {
				cout<<c; 
			} else {
				cout<<"o";
			}
		}
		cout<<endl;
	}
	
	cout<<endl;
}

void printChessBoard(const ChessBoard &chessBoard) {
	
	cout<<"   |A|B|C|D|E|F|G|H|"<<endl<<endl;
	for(int y=7; y >-1; y--) {
		cout<<y+1<<"  |";
		for(int x=0; x<8; x++) {
			int index=8*y + x;
			U64 mask = 1LL<<index;
			
			if(mask & chessBoard.pieces2[BLACK][PAWN]) {
				cout<<"p|"; 
			} else if(mask & chessBoard.pieces2[WHITE][PAWN]) {
				cout<<"P|"; 
			} else if(mask & chessBoard.pieces2[BLACK][ROOK]) {
				cout<<"r|"; 
			} else if(mask & chessBoard.pieces2[WHITE][ROOK]) {
				cout<<"R|"; 
			} else if(mask & chessBoard.pieces2[BLACK][KNIGHT]) {
				cout<<"n|"; 
			} else if(mask & chessBoard.pieces2[WHITE][KNIGHT]) {
				cout<<"N|"; 
			} else if(mask & chessBoard.pieces2[BLACK][BISHOP]) {
				cout<<"b|"; 
			} else if(mask & chessBoard.pieces2[WHITE][BISHOP]) {
				cout<<"B|"; 
			} else if(mask & chessBoard.pieces2[BLACK][KING]) {
				cout<<"k|"; 
			} else if(mask & chessBoard.pieces2[WHITE][KING]) {
				cout<<"K|"; 
			}  else if(mask & chessBoard.pieces2[BLACK][QUEEN]) {
				cout<<"q|"; 
			} else if(mask & chessBoard.pieces2[WHITE][QUEEN]) {
				cout<<"Q|"; 
			} else {
				cout<<"_|";
			} 
		}
		cout<<"  "<<y+1<<endl;
	}
	cout<<endl<<"   |A|B|C|D|E|F|G|H|"<<endl;
}
