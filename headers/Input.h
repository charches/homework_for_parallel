#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

class Input {
        public:
                string cal;
                string mat_type;
                int nr = 0, nc = 0;
                int mat_prt = 0;

                Input();
                Input(const string& filename);
                friend ostream& operator<<(ostream& my_cout, const Input& input);
                friend void to_lower(string& str);
};

#endif
