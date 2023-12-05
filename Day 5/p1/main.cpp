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

ll str_to_int(string &s){
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

vector <ll> seeds;
vector <ll> temp_seeds;

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
        ll num = str_to_int(inp);
        seeds.PB(num);
        temp_seeds.PB(num);
    }
    while (cin >> inp){
        if (!is_number(inp)){
            seeds = temp_seeds;
            continue;
        }
        ll l_end, r_end, l_start, r_start, l, d;
        l_end = str_to_int(inp);
        cin >> inp;
        l_start = str_to_int(inp);
        cin >> inp;
        l = str_to_int(inp);
        r_end = l_end + l - 1;
        r_start = l_start + l - 1;
        d = l_end - l_start;
        for (int i = 0; i < len(seeds); i++){
            if (l_start <= seeds[i] && seeds[i] <= r_start){
                temp_seeds[i] = seeds[i] + d;
            }
        }
    }
    seeds = temp_seeds;
    ll ans = INF64;
    for (ll seed : seeds){
        cout << seed << " ";
        ans = min(ans, seed);
    }
    cout << "\n" << ans << "\n";
}