#include<string>
#include<map>
#include<fstream>

using namespace std;

/***********************************************************************
 * Header file defines a class of Deterministic Finite Automaton
 * It recerives an input text file, which contains an information about
 * 
 * 
 * 
 * 
 * *********************************************************************/

#ifndef DFA_H
#define DFA_H
class DFA{
public:
	DFA(fstream&);
	string run(string&)const;
private:
	char inputSymbol; //set of input symbols
	char outputSymbol;//set of output symbols
	map<pair<char, int>, char> writeSymbol;//function that returns symbol to be written in output string
    map<pair<char, int>, int> changeState;//function that return the state the autamaton is going to change
    void parseFuncion(string&);

};

#endif