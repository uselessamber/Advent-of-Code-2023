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
const int N = 1e3 + 7;
const int INF = 1e9 + 7;
const double EPS = 1e-9;
const ll INF64 = 1e16 + 7;
int divceil(int x, int y){
    return 1 + ((x - 1) / y);
}
//stuff to declare
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int vs[N][N];

struct point{
    int x, y;
    point(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
};

int hex_to_int(string inp){
    int ans = 0;
    for (int i = 2; i < 8; i++){
        ans *= 16;
        switch (inp[i]){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ans += (inp[i] - '0');
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                ans += (inp[i] - 'a') + 10;
                break;
        }
    }
    return ans;
}

struct line{
    point a, b;
    int color;
    line(point a = point(), point b = point(), string scolor = "(#000000)"){
        this->a = a;
        this->b = b;
        this->color = hex_to_int(scolor);
    }
};
vector <line> line_list;
point curr(500, 500);

bool bound(int x, int y){
    return (0 <= x) && (x < N) && (0 <= y) && (y < N);
}

void bfs(){
    queue <pii> q;
    q.push(pii(0, 0));
    vs[0][0] = 2;
    while (!q.empty()){
        int cx = q.front().FS;
        int cy = q.front().SC;
        q.pop();
        for (int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (bound(nx, ny) && vs[nx][ny] == 0){
                q.push(pii(nx, ny));
                vs[nx][ny] = 2;
            }
        }
    }
}

int calculate_final(){
    int ans = 0;
    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            if (vs[x][y] == 0 || vs[x][y] == 1) ans++;
        }
    }
    return ans;
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    vs[500][500] = true;
    string col;
    char dir;
    int step;
    while (cin >> dir >> step >> col){
        point next = curr;
        int dir_int;
        switch (dir){
            case 'U':
                dir_int = 1;
                break;
            case 'D':
                dir_int = 3;
                break;
            case 'R':
                dir_int = 0;
                break;
            case 'L':
                dir_int = 2;
                break;
        }
        for (int i = 0; i < step; i++){
            next.x += dx[dir_int];
            next.y += dy[dir_int];
            vs[next.x][next.y] = 1;
        }
        line_list.PB(line(curr, next, col));
    }
    bfs();
    cout << calculate_final();
    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}