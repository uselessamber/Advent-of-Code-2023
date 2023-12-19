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

struct item{
    int x, m, a, s;
    string location;
    item(string inp = "{x=0,m=0,a=0,s=0}", string location = "A"){
        int ptr = 3;
        this->x = to_int(inp, ptr);
        ptr += 3;
        this->m = to_int(inp, ptr);
        ptr += 3;
        this->a = to_int(inp, ptr);
        ptr += 3;
        this->s = to_int(inp, ptr);
        this->location = location;
    }
    int summation(){
        return this->x + this->m + this->a + this->s;
    }
};

bool passed(condition &c, item &o){
    if (c.always_true) return true;
    int val;
    switch (c.type){
        case 'x':
            val = o.x;
            break;
        case 'm':
            val = o.m;
            break;
        case 'a':
            val = o.a;
            break;
        case 's':
            val = o.s;
            break;
    }
    switch (c.comp){
        case '<':
            return val < c.value;
        case '=':
            return val == c.value;
        case '>':
            return val > c.value;
    }
    return false;
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

map <string, workflow> workflow_map;
vector <item> item_list;

void next_workflow(item &o, workflow &w){
    for (condition c : w.rules){
        if (passed(c, o)){
            o.location = c.target;
            break;
        }
    }
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
            item_list.PB(item(line, "in"));
        }
    }
    int ans = 0;
    for (item i : item_list){
        while (i.location != "A" && i.location != "R"){
            next_workflow(i, workflow_map[i.location]);
        }
        if (i.location == "A") ans += i.summation();
    }
    cout << ans;
    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}