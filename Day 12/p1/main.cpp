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

int string_to_int(string inp){
    int ans = 0;
    for (char c : inp){
        ans *= 10;
        ans += int(c - '0');
    }
    return ans;
}

vi splitter(string inp){
    vi output;
    string part = "";
    for (char c : inp){
        if (c != ',') part = part + c;
        else{
            output.PB(string_to_int(part));
            part = "";
        }
    }
    if (part != "")
        output.PB(string_to_int(part));
    return output;
}

string s;
vi a;
int s_len, a_len;
vector <vector <ll>> dp; // dp[l][p] : l = position in the string, p = string group

void dp_init(){
    s_len = s.length();
    a_len = len(a);
    dp.assign(s_len + 1, vector <ll>(a_len + 1, -1));
}

ll dpf(int l, int p){
    if (l >= s_len){
        if (p >= a_len) return dp[s_len][a_len] = 1;
        else return dp[s_len][a_len] = 0;
    }
    if (dp[l][p] != -1) return dp[l][p]; // if val == -1, unvisit.
    if (s[l] == '.'){
        return dp[l][p] = dpf(l + 1, p);
    }
    if (s[l] == '#'){
        bool valid = true;
        if (p >= a_len) valid = false;
        else
            for (int i = 1; i < a[p]; i++){
                if (s[l + i] == '.') valid = false;
            }
        if (valid && s[l + a[p]] != '#'){
            return dp[l][p] = dpf(l + a[p] + 1, p + 1);
        }else{
            return dp[l][p] = 0;
        }
    }
    if (s[l] == '?'){
        ll sum = 0;
        bool valid = true;
        if (p >= a_len) valid = false;
        else
            for (int i = 1; i < a[p]; i++){
                if (s[l + i] == '.') valid = false;
            }
        if (valid && s[l + a[p]] != '#'){
            sum += dpf(l + a[p] + 1, p + 1);
        }
        sum += dpf(l + 1, p);
        return dp[l][p] = sum;
    }
    return dp[l][p] = 0;
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    string tmp;
    ll ans = 0;
    while (cin >> s >> tmp){
        a = splitter(tmp);
        dp_init();
        s = s + '.';
        ans += dpf(0, 0);
    }
    cout << ans << "\n";
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}