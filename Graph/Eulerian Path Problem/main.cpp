/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
//Briefing
/*
    This is the implementation for finding Euler Path

    * Status: tested
    * Author: bu1th4nh
*/
//=====================================
//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <list>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <utility>
using namespace std;


//=====================================
//Macros
#define task ""
#define fi first
#define se second
#define pb push_back
#define maxinp (int)()
#define siz(x) (int)(x.size())
#define len(x) (int)(x.length())
#define whole(x) x.begin(), x.end()
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP() {freopen(task".inp", "r", stdin); freopen(task".out", "w", stdout);}
#define FILEOP_DEBUG() {freopen(task".inp", "r", stdin); freopen(task".out", "w", stdout); freopen(task".err", "w", stderr);}


//=====================================
//Graph
class EulerPath
{
    struct Edge
    {
        int to, id;
        Edge(int __to, int __id): to(__to), id(__id) {}
    };

    typedef vector<Edge> ve;
    typedef vector<bool> vb;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<ve> vve;


    int n, m, start, total;
    vi ideg, odeg, path;
    vve adj;
    vb used;

    void findPath()
    {
        stack<int> s;
        int cur = start;

        while(!s.empty() || odeg[cur])
        {
            if(!odeg[cur])
            {
                path.push_back(cur);
                cur = s.top(); s.pop();
                continue;
            }
            else
            {
                for(Edge x: adj[cur])
                {
                    if(!used[x.id])
                    {
                        odeg[cur]--;
                        used[x.id] = true;
                        s.push(cur);
                        cur = x.to;
                        break;
                    }
                }
            }
        }

        path.push_back(cur);
    }

public:


    void initPath()
    {
        FORl(i, 0, n)
        {
            if(odeg[i] != ideg[i]) ++total;
            if(odeg[i] - ideg[i] == 1) start = i;
        }
        findPath();
    }
    void addEdge(int u, int v, int i)
    {
        adj[u].pb(Edge(v, i));
        odeg[u]++;
        ideg[v]++;
    }
    void print()
    {
        if(path.size() == m+1 && (total == 0 || total == 2))
        {
            FORb(i, m, 0) cout << path[i] << " ";
            puts("");
        }
        else puts("Impossible");
    }
    bool empty()
    {
        return path.empty();
    }
    vi extract_path()
    {
        return path;
    }



    EulerPath(int __n, int __m)
    {
        n = __n, m = __m;
        start = total = 0;

        ideg = odeg = vi(n, 0);
        used = vb(m, false);
        adj = vve(n);
    }
};


//=====================================
//Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vb> vvb;
typedef vector<vii> vvii;

//=====================================
//Driver Program #01: Kattis - Eulerian Path
void KATTIS1()
{
    int m, n;
    while(scanf("%d%d", &n, &m) == 2 && m && n)
    {
        int u, v;
        EulerPath ep(n, m);
        FORl(i, 0, m)
        {
            scanf("%d%d", &u, &v);
            ep.addEdge(u, v, i);
        }

        ep.initPath();
        ep.print();
    }
}



//Main Procedure
int main()
{
    KATTIS1();
    return 0;
}
