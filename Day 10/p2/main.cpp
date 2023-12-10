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
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

vector <string> input_map;
vector <vi> int_map; // 0 : up, 1 : right, 2 : down, 3 : left 
vector <vector <bool>> visit_map;
vector <vector <bool>> final_table;
vector <vi> final_cumulative_table;
int C, R;
int sr, sc;

int bit(int i){
    return 1 << i;
}

bool bound(int r, int c){
    return 0 <= r && r < R && 0 <= c && c < C;
}

bool modded_bound(int r, int c){
    return 0 <= r && r < 3 * R && 0 <= c && c < 3 * C;  
}

void bfs(){
    visit_map[sr][sc] = true;
    int nv = 0;
    queue <pii> q;
    q.push(pii(sr, sc));
    while (!q.empty()){
        int cr = q.front().FS;
        int cc = q.front().SC;
        int cp = visit_map[cr][cc];
        q.pop();
        for (int i = 0; i < 4; i++){
            int nr = cr + dr[i];
            int nc = cc + dc[i];
            int ii = (i + 2) % 4;
            if (!bound(nr, nc)) continue;
            if (!visit_map[nr][nc] && (bit(i) & int_map[cr][cc]) && (bit(ii) & int_map[nr][nc])){
                visit_map[nr][nc] = true;
                nv |= bit(i);
                q.push(pii(nr, nc));
            }
        }
        if (cr == sr && cc == sc) int_map[cr][cc] = nv;
    }
}

void modded_bfs(int ir, int ic){
    if (final_table[ir][ic]) return;
    final_table[ir][ic] = true;
    queue <pii> q;
    q.push(pii(ir, ic));
    while (!q.empty()){
        int cr = q.front().FS;
        int cc = q.front().SC;
        q.pop();
        for (int i = 0; i < 4; i++){
            int nr = cr + dr[i];
            int nc = cc + dc[i];
            if (modded_bound(nr, nc) && !final_table[nr][nc]){
                final_table[nr][nc] = true;
                q.push(pii(nr, nc));
            }
        }
    }
}

bool is_inside(int pr, int pc){
    pr = pr * 3 + 1;
    pc = pc * 3 + 1;
    return (
        final_cumulative_table[pr + 2][pc + 2] -
        final_cumulative_table[pr + 2][pc - 1] -
        final_cumulative_table[pr - 1][pc + 2] +
        final_cumulative_table[pr - 1][pc - 1]
    ) == 0;
}

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    string txt;
    R = C = 0;
    while (cin >> txt){
        R += 1;
        C = max(C, (int)txt.length());
        input_map.PB(txt);
        int_map.PB(vi((int)txt.length(), 0));
        visit_map.PB(vector <bool>((int)txt.length(), false));
    } // arr[h][w]
    //cout << R << " " << C << "\n";
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            switch (input_map[r][c]){
                case 'S':
                    sr = r; sc = c;
                    int_map[r][c] = 0b1111;
                break;
                case '|':
                    int_map[r][c] = 0b0101;
                break;
                case '-':
                    int_map[r][c] = 0b1010;
                break;
                case 'L':
                    int_map[r][c] = 0b0011;
                break;
                case 'J':
                    int_map[r][c] = 0b1001;
                break;
                case '7':
                    int_map[r][c] = 0b1100;
                break;
                case 'F':
                    int_map[r][c] = 0b0110;
                break;
                case '.':
                    int_map[r][c] = 0b0000;
                break;
            }
        }
    }
    //cout << sr << " " << sc << "\n";
    bfs();
    // Final Translation
    // 0 : up, 1 : right, 2 : down, 3 : left
    final_table.assign(R * 3, vector <bool>(3 * C, 0));
    final_cumulative_table.assign(R * 3 + 1, vector <int>(C * 3 + 1, 0));
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            if (visit_map[r][c]){
                final_table[r * 3 + 1][c * 3 + 1] = true;
                for (int i = 0; i < 4; i++){
                    if (int_map[r][c] & bit(i)){
                        final_table[r * 3 + 1 + dr[i]][c * 3 + 1 + dc[i]] = true;
                    }
                }
            }
        }
    }
    for (int r = 0; r < 3 * R; r++){
        modded_bfs(r, 0);
        modded_bfs(r, 3 * C - 1);
    }
    for (int c = 0; c < 3 * C; c++){
        modded_bfs(0, c);
        modded_bfs(3 * R - 1, c);
    }
    for (int r = 0; r < 3 * R; r++){
        for (int c = 0; c < 3 * C; c++){
            final_cumulative_table[r + 1][c + 1] = (
                final_cumulative_table[r][c + 1] + 
                final_cumulative_table[r + 1][c] - 
                final_cumulative_table[r][c] + 
                ((final_table[r][c])? 1 : 0)
            );
        }
    }
    int ans = 0;
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            ans += is_inside(r, c);
        }
    }
    cout << ans;
}