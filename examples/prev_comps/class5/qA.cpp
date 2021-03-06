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
typedef vector< vector<int> > vvi;


void KosarajuDFS(const vvi& g, int u, int color,vi& S, vi& colorMap) {
    colorMap[u] = color;
    for (auto& v : g[u]) if (colorMap[v] == -1)
            KosarajuDFS(g, v, color, S, colorMap);
    S.push_back(u);}

int findSCC(const vvi& g, vi& components) {
// first pass: record the `post-order' of original graph.
    vi order, seen;
    seen.assign(g.size(), -1);
    for (int i = 0; i < g.size(); ++i) if (seen[i] == -1)
            KosarajuDFS(g, i, 1, order, seen);
// second pass: explore the SCCs based on first pass result.
    vvi reverse_g(g.size(),vi()); for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u);
    int numSCC = 0; components.assign(g.size(), -1);
    vi dummy;
    for (int i = (int)g.size()-1; i >= 0; --i) if (components[order[i]] == -1)
            KosarajuDFS(reverse_g, order[i], numSCC++, dummy, components);
    return numSCC; }

bool topologicalSort(const vvi& g, vi& order) {
// compute indegree of all nodes
    vi indegree (g.size(), 0);
    for (int v=0; v<g.size(); v++) for (int u : g[v]) indegree[u]++;
// order sources first
    order = vector<int>();
    for (int v=0; v<g.size(); v++) if (indegree[v] == 0) order.push_back(v);
// go over the ordered nodes and remove outgoing edges, add new sources to the ordering
    for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u]==0) order.push_back(u);}
    return order.size()==g.size();}

int main() {
    int N;
    cin >> N;
    for (int n = 0; n < N; ++n) {
        int v,e;
        cin >> v >> e;
        vvi graph;
        for (int j = 0; j < v; ++j) {
            vi v_g;
            graph.push_back(v_g);
        }
        for (int k = 0; k < e; ++k) {
            int a,b;
            cin >> a >> b;
            graph.at(a-1).push_back(b-1);
        }

        vi scc;
        findSCC(graph,scc);

        vvi scc_graph;
        for(int i = 0; i<v;i++){
            while(scc_graph.size()<scc.at(i)+1) {
                vi s_graph;
                scc_graph.push_back(s_graph);
            }
            for(int vs: graph.at(i)){
                int vs_scc = scc.at(vs);
                if(vs_scc == scc.at(i))
                    continue;
                bool flag = false;
                for(int ve: scc_graph.at(scc.at(i))){
                    if(ve == vs_scc)
                        flag = true;
                }
                if(!flag)
                    scc_graph.at(scc.at(i)).push_back(vs_scc);
            }
        }

        vi order;
        topologicalSort(scc_graph,order);

        int size = scc_graph.size();
        bool* fallen = new bool[size];
        for(int i=0;i<size;i++)
            fallen[i] = false;
        int count = 0;

        for(int i=0;i<size;i++){
            if(!fallen[i]){
                count++;
                stack<int> stack1;
                stack1.push(i);
                while(!stack1.empty()){
                    int x = stack1.top();
                    stack1.pop();
                    fallen[x] = true;
                    for(int neight: scc_graph[x]){
                        stack1.push(neight);
                    }
                }
            }
        }

        printf("%d\n",count);
    }

}