#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ios>

#define WHITE          "\x1b[38m"
#define CYAN           "\x1b[36m"
#define RED            "\x1b[31m"
#define BLUE           "\x1b[38;5;63m"
#define GREEN          "\x1b[32m"
#define PURPLE         "\x1b[38;2;190;82;125m"
#define COLORENDS      "\x1b[0m"
#define BALD           "\x1b[1m"
#define U using std::

U string;
U cout;

const char* tokens[] = {"(", ")" , "^" , "sqrt" , "*" , "+" , "/" , "-" , NULL };

struct node{
    node *Left, *Right;
    string s;
};

struct Run_tree{
    Run_tree *left , *right ;
    string s = nullptr;
    bool is_a_token;
};

int FindString(string str, const char** list) {
    int i = 0;
    while (list[i]) {
        int temp = str.find(list[i]);
        if (temp!=std::string::npos) return temp;
        i++;
    }
    return -1;
}

Run_tree* AddNode (const bool Is_Token, const string S){
    Run_tree *tree = new Run_tree;
    tree -> left = tree->right = nullptr;
    tree -> s = S;
    tree -> is_a_token = Is_Token;
    return tree;
}

Run_tree* Build_Tree (string &line) {
    int t = FindString(line, tokens);
    if (t >= 0){
        string s1 = line;
        int n = 1, i = t+1;
        Run_tree* tree;
        switch (line[t]) {
        case '(':
            while (n) {
                if (line[i] == '(') ++n;
                if (line[i] == ')') --n;
                i++;
            }
            s1.erase(0,i);
            line.erase(i-1, line.length());
            line.erase(0 , 0);
            if (line[i]) {
                tree = AddNode(true, std::string(1, line[i]));
                tree -> left = Build_Tree(line);
                tree -> right = Build_Tree(s1);    
            }
            break;
        default:
            tree = AddNode(true, std::string(1, line[t]));
            s1.erase(0,t);
            line.erase(i-1, line.length());
            tree -> left = Build_Tree(line);
            tree -> right = Build_Tree(s1);    
            break;
        }
    } else return AddNode(false, line);
    return 0;
}

float Handler(string line){
    float temp;
    int t = FindString(line, tokens);
    if (t >= 0){
        string s1 = line;
        int n = 1, i = t+1;
        Run_tree* tree;
        switch (line[t]) {
        case '(':
            while (n) {
                if (line[i] == '(') ++n;
                if (line[i] == ')') --n;
                i++;
            }
            s1.erase(i,s1.length());
            s1.erase(0,t+1);
            line.erase(t,i);
            line.insert(t ,std::to_string(Handler(s1)));
            break;
        case '*':
            while (((std::isdigit(line[i]))||('.'))&&(line[i])) ++i;
            n=t;
            while (((std::isdigit(line[i]))||('.'))&&(n)) --n;
            
            s1.erase(t , s1.length());
            s1.erase(0 , n+1);
            temp = std::stof(s1);
            s1 = line;
            s1.erase(i , s1.length());
            s1.erase(0 , t+1);
            temp *= std::stof(s1);
        }
}

bool CheckLine(string &line) {
    int i = 0, n = 0;
    //std::stack <char> St;
    while (line[i]) {
        if (line[i] == '(') ++n;
        if (line[i] == ')') --n;
        if (line[i] == ',') line[i] = '.';
        if (line[i] == ' ') line.erase(i);
        if (n < 0) {
            cout << RED << "PLease check brackets\n" << COLORENDS;
            return 0;
        }
        ++i;
    }
    if (n) {
        cout << RED << "PLease check brackets\n" << COLORENDS;
        return 0;
    }
    return 1;
}

int main(int argc, char const *argv[]) {

    U cin;
    
    string line;
    /* code */
    cout << GREEN "This is calculator\n" << COLORENDS << "Please enter equation," << PURPLE << " for exit use EOF (Ctrl+D)\n"<< COLORENDS;
    while (std::getline(cin, line)) {
        Run_tree *tree;
        if (CheckLine(line)) {
            tree = Build_Tree(line);
        }
        std::cout << std::stof(line) << std::endl;
    }

    return 0;
}
