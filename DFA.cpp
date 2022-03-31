#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include<stdexcept>
#include<set>
#include<algorithm>
#include<regex>
#include"DFA.h"

DFA::DFA(string& fileName) {
    //delete empty lines from text file
    std::ifstream in(fileName);
    std::string line;
    vector<string> lines;

    if (in.is_open()) {
        while (getline(in, line)) {
            if (!(line.empty() || line.find_first_not_of(' ') == std::string::npos)) {
                lines.push_back(line);
            }
        }
    }
    else{
        throw std::runtime_error("Failed To Open Input Files");
    }

    in.close();

    //keep the number of lines
    int count = lines.size();
  
    if (count < 4) {
        throw std::invalid_argument("Invalid Text Format: Not Enough Information");
    }

    //check input symbols
    parseInput(lines[0]);

    
    //check output symbols
    parseOutput(lines[1]);

    //check states
    parseStates(lines[2]);

    //Check that the number of states is no less than lines
    //describing state chnages.
    //In case of additional lines just ignore them
    //It is assumed that the first lines corresponds
    //to the first state given in the state format
    //If for example first states are, q1,q2,q0
    //and input symbols are a,b,d
    //the first line describes correspondingly changes for
    //(q1,a), (q1,b), (q1,d) etc.

    if(count-3<(int)states.size()){
        throw std::invalid_argument("Invalid File Format");
    }



    //check (symbol,state) pairs
    for(int i=3; i<(int)lines.size(); i++){
        parseFunction(lines[i],states[i-3]);
    }
    
 }

void DFA::parseInput(std::string str){
    //remove whitespaces
    str.erase(remove(str.begin(), str.end(),' '), str.end());
    //add ',' at the end of the string to make parsing easier
    str.push_back(',');
    
    //parse to check that every second character is ','
    //string has at least two characters(as we added one at the end)
    //so checking is valid
    for(int i=1;i<(int)str.size();i+=2){
        if(str[i]!=','){
            throw std::invalid_argument("Invalid Input Format");
        }
    }

    //use set to check that string contains distinct characters
    //remove repeating ones
    for(int i=0; i<(int)str.size(); i+=2){
        if(sInput.find(str[i])==sInput.end()){
            inputSymbol.push_back(str[i]);
            sInput.insert(str[i]);
        }

    }
 }


void DFA::parseOutput(std::string str){
    //remove whitespaces
    str.erase(remove(str.begin(), str.end(),' '), str.end());
    //add ',' at the end of the string to make parsing easier
    str.push_back(',');
    
    //parse to check that every second character is ','
    //string has at least two characters(as we added one at the end)
    //so checking is valid
    for(int i=1;i<(int)str.size();i+=2){
        if(str[i]!=','){
            throw std::invalid_argument("Invalid Output Format");
        }
    }

    //use set to check that string contains distinct characters
    //remove repeating ones
    for(int i=0; i<(int)str.size(); i+=2){
        if(sOutput.find(str[i])==sOutput.end()){
            outputSymbol.push_back(str[i]);
            sOutput.insert(str[i]);
        }

    }
 }

 void DFA::parseStates(std::string str){
    //remove whitespaces
    str.erase(remove(str.begin(), str.end(),' '), str.end());
    //add ',' at the end of the string to make parsing easier
    str.push_back(',');

    //Check that States conatin the initial state-q0
    if(str.find("q0")==std::string::npos){
        throw std::invalid_argument("Invalid States Format: Does Not Contain Initial State");
    } 
    
    //States should conatain at least 2 characters
    if((int)str.size()<2){
        throw std::invalid_argument("Invalid States Format");
    }
    
    //States should start with q
    if(str[0]!='q'){
        throw std::invalid_argument("Invalid States Format");
    }


    //check the states do not contain invalid characters
    for(int i=0; i<(int)str.size(); i++){
        if(str[i]!='q' && str[i]!=',' && (str[i]-'0'<0 || str[i]-'0'>10)){
            throw std::invalid_argument("Invalid States Format: Contains non-valid characters");
        }
    }
    
    int init=0;
    std::vector<std::string> result;
    for(int i=1; i<(int)str.size(); i++){
        if(str[i]==','){
            int len=i-init;
            result.push_back(str.substr(init,len));
            init=i+1;
        }
    }

    for(int i=0; i<(int)result.size(); i++){
        if((int)result[i].size()<1) continue;
        if((int)result[i].size()<2 && (int)result[i].size()>0){
            throw std::invalid_argument("Invalid States Format");
        }
        if(result[i][0]!='q'){
                throw std::invalid_argument("Invalid States Format");
        }
        
        //check that States do not contain states of wrong format q01234
        if((int)result[i].size()>2 && result[i][1]=='0'){
            throw std::invalid_argument("Invalid States Format");
        }

        
        std::string number;
        for(int j=1; j<(int)result[i].size(); j++){
            if(result[i][j]-'0'<0 || result[i][j]-'0'>10){
                throw std::invalid_argument("Invalid States Format: Contains non-valid characters");
            }
            else number.push_back(result[i][j]);
        }
        
        int num=stoi(number);
        if(sStates.find(num)==sStates.end()){
            states.push_back(num);
            sStates.insert(num);
        }
    }
 }


void DFA::parseFunction(string str, int state) {

    str.erase(remove(str.begin(), str.end(),' '), str.end());
    str.push_back('|');
    int init=0;
    if((int)str.size()<4){
        throw std::invalid_argument("Invalid Form Of States");
    }
    std::vector<std::string> result;
    for(int i=1; i<(int)str.size(); i++){
        if(str[i]=='|'){
            int len=i-init;
            if(len!=0){
                result.push_back(str.substr(init,len));
            }
            init=i+1;     
        }
    }

    //check that the number of pair is no less than the number of input symbols
    //if number of pairs is more they are just going to be ignored
    if((int)result.size()<(int)inputSymbol.size()){
        throw std::invalid_argument("Not Enough Pairs Given");
    }

    //check that for each pair the length requirement is met
    for(int i=0; i<(int)result.size();i++){
        if(result[i].size()<4){
            throw std::invalid_argument("Invalid (symbol,state) Pair");
        }
    }
    //check that every second character for pair is ','
    for(int i=0; i<(int)result.size();i++){
        if(result[i][1]!=','){
            throw std::invalid_argument("Wrong Form of Character Given In (symbol,state) Pair");
        }
    }

    //check that in all pair symbols are from output
    for(int i=0; i<(int)result.size();i++){
        if(sOutput.find(result[i][0])==sOutput.end()){
            throw std::invalid_argument("Symbol Is Not Contained In Initial Output Set");
        }
    }

    for(int i=0; i<(int)result.size();i++){
        if(result[i][2]!='q'){
            throw std::invalid_argument("Invalid (symbol,state) Pair");
        }
    }

    for(int i=0; i<(int)result.size();i++){
        for(int j=3; j<(int)result[i].size();j++){
            if(result[i][j]-'0'<0 || result[i][j]-'0'>10){
                throw std::invalid_argument("Wrong Character Given in (symbol,state) Pair");
            }
            if((int)result[i].size()>4 && result[i][j]=='0'){
                throw std::invalid_argument("Wrong State Given in (symbol,state) Pair");
            }
        }
    }


    for(int i=0; i<(int)result.size();i++){
        for(int j=3; j<(int)result[i].size();j++){
            int len=(int)result[i].size()-3;
            int num=stoi(result[i].substr(3,len));
            if(sStates.find(num)==sStates.end()){
                throw std::invalid_argument("State Is Not Contained In Initial State List");
            }
            else{
                writeSymbol[std::make_pair(inputSymbol[i],state)]=result[i][0];
                changeState[std::make_pair(inputSymbol[i],state)]=num;
            }
        }
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
