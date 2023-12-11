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
int R, C;
vector <pii> galaxy_pos;
vector <bool> is_row_empty, is_column_empty;
vector <ll> empty_row_count, empty_column_count;

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    string inp;
    bool first_loop = true;
    is_row_empty.PB(true);
    while (cin >> inp){
        R += 1;
        C = inp.length();
        if (first_loop){
            is_column_empty.assign(C + 1, true);
            first_loop = false;
        }
        is_row_empty.PB(true);
        for (int i = 1; i <= C; i++){
            if (inp[i - 1] == '#'){
                galaxy_pos.PB(pii(R, i));
                is_column_empty[i] = false;
                is_row_empty[R] = false;
            }
        }
    }
    empty_row_count.assign(R + 1, 0);
    for (int i = 1; i <= R; i++){
        empty_row_count[i] = empty_row_count[i - 1] + is_row_empty[i];
    }
    empty_column_count.assign(C + 1, 0);
    for (int i = 1; i <= C; i++){
        empty_column_count[i] = empty_column_count[i - 1] + is_column_empty[i];
    }
    ll ans = 0;
    for (int i = 0; i < len(galaxy_pos) - 1; i++){
        for (int j = i + 1; j < len(galaxy_pos); j++){
            int max_r = max(galaxy_pos[i].FS, galaxy_pos[j].FS);
            int min_r = min(galaxy_pos[i].FS, galaxy_pos[j].FS);
            int max_c = max(galaxy_pos[i].SC, galaxy_pos[j].SC);
            int min_c = min(galaxy_pos[i].SC, galaxy_pos[j].SC);
            ans += (
                ((max_r - min_r) + (empty_row_count[max_r] - empty_row_count[min_r - 1])) + 
                ((max_c - min_c) + (empty_column_count[max_c] - empty_column_count[min_c - 1]))
            );
        }
    }
    cout << ans;
}