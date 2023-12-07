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

int convert(char c){
    switch (c){
        case 'A':
            return 0;
        case 'K':
            return 1;
        case 'Q':
            return 2;
        case 'J':
            return 3;
        case 'T':
            return 4;
        case '9':
            return 5;
        case '8':
            return 6;
        case '7':
            return 7;
        case '6':
            return 8;
        case '5':
            return 9;
        case '4':
            return 10;
        case '3':
            return 11;
        case '2':
            return 12;
    }
    return -1;
}

struct hand{
    string hand_string;
    int count[13] = {}; // A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2
    int hand_type = 0;
    int bet = 0;
    int high_card = 0;

    hand(string str, int bet_val){
        this->hand_string = str;
        this->bet = bet_val;
        for (char c : this->hand_string){
            this->count[convert(c)]++;
        }
        this->hand_level();
        this->high_card_find();
    }

    void hand_level(){
        int res = 0;
        /*  0 = five-of-a-kind
            1 = four-of-a-kind
            2 = full-house
            3 = three-of-a-kind
            4 = two-pair
            5 = pair
            6 = high            */
        int test = 0;
        for (int i = 0; i < 13; i++){
            if (this->count[i] == 5) test = 1;            
        }
        if (test == 1){
            this->hand_type = 0;
            return;
        }
        test = 0;
        for (int i = 0; i < 13; i++){
            if (this->count[i] == 4) test = 1;
        }
        if (test == 1){
            this->hand_type = 1;
            return;
        }
        test = 0;
        for (int i = 0; i < 13; i++){
            if (this->count[i] == 3 || this->count[i] == 2) test += this->count[i];
        }
        if (test == 5){
            this->hand_type = 2;
            return;
        }
        if (test == 3){
            this->hand_type = 3;
            return;
        }
        if (test == 4){
            this->hand_type = 4;
            return;
        }
        if (test == 2){
            this->hand_type = 5;
            return;
        }
        this->hand_type = 6;
    }

    void high_card_find(){
        for (int i = 12; i >= 0; i--){
            if (this->count[i] > 0){
                this->high_card = i;
                return;
            }
        }
    }

    bool operator <(hand &other){
        if (this->hand_type < other.hand_type) return true;
        if (this->hand_type > other.hand_type) return false;
        for (int i = 0; i < 5; i++){
            int this_hand = convert(this->hand_string[i]);
            int other_hand = convert(other.hand_string[i]);
            if (this_hand < other_hand) return true;
            if (this_hand > other_hand) return false;
        }
        return false;
    }

    bool operator >(hand &other){
        if (this->hand_type > other.hand_type) return true;
        if (this->hand_type < other.hand_type) return false;
        for (int i = 0; i < 5; i++){
            int this_hand = convert(this->hand_string[i]);
            int other_hand = convert(other.hand_string[i]);
            if (this_hand > other_hand) return true;
            if (this_hand < other_hand) return false;
        }
        return false;
    }

    bool operator ==(hand &other){
        for (int i = 0; i < 5; i++){
            int this_hand = convert(this->hand_string[i]);
            int other_hand = convert(other.hand_string[i]);
            if (this_hand != other_hand) return false;
        }
        return true;
    }
};

vector <hand> game;

int main(){
    auto start = chrono::high_resolution_clock::now();
    if (open_file){
        fileio("file");
    }
    //main code
    string inp;
    int bet_val;
    while (cin >> inp >> bet_val){
        game.PB(hand(inp, bet_val));
    }
    sort(game.begin(), game.end());
    ll ans = 0;
    for (int i = 0; i < len(game); i++){
        ans += (ll)game[i].bet * (ll)(len(game) - i);
    }
    cout << ans;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cerr << "Time elapsed: " << duration.count() << "s\n";
}