#include"DFA.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
int main(int argc, char* argv[]) {
    
    for (int i = 1; i < argc; i++) {

        std::string str(argv[i]);
        DFA a(str);
        std::string test;
        std::cin>>test;
        std::cout << a.run(test) << std::endl;;
    }
    
}
