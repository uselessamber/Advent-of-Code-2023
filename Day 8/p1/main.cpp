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

string instruction;
map <string, int> dict;
vector <pii> connect_map;
vector <string> num_to_str;
int len = 0;

int get_idx(string inp){
    if (dict.find(inp) == dict.end()){
        connect_map.PB(pii(0, 0));
        num_to_str.PB(inp);
        dict[inp] = len++;
    }
    return dict[inp];
}

int s;
int e;

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    cin >> instruction;
    string a, b, c, d;
    while(cin >> a >> b >> c >> d){
        c = c.substr(1, 3);
        d = d.substr(0, 3);
        int ia = get_idx(a), ib = get_idx(c), ic = get_idx(d);
        if (a == "AAA"){
            s = ia;
        }
        if (c == "AAA"){
            s = ib;
        }
        if (d == "AAA"){
            s = ic;
        }
        if (a == "ZZZ"){
            e = ia;
        }
        if (c == "ZZZ"){
            e = ib;
        }
        if (d == "ZZZ"){
            e = ic;
        }
        connect_map[ia] = pii(ib, ic);
    }
    int pos = 0;
    int step = 0;
    int curr = s;
    while (curr != e){
        switch (instruction[pos]){
            case 'L':
                curr = connect_map[curr].FS;
                break;
            case 'R':
                curr = connect_map[curr].SC;
                break;
        }
        pos = (pos + 1) % instruction.length();
        step ++;
    }
    cout << step;
}