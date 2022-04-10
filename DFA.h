
#include<string>
#include<map>

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
    DFA(std::string&);
    std::string run(std::string&);
private:
    std::vector<char> inputSymbol; //set of input symbols
    std::set<char> sInput;
    std::vector<char> outputSymbol;//set of output symbols
    std::set<char> sOutput;
    std::vector<int> states;//set of internal states
    std::set<int> sStates;
    std::map<std::pair<char, int>, char> writeSymbol;//function that returns symbol to be written in output string
    std::map<std::pair<char, int>, int> changeState;//function that return the state the autamaton is going to change
    void parseInput(std::string);
    void parseOutput(std::string);
    void parseStates(std::string);
    void parseFunction(std::string, int);
};

#endif
