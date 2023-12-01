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
string line;
int val = 0;

int main(){
    if (open_file){
        fileio("file");
    }
    //main code
    while (cin >> line){
        int df = 0, dl = 0;
        for (int i = 0; i < line.length(); i++){
            if (isdigit(line[i])){
                df = line[i] - '0';
                dl = df;
                break;
            }
        }
        for (int i = line.length() - 1; i >= 0; i--){
            if (isdigit(line[i])){
                dl = line[i] - '0';
                break;
            }
        }
        val += df * 10 + dl;
    }
    cout << val;
}