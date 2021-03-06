#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;

// KMP Init
void KMP_init(){
    int m = KMP_pat.length();
    lps.resize(m,0);
    lps[0]=-1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
void KMP_search() {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
            cout << "The pattern is found at index " << i-j << endl;
            j = lps[j];
        }
    }
}

int main() {
    KMP_pat = "ababac";
    KMP_str = "abababacababac";
    KMP_init();
    KMP_search();
    return 0;
}

