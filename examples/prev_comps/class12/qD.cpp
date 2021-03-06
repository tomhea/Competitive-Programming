#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>

using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;


vector<pair<pair<int,int>,pair<int,int>>> getMoves(int mat[5][5]){
    vector<pair<pair<int,int>,pair<int,int>>> moves;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= i; ++j) {
            if(j + 2 <= i){
                if(mat[i][j] != 0 && mat[i][j+1] != 0 && mat[i][j+2] == 0){
                    moves.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(i,j),pair<int,int>(i,j+2)));
                }
            }
            if(j - 2 >= 0){
                if(mat[i][j] != 0 && mat[i][j-1] != 0 && mat[i][j-2] == 0){
                    moves.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(i,j),pair<int,int>(i,j-2)));
                }
            }
            if(i - 2 >= 0 && j<=i-2){
                if(mat[i][j] != 0 && mat[i-1][j] != 0 && mat[i-2][j] == 0){
                    moves.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(i,j),pair<int,int>(i-2,j)));
                }
            }
            if(i + 2 < 5){
                if(mat[i][j] != 0 && mat[i+1][j] != 0 && mat[i+2][j] == 0){
                    moves.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(i,j),pair<int,int>(i+2,j)));
                }
            }
            if(i - 2 >= 0 && j - 2 >= 0){
                if(mat[i][j] != 0 && mat[i-1][j-1] != 0 && mat[i-2][j-2] == 0){
                    moves.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(i,j),pair<int,int>(i-2,j-2)));
                }
            }
            if(i + 2 < 5){
                if(mat[i][j] != 0 && mat[i+1][j+1] != 0 && mat[i+2][j+2] == 0){
                    moves.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(i,j),pair<int,int>(i+2,j+2)));
                }
            }
        }
    }
    return moves;
}

int applyMove(int mat[5][5], pair<pair<int,int>,pair<int,int>> move){
    pair<int,int> c1 = move.first;
    pair<int,int> c2 = move.second;
    int dx = (c2.first - c1.first)/2;
    int dy = (c2.second - c1.second)/2;
    int rew = mat[c1.first][c1.second]*mat[c1.first+dx][c1.second+dy];
    mat[c2.first][c2.second] = mat[c1.first][c1.second];
    mat[c1.first][c1.second] = 0;
    mat[c1.first+dx][c1.second+dy] = 0;
    return rew;
}

void reverseMove(int mat[5][5], pair<pair<int,int>,pair<int,int>> move, int reward){
    pair<int,int> c1 = move.first;
    pair<int,int> c2 = move.second;
    int dx = (c2.first - c1.first)/2;
    int dy = (c2.second - c1.second)/2;
    int cell_mid = reward/mat[c2.first][c2.second];
    mat[c1.first][c1.second] = mat[c2.first][c2.second];
    mat[c2.first][c2.second] = 0;
    mat[c1.first+dx][c1.second+dy] = cell_mid;
}

int solve(int mat[5][5], bool flag) {
    vector<pair<pair<int, int>, pair<int, int>>> moves = getMoves(mat);
    if (moves.size() == 0)
        return 0;
    if (flag) {
        int best = -100000;
        for (int i = 0; i < moves.size(); ++i) {
            int reward = applyMove(mat, moves[i]);
            int diff = solve(mat, !flag) + reward;
            best = max(diff, best);
            reverseMove(mat, moves[i], reward);
        }
        return best;
    } else {
        int best = 100000;
        for (int i = 0; i < moves.size(); ++i) {
            int reward = applyMove(mat, moves[i]);
            int diff = solve(mat, !flag) - reward;
            best = min(diff, best);
            reverseMove(mat, moves[i], reward);
        }
        return best;
    }
}

int main() {
    int mat[5][5];
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> mat[i][j];
        }
    }

    int res = solve(mat,true);
    printf("%d\n",res);
    return 0;
}
