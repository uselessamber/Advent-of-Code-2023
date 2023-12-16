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
const int dr[4] = {0, 1, 0, -1}; // >, v, <, ^
const int dc[4] = {1, 0, -1, 0};
const int dm1[4] = {3, 2, 1, 0};
const int dm2[4] = {1, 0, 3, 2};
vector <string> input_map;
int row_count, col_count;
vector<vector<int>> visit; // visit[r][c][d] // row column direction

void init(){
    visit.assign(row_count, vector<int>(col_count, 0));
}

bool bound(int row, int col){
    return (0 <= row) && (row < row_count) && (0 <= col) && (col < col_count);
}

void enqueue(int row, int col, int dir, queue <pair <pair<int, int>, int>> &q){
    if (bound(row, col) && ((visit[row][col] & (1 << dir)) == 0)){
        q.push(pair <pair<int, int>, int>(
            pair<int, int>(
                row, 
                col
            ), 
            dir
        ));
        visit[row][col] |= (1 << dir);
    }
}

void bfs(int row_begin, int col_begin, int direction_begin){
    queue <pair <pair<int, int>, int>> light; // r, c, d // row column direction
    visit[row_begin][col_begin] |= (1 << direction_begin);
    light.push(pair <pair<int, int>, int>(pair<int, int>(row_begin, col_begin), direction_begin));
    while (!light.empty()){
        int current_row = light.front().first.first;
        int current_col = light.front().first.second;
        int current_dir = light.front().second;
        int new_row, new_col, new_dir;
        light.pop();
        switch (input_map[current_row][current_col]){
            case '.':
                new_row = current_row + dr[current_dir];
                new_col = current_col + dc[current_dir];
                enqueue(new_row, new_col, current_dir, light);
            break;
            case '/':
                new_dir = dm1[current_dir];
                new_row = current_row + dr[new_dir];
                new_col = current_col + dc[new_dir];
                enqueue(new_row, new_col, new_dir, light);
            break;
            case '\\':
                new_dir = dm2[current_dir];
                new_row = current_row + dr[new_dir];
                new_col = current_col + dc[new_dir];
                enqueue(new_row, new_col, new_dir, light);
            break;
            case '|':
                if ((current_dir & 1)){
                    new_row = current_row + dr[current_dir];
                    new_col = current_col + dc[current_dir];
                    enqueue(new_row, new_col, current_dir, light);
                }else{
                    new_dir = (current_dir + 1) % 4;
                    new_row = current_row + dr[new_dir];
                    new_col = current_col + dc[new_dir];
                    enqueue(new_row, new_col, new_dir, light);
                    new_dir = (current_dir + 4 - 1) % 4;
                    new_row = current_row + dr[new_dir];
                    new_col = current_col + dc[new_dir];
                    enqueue(new_row, new_col, new_dir, light);                
                }
            break;
            case '-':
                if (!(current_dir & 1)){
                    new_row = current_row + dr[current_dir];
                    new_col = current_col + dc[current_dir];
                    enqueue(new_row, new_col, current_dir, light);
                }else{
                    new_dir = (current_dir + 1) % 4;
                    new_row = current_row + dr[new_dir];
                    new_col = current_col + dc[new_dir];
                    enqueue(new_row, new_col, new_dir, light);
                    new_dir = (current_dir + 4 - 1) % 4;
                    new_row = current_row + dr[new_dir];
                    new_col = current_col + dc[new_dir];
                    enqueue(new_row, new_col, new_dir, light);                 
                }
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
    string inp;
    while (cin >> inp){
        col_count = inp.length();
        row_count++;
        input_map.push_back(inp);
    }
    init();
    bfs(0, 0, 0);
    int ans = 0;
    for (int r = 0; r < row_count; r++){
        for (int c = 0; c < col_count; c++){
            if (visit[r][c]) ans++;
        }
    }
    cout << ans;
    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}