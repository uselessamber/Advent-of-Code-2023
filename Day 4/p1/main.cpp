#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <chrono>
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

void tokenizer(string &inp, vector <string>&tokens, char splitter = ' '){
    tokens.clear();
    tokens.push_back("");
    int top = 1;
    for (char c : inp){
        if (c == splitter){
            if (tokens[top - 1].length() == 0) continue;
            top += 1;
            tokens.PB("");
        }else{
            tokens[top - 1] = tokens[top - 1] + c;
        }
    }
}

int str_to_int(string &s){
    int val = 0;
    for (char c : s){
        val *= 10;
        val += c - '0';
    }
    return val;
}

string text;
set <int> winning_number;
int answer = 0;

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    while (getline(cin, text)){
        vector <string> game;
        tokenizer(text, game);
        int n = len(game);
        bool hand_mode = false;
        int found_win = 0;
        for (int i = 2; i < n; i++){
            if (game[i] == "|"){
                hand_mode = true;
                continue;
            }
            int curr = str_to_int(game[i]);
            if (!hand_mode){
                winning_number.insert(curr);
            }else{
                if (winning_number.find(curr) != winning_number.end())
                    found_win = ((found_win == 0)? 1 : found_win * 2);
            }
        }
        answer += found_win;
        winning_number.clear();
    }
    cout << answer;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}