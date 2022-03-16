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
        vector<string> s;
        for (int i = 1; i < argc; i++) {
            s.push_back(argv[i]);
        }

        fstream fstrm;

        for (int i = 0; i < s.size(); i++) {

            fstrm.open(s[i]);
            if (fstrm.is_open()) {
                DFA a(fstrm);
                string ss = "aaaa";
                cout << a.run(ss) << endl;;
            }
            else {
                cerr << "Failed to read text file" << endl;
            }
            fstrm.close();

        }
    }

}
