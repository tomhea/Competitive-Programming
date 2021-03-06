#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;
typedef vector<int> vi;
typedef pair<int, char*> ics;

#define MAX_TEXT 200010
#define MAX_PET  100000

class SuffixArray {
private:
    vi RA;                                         // rank array

    void countingSort(int k) {                     // O(n)
        int maxi = max(300, n);                      // up to 255 ASCII chars
        vi c(maxi, 0);                               // clear frequency table
        for (int i = 0; i < n; ++i)                  // count the frequency
            ++c[i+k < n ? RA[i+k] : 0];                // of each integer rank
        for (int i = 0, sum = 0; i < maxi; ++i) {
            int t = c[i]; c[i] = sum; sum += t;
        }
        vi tempSA(n);
        for (int i = 0; i < n; ++i)                  // sort SA
            tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        swap(SA, tempSA);                            // update SA
    }

    void constructSA() {                           // can go up to 400K chars
        SA.resize(n);
        iota(SA.begin(), SA.end(), 0);               // the initial SA
        RA.resize(n);
        for (int i = 0; i < n; ++i) RA[i] = T[i];    // initial rankings
        for (int k = 1; k < n; k <<= 1) {            // repeat log_2 n times
            // this is actually radix sort
            countingSort(k);                           // sort by 2nd item
            countingSort(0);                           // stable-sort by 1st item
            vi tempRA(n);
            int r = 0;
            tempRA[SA[0]] = r;                         // re-ranking process
            for (int i = 1; i < n; ++i)                // compare adj suffixes
                tempRA[SA[i]] = // same pair => same rank r; otherwise, increase r
                        ((RA[SA[i]] == RA[SA[i-1]]) && (RA[SA[i]+k] == RA[SA[i-1]+k])) ?
                        r : ++r;
            swap(RA, tempRA);                          // update RA
            if (RA[SA[n-1]] == n-1) break;             // nice optimization
        }
    }

    void computeLCP() {
        vi Phi(n);
        vi PLCP(n);
        PLCP.resize(n);
        Phi[SA[0]] = -1;                             // default value
        for (int i = 1; i < n; ++i)                  // compute Phi in O(n)
            Phi[SA[i]] = SA[i-1];                      // remember prev suffix
        for (int i = 0, L = 0; i < n; ++i) {         // compute PLCP in O(n)
            if (Phi[i] == -1) { PLCP[i] = 0; continue; } // special case
            while ((i+L < n) && (Phi[i]+L < n) && (T[i+L] == T[Phi[i]+L]))
                L++;                                     // L incr max n times
            PLCP[i] = L;
            L = max(L-1, 0);                           // L dec max n times
        }
        LCP.resize(n);
        for (int i = 0; i < n; ++i)                  // compute LCP in O(n)
            LCP[i] = PLCP[SA[i]];                      // restore PLCP
    }

public:
    const char* T;                                 // the input string
    const int n;                                   // the length of T
    vi SA;                                         // Suffix Array
    vi LCP;                                        // of adj sorted suffixes

    SuffixArray(const char* _T, const int _n) : T(_T), n(_n) {
        constructSA();                               // O(n log n)
        computeLCP();                                // O(n)
    }
};


bool icsCmp (ics s1, ics s2) {
    return strcmp(s1.second, s2.second) < 0;
}

int main() {
    int N,n;
    string s;
    char text[MAX_TEXT], tempPat[MAX_PET];
    while (cin >> N) {
        getline(cin, s);    // clears the line of input integer n;
        vector<string> pats; while (N--) { getline(cin,s); pats.push_back(s); }

        getline(cin,s); strcpy(text, s.c_str()); n = strlen(text);

        SuffixArray S(text, n);
        vector<ics> sa; for (int i = 0; i < n; i++) sa.emplace_back(i, text+S.SA[i]);

        for (const string& pat : pats) {
            strcpy(tempPat, pat.c_str()); ics tempICS = {0, tempPat};
            int i = lower_bound(sa.begin(), sa.end(), tempICS, icsCmp)->first;
            if (i >= n || s.substr(S.SA[i], n-S.SA[i]).rfind(pat, 0) != 0) { cout << "" << endl; continue; }

            vi places(1, S.SA[i++]); for (; i<n && S.LCP[i] >= pat.length(); i++) places.push_back(S.SA[i]);

            sort(places.begin(), places.end());
            cout << places[0]; for (int i = 1; i < places.size(); i++) cout << " " << places[i]; cout << endl;
        }
    }

    return 0;
}
