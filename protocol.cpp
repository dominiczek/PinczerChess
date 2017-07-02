#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

#include "fenParser.h"

using namespace std;

int main3(int argc, char** argv) {
	
	cout<<fieldCodeToField("a1");
	
	string line;
	while(true) {
		
		getline(cin, line);
		
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);

		if(line.find("uci") == 0) {
			cout<<"id name Pinczer"<<endl;
			cout<<"id author Dominik Kunicki";
			
			//send option here
			cout<<"uciok"<<endl;
		}
		if(line.find("debug") == 0) {
		
		}
		if(line.find("isready") == 0) {
			// create engine
			cout<<"readyok"<<endl;
		}
		if(line.find("setoption name ") == 0) {
			
		}
		if(line.find("register") == 0) {
			
		}
		if(line.find("ucinewgame") == 0) {
			// new game has started
		}
		if(line.find("position") == 0) {
			
			
			
		}	
		if(line.find("go") == 0) {
			
		}
		if(line.find("stop") == 0) {
			
		}
		if(line.find("ponderhit") == 0) {
			
		}
		if(line.find("quit") == 0) {
			
		}
	
	}
}
