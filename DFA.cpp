#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include<stdexcept>
#include"DFA.h"

using namespace std;

DFA::DFA(fstream& fstrm) {
    //delete empty lines 
    string line;
    int count = 0;//find the number of non-empty lines
    vector<string> lines;
    while (getline(fstrm, line) && !fstrm.eof()) {
        if (!(line.empty() || line.find_first_not_of(' ') == string::npos)) {
            lines.push_back(line);
            count++;
        }
    }

    if (count < 5) {
        throw invalid_argument("Invalid Input");
    }

   
        istringstream strm(lines[0]);
        for (int i = 0; i < 4; i++) {
            if (!strm >> inputSymbol[i]) {
                throw invalid_argument("Invalid Input");
            }
        }


        strm.clear();
        strm>>lines[1];
        for (int i = 0; i < 2; i++) {
            if (!strm >> outputSymbol[i]) {
                throw invalid_argument("Invalid Input");
            }
        }



        //delete all spaces from line 2
        remove_if(lines[2].begin(), lines[2].end(), isspace);
        if (lines[2] != "q0,q1") {
            throw invalid_argument("Invalid Input");
        }

        parseFunction(lines[3], 0);
        parseFunction(lines[4], 1);

}

void DFA::parseFunction(string& str, int state) {

    //delete all spaces from line 3
    remove_if(str.begin(), str.end(), isspace);
    for (int i = 0; i < str.size(); i++) {
        if ((i == 0 || str[i - 1] == '|') && i < str.size() - 3) {
            char sym = str[i];
            int num = str[i + 3] - '0';

            //check that char symbol belongs to output symbols set
            if (sym != outputSymbol[0] && sym != outputSymbol[1]) {
                throw invalid_argument("Invalid Input");
            }
            else if (str[i + 1] != ',' || str[i + 2] != 'q') {
                throw invalid_argument("Invalid Input");
            }
            else if (str[i + 3] - '0' > 1 || str[i + 3] - '0' < 0) {
                throw invalid_argument("Invalid Input");
            }

            else {
                writeSymbol[make_pair(inputSymbol[i], state)] = sym;
                changeState[make_pair(inputSymbol[i], state)] = num;

            }
        }
    }


}

string DFA::run(string& str) {

    int len = str.size();

    string answer;

    char curSymbol = writeSymbol[make_pair(str[0], 0)];
    int curState = changeState[{str[0], 0}];

    answer.push_back(curSymbol);

    for (int i = 1; i < len; i++) {
        curSymbol = writeSymbol[make_pair(str[0], curState)];
        answer.push_back(curSymbol);
        curState = changeState[make_pair(str[0], 0)];
    }

    return answer;
}

