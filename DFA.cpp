#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include<stdexcept>
#include<set>
#include<algorithm>
#include"DFA.h"

using namespace std;

DFA::DFA(string& fileName) {
    //delete empty lines from text file
    ifstream in(fileName);
    string line;
    vector<string> lines;

    if (in.is_open()) {
        while (getline(in, line)) {
            if (!(line.empty() || line.find_first_not_of(' ') == string::npos)) {
                lines.push_back(line);
            }
        }
    }

    in.close();

    //keep the number of lines
    int count = lines.size();
  
    if (count < 5) {
        throw invalid_argument("Invalid Text Format: Not Enough Information");
    }

    //check input symbols
    lines[0].erase(remove(lines[0].begin(), lines[0].end(),' '), lines[0].end());//remove whitespaces
    lines[0].erase(remove(lines[0].begin(), lines[0].end(), ','), lines[0].end());//remove ,
   
    if (lines[0].size() != 4) {
        throw invalid_argument("failed to read input symbols");
    }
    else {
        //check that all 4 charcters of string are distinct
        set<char> s;
        for (int i = 0; i < 4; i++) {
            if (s.find(lines[0][i]) != s.end()) {
                throw invalid_argument("input symbols should be distinct");
            }
        }
        for (int i = 0; i < 4; i++) {
            inputSymbol[i] = lines[0][i];
        }
    }
 
    //check output symbols
    lines[1].erase(remove(lines[1].begin(), lines[1].end(), ' '), lines[1].end());
    lines[1].erase(remove(lines[1].begin(), lines[1].end(), ','), lines[1].end());
    if(lines[1].size()>2 || lines[1].size()<1 )
        throw invalid_argument("failed to read output symbols");

    if (lines[1].size() == 1) outputSymbol[0] = lines[1][0];
    else if (lines[1][0] == lines[1][1]) outputSymbol[0] = lines[1][0];
    else outputSymbol[0] = lines[1][0], outputSymbol[1] = lines[1][1];

    //check states
    lines[2].erase(remove(lines[2].begin(), lines[2].end(), ' '), lines[2].end());
    lines[2].erase(remove(lines[2].begin(), lines[2].end(), ','), lines[2].end());
    if(lines[2]!="q0q1")
        throw invalid_argument("failed to read automaton states");

    parseFunction(lines[3], 0);
    parseFunction(lines[4], 1);

 }


void DFA::parseFunction(string& str, int state) {

    //delete all whitespaces,'|',',' symbols
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '|'), str.end());
    str.erase(remove(str.begin(), str.end(), ','), str.end());

    int len = str.size();
    if (len !=12) {
        throw invalid_argument("Wrong Function Input");
    }
    
    for (int i = 0; i < len; i+=3) {
        bool flag = false;
        for (int i = 0; i < 4; i++) {
            if (str[i] == inputSymbol[i]) flag = false;
        }
        if (flag) {
            throw invalid_argument("Wrong Function Input");
        }
    }

    for (int i = 0; i < len; i+=3) {
        if (str[i + 1] != 'q') {
            throw invalid_argument("Wrong Function Input");
        }
    }

    for (int i = 0; i < len; i += 3) {
        int num = str[i + 2] - '0';
        if (num!=0 && num!=1) {
            throw invalid_argument("Wrong Function Input");
        }
    }

    for (int i = 0; i < len; i += 3) {
        char sym = str[i];
        int num = str[i + 2] - '0';
        writeSymbol[make_pair(inputSymbol[i / 3], state)] = sym;
        changeState[make_pair(inputSymbol[i / 3], state)] = num;
       
    }

}



string DFA::run(string& str) {

    int len = str.size();

    string answer;

    char curSymbol = writeSymbol[make_pair(str[0], 0)];
    int curState = changeState[make_pair(str[0], 0)];

    answer.push_back(curSymbol);

    for (int i = 1; i < len; i++) {
        curSymbol = writeSymbol[make_pair(str[i], curState)];
        answer.push_back(curSymbol);
        curState = changeState[make_pair(str[i], 0)];
    }

    return answer;
}
