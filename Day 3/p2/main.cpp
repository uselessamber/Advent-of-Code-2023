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
const int dr[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
const int dc[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
vector <string> text_map;
vector <vector <ll>> gear_map; 
vector <vector <bool>> gear_active_map;
vector <vector <bool>> temporary_board;
string text;
int max_c = 0, max_r = 0;

bool bound(int r, int c){
    return (0 <= r) && (0 <= c) && (r < max_r) && (c < max_c);
}

int answer = 0;

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    while(cin >> text){
        text_map.PB(text);
        int l = (int)text.length();
        max_c = max(max_c, l);
        max_r++;
        gear_map.PB(vector <ll>(l, 0));
        gear_active_map.PB(vector <bool>(l, false));
        temporary_board.PB(vector <bool>(l, false));
    }  
    string number = "";
    stack <pii> gear_pos;
    for (int r = 0; r < max_r; r++){
        for (int c = 0; c < max_c; c++){
            char curr = text_map[r][c];
            if (isdigit(curr)){
                number = number + curr;
                for (int i = 0; i < 8; i++){
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (bound(nr, nc)){
                        char near = text_map[nr][nc];
                        if (near == '*'){
                            gear_pos.push(pii(nr, nc));
                            temporary_board[nr][nc] = true;
                        }
                    }
                }
            }else{
                ll value = 0;
                for (char c : number){
                    value *= 10;
                    value += c - '0';
                }
                while (!gear_pos.empty()){
                    int gr = gear_pos.top().FS;
                    int gc = gear_pos.top().SC;
                    gear_pos.pop();
                    if (temporary_board[gr][gc]){
                        temporary_board[gr][gc] = false;
                    }else{
                        continue;
                    }
                    if (gear_map[gr][gc] != 0){
                        gear_active_map[gr][gc] = true;
                        gear_map[gr][gc] *= value;
                    }else{
                        gear_active_map[gr][gc] = false;
                        gear_map[gr][gc] = value;
                    }
                }
                number = "";
            }
        }
    }
    answer = 0;
    for (int r = 0; r < max_r; r++){
        for (int c = 0; c < max_c; c++){
            answer += ((gear_active_map[r][c])? gear_map[r][c] : 0);
        }
    }
    cout << answer;
}