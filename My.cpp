#include <iostream>
#include <fstream>
#include <deque>
#include <map>
//console colors
#define COLORENDS      "\x1b[0m"
#define GREEN          "\x1b[32m"
#define RED            "\x1b[31m"
#define PURPLE         "\x1b[38;2;190;82;125m"


using std::cin; 
using std::cout;

class N13{
public:
    int Num_in_dex;
    std::string Num_in_str; 
};

int to_int(const char& ch) noexcept {
    switch (ch) {
    case 'A' :
        return 10;
    case 'B' :
        return 11;
    case 'C' :
        return 12;
    default:
        if((ch <= '9')&&(ch >= '0')) return ch - '0';
            std::cerr << RED << "WARNING: undefined behavior\n" << PURPLE << "Check Num format\n" << COLORENDS;
    }
    return 0;
}

bool check_num (const std::string& str) noexcept {
    int i=0, j=str.size()-1,left=0,right=0;
    while (i != j) {
        left += to_int(str[i]);
        right += to_int(str[j]);
        ++i;
        --j;
        if ((i>7)||(j<7)) {
            std::cerr << RED<< "WARNING: undefined behavior\n" << PURPLE << "Wrong count symbol in a num\n" << COLORENDS;
        }
    }
    if(left == right) return true;
    return false;
}

int main(int argc, char const *argv[]) {
    std::ifstream file;
    // открываем файл
    if (argc > 1) {
        file.open(argv[1]);
    } else {
        std::string s1;
        cout << "Write the name of the input file" << std::endl;
        cin >> s1;
        file.open(s1); 
    }
    if (!file.is_open()){
        std::cerr << RED << "Can't open input file\n" << COLORENDS;
        return 1;
    }
    int i=0;
    while (!file.eof()) {
        std::string str;
        file >> str;
        if (str == "") break;
        if(check_num(str)) ++i;
    }
    cout << GREEN << "Result\n" << i << std::endl;  
    return 0;
}

