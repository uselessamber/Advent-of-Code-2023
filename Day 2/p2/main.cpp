#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <time.h>
#include <math.h>
#include <iomanip>
#define fileio(name) freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout)
#define len(v) (int)v.size()
#define FS first
#define SC second
#define PB push_back
#define LSOne(i) i & (-i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
const bool open_file = true;
const int N = 1e6 + 7;
const int INF = 1e9 + 7;
const double EPS = 1e-9;
const ll INF64 = 1e16 + 7;
int divceil(int x, int y){
    return 1 + ((x - 1) / y);
}
//stuff to declare
string line;
vector <string> tokens;

void tokenizer(string &inp, char splitter = ' '){
    tokens.clear();
    tokens.push_back("");
    int top = 1;
    for (char c : inp){
        if (c == splitter){
            top += 1;
            tokens.push_back("");
        }else{
            tokens[top - 1] = tokens[top - 1] + c;
        }
    }
}

bool is_number(string &s){
    for (char c : s){
        if (!isdigit(c)) return false;
    }
    return true;
}

int str_to_int(string &s){
    int val = 0;
    for (char c : s){
        val *= 10;
        val += c - '0';
    }
    return val;
}

int color_to_id(string s){
    switch (s[0]){
        case 'r':
            return 0;
        case 'g':
            return 1;
        case 'b':
            return 2;
    }
    return -1;
}

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    ll final_sum = 0;
    int game_id = 0;
    ll cube = 0;
    ll color_cube[3] = {};
    while (getline(cin, line)){
        tokenizer(line);
        for (string token : tokens){
            if (token == "Game"){
                final_sum += color_cube[0] * color_cube[1] * color_cube[2];
                color_cube[0] = color_cube[1] = color_cube[2] = 0;
                cube = 0;
                continue;
            }
            if (token[token.length() - 1] == ':'){
                int val = 0;
                for (int i = 0; i < token.length() - 1; i++){
                    val *= 10;
                    val += token[i] - '0';
                }
                game_id = val;
            }else{
                if (is_number(token)){
                    cube = str_to_int(token);
                }else{
                    color_cube[color_to_id(token)] = max(color_cube[color_to_id(token)], cube);
                }
            }
        }
    }
    final_sum += color_cube[0] * color_cube[1] * color_cube[2];
    cout << final_sum;
}