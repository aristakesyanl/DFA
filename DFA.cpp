#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<stdexcept>
#include"DFA.h"

using namepsace std;

DFA::DFA(fstream& fstrm){
    //delete empty lines 
    string line, text;
    int count=0;//find the number of non-empty lines
    vector<string> lines;
    while(getline(fstrm, line) && !fstrm.eof()){
        if(!(line.empty() || line.find_first_not_of(' ')==string::npos)){
            lines.push_back(line);
            count++;
        }
    }
    
    if(count!=5){
        throw SomeException("Invalid Input");
    }

    else{
        istringstream strm(lines[0]);
        for(int i=0; i<4; i++){
            if(!strm>>inputSymbol[i]){
                throw SomeException("Invalid Input");
            }
        }


        strm.clear();
        strm(lines[1]);
        for(int i=0; i<2; i++){
            if(!strm>>outputSymbol[i]){
                throw SomeException("Invalid Input");
            }
        }

       

        //delete all spaces from line 2
        erase_all(lines[2]," ");
        if(lines[2]!="q0,q1"){
            throw SomeException("Invalid Input")
        }

        parseFunction(lines[3], 0);
        parseFunction(lines[3], 1);

    }
}

void DFA::parseFunction(string& str, int state){

    //delete all spaces from line 3
    erase_all(str, " ");
    for(int i=0; i<str.size(); i++){
        if((i==0 || str[i-1]=='|') && i<str.size()-3){
            char sym=str[i];
            int num=str[i+3]-'0';

            //check that char symbol belongs to output symbols set
            if(sym!=outputSymbol[0] && sym!=outputSymbol[1]){
                throw SomeException("Invalid Input");
            } 
            else if(str[i+1]!=',' || str[i+2]!='q'){
                throw SomeException("Invalid Input");
            }
            else if(str[i+3]-'0'>1 || str[i+3]-'0'<0){
                throw SomeException("Invalid Input");
            }
            
            else{
                writeSymbol.[make_pair(inputSymbol[i],state)]=sym;
                changeState.[make_pair(inputSymbol[i],state)]=num;

            }
        }
    }

  
}

string DFA::run(string& str) const{

    int len=str.size();

    string answer;

    char curSymbol=writeSymbol[{str[0],0}];
    int curState=changeState[{str[0],0}];

    answer.push_back(curSymbol);

    for(int i=1; i<len; i++){
        curSymbol=wrtiteSymbol[{str[0],curState}];
        answer.push_back(curSymbol);
        curState=chnageState[{str[0], 0}];
    }

    return answer;
}


int main(int argc, char* argv[]){
    if(argc>=1){
        cout<<"No Argument Provided"<<endl;
    }
    else{
        vector<string> s;
        for(int i=1; i<argc; i++){
            s.push_back(argv[i]);
        }

        fstream fstrm;

        for(int i=0; i<s.size(); i++){

            fstrm.open(s[i]);
            if(fstrm.is_open()){
                DFA a(fstrm);
            }
            else{
                cerr<<"Failed to read text file"<<endl;
            }
            fstrm.close();

        }
    }

}