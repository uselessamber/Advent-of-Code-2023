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
typedef pair<pii, pii> piiii;
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

struct condition{
    char type;
    char comp;
    int value;
    string target;
    bool always_true = false;
    condition(string inp = "x<0:a", bool always_true = false){
        if (always_true){
            this->type = 0;
            this->comp = 0;
            this->value = 0;
            this->target = inp;
            this->always_true = true;
        }else{
            this->type = inp[0];
            this->comp = inp[1];
            this->value = 0;
            int ptr = 2;
            while (inp[ptr] != ':'){
                this->value *= 10;
                this->value += (inp[ptr] - '0');
                ptr++;
            }
            ptr++;
            while (ptr < inp.length()){
                this->target = this->target + inp[ptr++];
            }
        }
    }
};

int to_int(string inp, int &pos){
    int ans = 0;
    while (pos < inp.length() && inp[pos] != ',' && inp[pos] != '}'){
        ans *= 10;
        ans += (inp[pos] - '0');
        pos++;
    }
    return ans;
}

struct workflow{
    string name;
    vector <condition> rules;
    workflow(string inp = "a{A}"){
        int ptr = 0;
        while (ptr < inp.length() && inp[ptr] != '{'){
            this->name = this->name + inp[ptr];
            ptr++;
        }
        ptr++;
        string cnd = "";
        bool always_true = true;
        while (ptr < inp.length()){
            if (inp[ptr] != ',' && inp[ptr] != '}'){
                cnd = cnd + inp[ptr];
                if (inp[ptr] == '<' || inp[ptr] == '=' || inp[ptr] == '>') always_true = false;
            }else{
                rules.PB(condition(cnd, always_true));
                cnd = "";
                always_true = true;
            }
            ptr++;
        }
    }
};

struct state{ // inclusive-exclusive [l, r]
    pii a[4];
    string pos;
    state(pii x, pii m, pii a, pii s, string pos){
        this->a[0] = x;
        this->a[1] = m;
        this->a[2] = a;
        this->a[3] = s;
        this->pos = pos;
    }
    bool valid(){
        for (int i = 0; i < 4; i++){
            if (this->a[i].FS >= this->a[i].SC) return false;
        }
        return true;
    }
    ll score(){
        ll ans = 1;
        for (int i = 0; i < 4; i++){
            ans *= (ll)(this->a[i].SC - this->a[i].FS + 1);
        }
        return ans;
    }
    bool operator<(const state other) const{
        if (this->pos.compare(other.pos) < 0) return true;
        if (this->pos.compare(other.pos) > 0) return false;
        for (int i = 0; i < 4; i++){
            if (this->a[i] < other.a[i]) return true;
            if (this->a[i] > other.a[i]) return false;
        }
        return false;
    }
    bool operator>(const state other) const{
        if (this->pos.compare(other.pos) > 0) return true;
        if (this->pos.compare(other.pos) < 0) return false;
        for (int i = 0; i < 4; i++){
            if (this->a[i] > other.a[i]) return true;
            if (this->a[i] < other.a[i]) return false;
        }
        return false;
    }
    bool operator==(const state other) const{
        if (this->pos != other.pos) return false;
        for (int i = 0; i < 4; i++){
            if (this->a[i] != other.a[i]) return false;
        }
        return true;
    }
};

map <string, workflow> workflow_map;
map <state, ll> dp;

ll dpf(state s){
    if (dp.find(s) != dp.end()) return dp[s];
    if (!s.valid()) return dp[s] = 0;
    if (s.pos == "R") return dp[s] = 0;
    if (s.pos == "A") return dp[s] = s.score();
    ll ans = 0;
    for (condition c : workflow_map[s.pos].rules){
        int v = 0;
        if (c.always_true){
            s.pos = c.target;
            ans += dpf(s);
        }else{
            switch (c.type){
                case 'x':
                    v = 0;
                    break;
                case 'm':
                    v = 1;
                    break;
                case 'a':
                    v = 2;
                    break;
                case 's':
                    v = 3;
                    break;
            }
            state temp = s;
            switch (c.comp){
                case '<':
                    temp.a[v].SC = min(temp.a[v].SC, c.value - 1);
                    temp.pos = c.target;
                    ans += dpf(temp);
                    s.a[v].FS = c.value;
                    break;
                case '>':
                    temp.a[v].FS = max(temp.a[v].FS, c.value + 1);
                    temp.pos = c.target;
                    ans += dpf(temp);
                    s.a[v].SC = c.value;
                    break;
            }
        }
    }
    return dp[s] = ans;
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    string line;
    while (cin >> line){
        if (line[0] != '{'){
            workflow w(line);
            workflow_map[w.name] = w;
        }else{
            break;
        }
    }
    state initial(pii(1, 4000), pii(1, 4000), pii(1, 4000), pii(1, 4000), "in");
    cout << dpf(initial);
    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}