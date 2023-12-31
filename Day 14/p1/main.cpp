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
vector <string> input;
int row_count, col_count;
vi space_count;

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code

    string txt;
    while (cin >> txt){
        row_count += 1;
        col_count = txt.length();
        input.PB(txt);
    }
    space_count.assign(col_count, 0);
    int ans = 0;
    for (int r = 0; r < row_count; r++){
        for (int c = 0; c < col_count; c++){
            switch(input[r][c]){
                case '#':
                    space_count[c] = 0;
                    break;
                case '.':
                    space_count[c]++;
                    break;
                case 'O':
                    ans += (row_count - r) + space_count[c];
                    break;
            }
        }
    }
    cout << ans;

    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}