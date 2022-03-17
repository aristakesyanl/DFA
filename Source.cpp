#include"DFA.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "No Argument Provided" << endl;
    }
    else {
      
        for (int i = 1; i < argc; i++) {

            string str(argv[i]);
            DFA a(str);
            string test = "abdb";
            cout << a.run(test) << endl;;
        }
    }
}
