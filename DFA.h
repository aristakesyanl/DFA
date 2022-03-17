#include<string>
#include<map>
#include<fstream>

using namespace std;

/***********************************************************************
* 
 * Header file defines a class of Deterministic Finite Automaton
 * It recerives an input text file, which contains an information about 
 * Deterministic Finite Automaton and configures such.
 * We can run the machine with the help of class method run(), which runs
 * corresponding string on the machine and return the result
 * 
 * *********************************************************************/
#ifndef DFA_H
#define DFA_H
class DFA {
public:
	DFA(string&);
	string run(string&);
private:
	char inputSymbol[4]; //set of input symbols
	char outputSymbol[2];//set of output symbols
	map<pair<char, int>, char> writeSymbol;//function that returns symbol to be written in output string
	map<pair<char, int>, int> changeState;//function that return the state the autamaton is going to change
	void parseFunction(string&, int);

};

#endif

