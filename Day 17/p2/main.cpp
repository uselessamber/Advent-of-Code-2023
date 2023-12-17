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
typedef pair<pii, pii> piiii;
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
const int dr[4] = {0, 1, 0, -1};
const int dc[4] = {1, 0, -1, 0};
vector <vi> mp;
vector <vector <vi>> visit;
int R, C;

bool bound(int r, int c){
    return (0 <= r) && (r < R) && (0 <= c) && (c < C);
}

int path(int sr, int sc, int er, int ec){
    string d[4] = {"right", "down", "left", "up"};
    priority_queue <piiii, vector<piiii>, greater<piiii>> pq;
    visit[sr][sc][0] = 0;
    pq.push(piiii(pii(0, 0), pii(sr, sc)));
    while (!pq.empty()){
        int cr = pq.top().SC.FS;
        int cc = pq.top().SC.SC;
        int cv = pq.top().FS.FS;
        int cd = pq.top().FS.SC & 0b11;
        int cs = (pq.top().FS.SC & 0b111100) >> 2;
        pq.pop();
        //cout << "Tile [" << cr << ", " << cc << "] - [" << d[cd] << " for " << cs << " steps] = " << cv << "\n";
        if (cr == er && cc == ec && (4 <= cs && cs <= 10)) return cv;
        for (int i = 0; i < 4; i++){
            if (i == (cd + 2) % 4) continue;
            int nr = cr + dr[i];
            int nc = cc + dc[i];
            if (
                bound(nr, nc) &&
                ((cs < 4 && i == cd) || (4 <= cs && cs < 10) || (cs >= 10 && i != cd))
            ){
                int tmp = 0;
                if (i == cd){
                    tmp = cd | ((cs + 1) << 2);
                }else{
                    tmp = i | (1 << 2);
                }
                if (visit[nr][nc][tmp] > cv + mp[nr][nc]){
                    visit[nr][nc][tmp] = cv + mp[nr][nc];
                    pq.push(piiii(pii(cv + mp[nr][nc], tmp), pii(nr, nc)));
                }
            }
        }
    }
    return -1;
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code

    string inp;
    while (cin >> inp){
        R += 1;
        C = inp.length();
        mp.PB(vi(C, 0));
        visit.PB(vector <vi>(C, vi(0b111111, INF)));
        for (int i = 0; i < C; i++){
            mp[R - 1][i] = inp[i] - '0';
        }
    }
    //cout << path(0, 0, 0, 5);
    cout << path(0, 0, R - 1, C - 1);
    //end code
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}