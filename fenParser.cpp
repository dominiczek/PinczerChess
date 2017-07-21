#include "fenParser.h"

#include <iostream>
#include <ctype.h>
#include <string.h>
#include "chessboard.h"

using namespace std;

int fieldCodeToField(char* moveCode) {
	char x = tolower(moveCode[0]) - 97;
	char y = moveCode[1] - 49;
	
	return y*8 + x;
}

ChessBoard parseFen(ChessBoard& board, char* fenString) {
	
	char c = 'x';
	
	int boardIndexY = 7;
	int boardIndexX = 1;
	int stringIndex = 0;
	
	for(stringIndex = 0; c !=' '; stringIndex++) {
		c = fenString[stringIndex];
		
		if(isdigit(c)) {
			int offset = c - 48;
			
			boardIndexX += offset;
		} else {
			switch(c) {
				case 'r':  addNewRook(board, boardIndexY * 8 + boardIndexX++, BLACK); break;
				case 'n':  addNewKnight(board, boardIndexY * 8 + boardIndexX++, BLACK); break;
				case 'b':  addNewBishop(board, boardIndexY * 8 + boardIndexX++, BLACK); break;
				case 'k':  addNewKing(board, boardIndexY * 8 + boardIndexX++, BLACK); break;
				case 'q':  addNewQueen(board, boardIndexY * 8 + boardIndexX++, BLACK); break;
				case 'p':  addNewPawn(board, boardIndexY * 8 + boardIndexX++, BLACK); break;
				
				case 'R':  addNewRook(board, boardIndexY * 8 + boardIndexX++, WHITE); break;
				case 'N':  addNewKnight(board, boardIndexY * 8 + boardIndexX++, WHITE); break;
				case 'B':  addNewBishop(board, boardIndexY * 8 + boardIndexX++, WHITE); break;
				case 'K':  addNewKing(board, boardIndexY * 8 + boardIndexX++, WHITE); break;
				case 'Q':  addNewQueen(board, boardIndexY * 8 + boardIndexX++, WHITE); break;
				case 'P':  addNewPawn(board, boardIndexY * 8 + boardIndexX++, WHITE); break;
				
				case '/': boardIndexX = 1; boardIndexY--; break;
			}
			
		}			
	}

	c = fenString[stringIndex];
	
	if(c=='b') {
		board.sideToMove = 1;
		cout<<"BLACK"<<endl;
	} else {
		board.sideToMove = 0;
		cout<<"WHITE"<<endl;
	}
	
	c = fenString[++++stringIndex];
	
	
	
	if(c == '-') {
	} else {
		while(c!=' ') {
			if(c=='K') {
				board.castleKingW = true;
				cout<<"King side W"<<endl;
			}
			if(c=='k') {
				board.castleKingB = true;	
				cout<<"King side B"<<endl;
			}
			if(c=='Q') {
				board.castleQueenW = true;			
				cout<<"Queen side W"<<endl;
			}
			if(c=='q') {
				board.castleQueenB = true;		
				cout<<"King side W"<<endl;
			}
			c = fenString[++stringIndex];
		}
	}
		
	char enpessant[2];	
	stringIndex++;
	
	c = fenString[++stringIndex];
	if(c != '-' && c!='\0') {
		cout<<c;
		enpessant[0] = c;
		c = fenString[++stringIndex];
		cout<<c<<endl;
		enpessant[1] = c;
		
		cout<<enpessant<<endl;
		
		int enpessantSqr = fieldCodeToField(enpessant);
		cout<<"EN - "<<enpessantSqr<<endl;
		board.enPessantSqr = 1LL<<(enpessantSqr);
		
		if(board.sideToMove) {
			board.enPessantPawn = board.enPessantSqr<<8;	
		} else {
			board.enPessantPawn = board.enPessantSqr>>8;
		}
		
	}
	
	return board;
	
}
