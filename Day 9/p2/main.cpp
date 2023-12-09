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
#include <sstream>
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

vector<vector <ll>> arr;
int n;
ll ans = 0;

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    string line;
    while (getline(cin, line)){
        arr.clear();
        stringstream ss;
        ss.clear();
        ss << line;
        ll val;
        arr.PB(vector<ll>());
        while (ss >> val){
            arr[0].PB(val);
        }
        reverse(arr[0].begin(), arr[0].end());
        n = len(arr[0]);
        for (int i = 1; i < n; i++){
            arr.PB(vector<ll>(n - i, 0));
            for (int j = 0; j < n - i; j++){
                arr[i][j] = arr[i - 1][j + 1] - arr[i - 1][j];
            }
        }
        arr[n - 1].PB(0);
        for (int i = n - 2; i >= 0; i--){
            arr[i].PB(arr[i][len(arr[i]) - 1] + arr[i + 1][len(arr[i + 1]) - 1]);
        }
        ans += arr[0][len(arr[0]) - 1];
    }
    cout << ans;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}