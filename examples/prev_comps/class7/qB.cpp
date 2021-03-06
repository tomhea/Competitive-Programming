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
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;


int main() {
    while(true){
        int n;
        cin >> n;
        if(n == 0){
            break;
        }
        string key = "";
        while(key == "")
            getline(cin,key);


        bool letters[26];
        for (int i = 0; i < 26; ++i) {
            letters[i] = false;
        }
        letters['J'-'A'] = true;
        pair<int,int> letterPos[26];
        char matrix[5][5];
        int index = 0;
        for (int l = 0; l < key.size(); ++l) {
            char c = (char)toupper(key.at(l));
            if(c == ' ')
                continue;
            if(c == 'J')
                c = 'I';
            if(!letters[c-'A']){
                matrix[index/5][index%5] = c;
                letterPos[c-'A'] = pair<int,int>(index/5,index%5);
                index++;
                letters[c-'A'] = true;
            }
        }

        int letIndex = 0;
        while(index < 25){
            if(!letters[letIndex]){
                matrix[index/5][index%5] = (char)('A'+letIndex);
                letterPos[letIndex] = pair<int,int>(index/5,index%5);
                letters[letIndex] = true;
                index++;
            }
            letIndex++;
        }

        for (int k = 0; k < n; ++k) {
            string str;
            while(str == "")
                getline(cin,str);
            vector<char> s;
            int len = str.size();
            for (int j = 0; j < len; ++j) {
                char c = (char)toupper(str.at(j));
                if(c == ' ')
                    continue;
                if(c == 'J')
                    c = 'I';
                if(s.size()%2 == 1){
                    if(s.at(s.size()-1) == c)
                        s.push_back('X');
                }
                s.push_back(c);
            }
            int i = 0;
            len = s.size();
            while(i<len){
                char c1 = s.at(i);
                i++;
                if(c1 == 'J')
                    c1 = 'I';
                char c2;
                if(i == len){
                    c2 = 'X';
                } else {
                    c2 = s.at(i);
                    if(c2 == 'J')
                        c2 = 'I';
                    i++;
                }
                if(c1 == c2){
                    printf("YY");
                    continue;
                }
                pair<int,int> pos1 =  letterPos[c1-'A'];
                pair<int,int> pos2 =  letterPos[c2-'A'];
                if(pos1.first == pos2.first){
                    printf("%c%c",matrix[pos1.first][(pos1.second+1)%5],matrix[pos2.first][(pos2.second+1)%5]);
                } else if(pos1.second == pos2.second){
                    printf("%c%c",matrix[(pos1.first+1)%5][pos1.second],matrix[(pos2.first+1)%5][pos2.second]);
                } else {
                    printf("%c%c",matrix[pos1.first][pos2.second],matrix[pos2.first][pos1.second]);
                }
            }
            printf("\n");
        }
        printf("\n");



    }
    return 0;
}