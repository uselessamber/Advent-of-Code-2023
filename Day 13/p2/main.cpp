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
vector <vector <bool>> bmap;
int width, height;
int ans;

bool verify_col(int col){
    for (int c = 0; (col + 1 + c < width) && (col - c >= 0); c++){
        for (int r = 0; r < height; r++){
            if (bmap[r][col + 1 + c] != bmap[r][col - c]) return false;
        }
    }
    return true;
}

bool verify_row(int row){
    for (int r = 0; (row + 1 + r < height) && (row - r >= 0); r++){
        for (int c = 0; c < width; c++){
            if (bmap[row + 1 + r][c] != bmap[row - r][c]) return false;
        }
    }
    return true;
}

vi mirror_location(){
    vi output;
    // Check column:
    for (int i = 0; i < width - 1; i++){
        if (verify_col(i)) output.PB(i + 1);
    }
    // Check row:
    for (int i = 0; i < height - 1; i++){
        if (verify_row(i)) output.PB((i + 1) * 100);
    }
    return output;
}

int true_mirror_location(){
    vi temp_ans = mirror_location();
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            bmap[r][c] = !bmap[r][c];
            vi new_ans = mirror_location();
            for (int i : new_ans){
                if (i != 0 && i != temp_ans[0]){
                    return i;
                }
            }
            bmap[r][c] = !bmap[r][c];
        }
    }
    return temp_ans[0];
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code

    string line;
    width = 0; 
    height = 0;
    while (getline(cin, line)){
        if (line != ""){
            height += 1;
            width = line.length();
            bmap.PB(vector <bool>(width, 0));
            for (int i = 0; i < width; i++){
                bmap[height - 1][i] = (line[i] == '#');
            }
        }else{
            ans += true_mirror_location();
            width = 0; 
            height = 0;
        }
    }
    ans += true_mirror_location();
    cout << ans;
    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}