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
typedef vector<double> vf;
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

string inp;
ll race_time;
ll race_dist;
ll ans;

vf quadratic(double a, double b, double c){ // ax^2 + b^x + c = 0
    double delta = b * b - 4 * a * c;
    vf solution;
    if (delta == 0){
        solution.PB(- b / (2 * a));
    }
    if (delta > 0){
        solution.PB((- b - sqrt(delta)) / (2 * a));
        solution.PB((- b + sqrt(delta)) / (2 * a));
        if (solution[0] > solution[1]){
            double temp = solution[1];
            solution[1] = solution[0];
            solution[0] = temp;
        }
    }
    return solution;
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    bool time_mode = true;
    cin >> inp;
    string patch = "";
    while(cin >> inp){
        if (!is_number(inp)){
            race_time = str_to_int(patch);
            patch = "";
        }else{
            patch = patch + inp;
        }
    }
    race_dist = str_to_int(patch);
    vf sol = quadratic(1.0f, - ((float)race_time), + ((float)race_dist));
    if (!sol.empty()){
        ll l = (int)floor(sol[0] + 1.0);
        ll r = (int)ceil(sol[len(sol) - 1] - 1.0);
        if (r >= l){
            if (ans == 0) ans = 1;
            ans *= r - l + 1;
        }
    }
    cout << ans;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}