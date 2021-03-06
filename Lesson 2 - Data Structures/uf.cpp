#include <iostream>
#include <vector>
using namespace std;

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size)
    {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};

int main() {

    ///union find
    unionfind uf(10);
    uf.Union(1, 5);
    uf.Union(2, 5);
    if(uf.find(1)==uf.find(2))
        cout<<"1 and 2 in the same team"<<endl;
    if(uf.find(1)!=uf.find(7))
        cout<<"1 and 7 not in the same team";
    return 0;
}