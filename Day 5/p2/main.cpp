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

ull str_to_int(string &s){
    ll val = 0;
    for (char c : s){
        val *= 10;
        val += c - '0';
    }
    return val;
}

bool is_number(string &s){
    for (char c : s){
        if (!isdigit(c)) return false;
    }
    return true;
}

struct split{
    ll l;
    ll r;
    ll d;
    split(ll il, ll ir, ll id){
        this->l = il;
        this->r = ir;
        this->d = id;
    }
};

vector <pll> seeds;
vector <split> split_list;
vector <pll> new_seeds;
//vector <pll> temp_seeds;

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    string inp;
    cin >> inp;
    while (cin >> inp){
        if (!is_number(inp)){
            break;
        }
        ll start = str_to_int(inp);
        cin >> inp;
        ull length = str_to_int(inp);
        seeds.PB(pll(start, start + length - 1));
        //temp_seeds.PB(pll(start, start + length - 1));
    }
    while (cin >> inp){
        if (!is_number(inp)){
            //seeds = temp_seeds;
            new_seeds.clear();
            for (pll seed : seeds){
                pll curr = seed;
                bool skip = false;
                //if (curr.FS < 0 || curr.SC < 0) continue;
                for (split s : split_list){
                    if (curr.SC < curr.FS || skip) break;
                    if (curr.SC < s.l || s.r < curr.FS) continue;
                    if (s.l <= curr.FS && curr.SC <= s.r){
                        new_seeds.PB(pll(curr.FS + s.d, curr.SC + s.d));
                        skip = true;
                        continue;
                    }
                    if (curr.FS < s.l && curr.SC <= s.r){
                        new_seeds.PB(pll(s.l + s.d, curr.SC + s.d));
                        curr.SC = s.l - 1;
                        continue;
                    }
                    if (s.l <= curr.FS && s.r < curr.SC){
                        new_seeds.PB(pll(curr.FS + s.d, s.r + s.d));
                        curr.FS = s.r + 1;
                        continue;
                    }
                    if (curr.FS < s.l && s.r < curr.SC){
                        new_seeds.PB(pll(s.l + s.d, s.r + s.d));
                        seeds.PB(pll(curr.FS, s.l - 1));
                        seeds.PB(pll(s.r + 1, curr.SC));
                        skip = true;
                        continue;
                    }
                }
                if (curr.FS <= curr.SC && !skip) new_seeds.PB(curr);
            }
            seeds = new_seeds;
            split_list.clear();
            continue;
        }
        ll l_end, l_start, r_start, l, d;
        l_end = str_to_int(inp);
        cin >> inp;
        l_start = str_to_int(inp);
        cin >> inp;
        l = str_to_int(inp);
        r_start = l_start + l - 1;
        d = l_end - l_start;
        split new_split(l_start, r_start, d);
        // Split sanitization process
        /*
        bool conflict = false;
        for (int i = 0; i < len(split_list); i++){
            if (new_split.r < split_list[i].l || split_list[i].r < new_split.l) continue;
            conflict = true;

            if (new_split.l <= split_list[i].l && split_list[i].r <= new_split.r){
                split_list[i] = new_split;
                continue;
            }

            if (split_list[i].l < new_split.l && split_list[i].r <= new_split.r){
                split_list[i].r = new_split.l - 1;
                conflict = false;
                continue;
            }

            if (new_split.l <= split_list[i].l && new_split.r < split_list[i].r){
                split_list[i].l = new_split.r + 1;
                conflict = false;
                continue;
            }

            if (split_list[i].l < new_split.l && new_split.r < split_list[i].r){
                split left_side(split_list[i].l, new_split.l - 1, split_list[i].d);
                split right_side(new_split.r + 1, split_list[i].r, split_list[i].d);
                split_list.PB(left_side);
                split_list.PB(right_side);
                split_list[i] = new_split;
                continue;
            }
        }*/
        //if (!conflict){
            split_list.PB(new_split);
        //}
    }
    new_seeds.clear();
    for (pll seed : seeds){
        pll curr = seed;
        bool skip = false;
        //if (curr.FS < 0 || curr.SC < 0) continue;
        for (split s : split_list){
            if (curr.SC < curr.FS || skip) break;
            if (curr.SC < s.l || s.r < curr.FS) continue;
            if (s.l <= curr.FS && curr.SC <= s.r){
                new_seeds.PB(pll(curr.FS + s.d, curr.SC + s.d));
                skip = true;
                continue;
            }
            if (curr.FS < s.l && curr.SC <= s.r){
                new_seeds.PB(pll(s.l + s.d, curr.SC + s.d));
                curr.SC = s.l - 1;
                continue;
            }
            if (s.l <= curr.FS && s.r < curr.SC){
                new_seeds.PB(pll(curr.FS + s.d, s.r + s.d));
                curr.FS = s.r + 1;
                continue;
            }
            if (curr.FS < s.l && s.r < curr.SC){
                new_seeds.PB(pll(s.l + s.d, s.r + s.d));
                seeds.PB(pll(curr.FS, s.l - 1));
                seeds.PB(pll(s.r + 1, curr.SC));
                skip = true;
                continue;
            }
        }
        if (curr.FS <= curr.SC && !skip) new_seeds.PB(curr);
    }
    seeds = new_seeds;
    //seeds = temp_seeds;
    ull ans = INF64;
    for (pll seed : seeds){
        cout << seed.FS << " - " << seed.SC << " | ";
        ans = min(ans, seed.FS);
    }
    cout << "\n" << ans << "\n";
}