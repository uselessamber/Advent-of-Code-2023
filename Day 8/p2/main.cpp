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
#include <set>
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
typedef pair<int, pii> piii;
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
vector <string> str_list;
int len = 0;

int get_idx(string inp){
    if (dict.find(inp) == dict.end()){
        connect_map.PB(pii(0, 0));
        str_list.PB(inp);
        dict[inp] = len++;
    }
    return dict[inp];
}

set <int> s;
set <int> e;
vi current;
vector<vector<piii>> g;
vector <vector <bool>> visit;

ll gcd(ll a, ll b){
    while (b != 0){
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ll lcm(ll a, ll b){
    return (a * b) / gcd(a, b);
}

void to_nearest_z(int pos, int step){
    int step_count = 0;
    int spos = pos, sstep = step;
    if (g[spos][sstep] != piii(0, pii(0, 0))) return;
    visit.assign(len(str_list), vector<bool>(instruction.length(), false));
    do{
        switch (instruction[step]){
            case 'L':
                pos = connect_map[pos].FS;
                break;
            case 'R':
                pos = connect_map[pos].SC;
                break;
        }
        step = (step + 1) % instruction.length();
        if (!visit[pos][step]){
            visit[pos][step] = true;
        }else{
            step_count = -1;
            break;
        }
        step_count++;
    }while (e.find(pos) == e.end());
    g[spos][sstep] = piii(step_count, pii(pos, step));
}

int main(){
    auto start = chrono::high_resolution_clock::now();
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
        if (a[2] == 'A'){
            s.insert(ia);
        }
        if (c[2] == 'A'){
            s.insert(ib);
        }
        if (d[2] == 'A'){
            s.insert(ic);
        }
        if (a[2] == 'Z'){
            e.insert(ia);
        }
        if (c[2] == 'Z'){
            e.insert(ib);
        }
        if (d[2] == 'Z'){
            e.insert(ic);
        }
        connect_map[ia] = pii(ib, ic);
    }

    g.assign(len(str_list), vector<piii>(instruction.length(), piii(0, pii(0, 0))));

    ll max_step = 1;
    for (set <int>::iterator ptr = s.begin(); ptr != s.end(); ptr++){
        to_nearest_z(*ptr, 0);
        max_step = lcm(g[*ptr][0].FS, max_step);
    }
    cout << max_step;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}