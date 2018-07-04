//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;


//=====================================
//Macros
#define task ""
#define inf INFINITY
#define maxvalueinp (int)(2309)
#define MODUL (int)(1e9+57)
#define len(x) (int)(x.length())
#define siz(x) (int)(x.size())
#define whole(x) x.begin(), x.end()
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP(x) freopen(x".inp", "r", stdin); freopen(x".out", "w", stdout);

//=====================================
//Typedef
typedef pair<int, int> ii;
typedef vector<ii> vii;
int trace[maxvalueinp];
vii adj[maxvalueinp];
int d[maxvalueinp];
int n, m, st;

//=====================================
//Functions and procedures
//Input
void Input()
{
    scanf("%d%d%d", &n, &m, &st);
    FOR(i, 1, m)
    {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        adj[x].push_back(ii(w, y));
        adj[y].push_back(ii(w, x));
    }
    //FOR(i, 1, n) adj[i].push_back(ii(0, 0));
}

//Dijkstra Algorithm
void Dijkstra(int start)
{
    priority_queue<ii, vii, greater<ii>> pq;
    int u, v, du, uv;

    //MEMS(d, 100000000);
    FOR(i, 1, n) d[i] = 1000000000;
    d[start] = 0;
    pq.push(ii(0, start));

    while(pq.size())
    {
        u = pq.top().second;
        du = pq.top().first;
        pq.pop();
        if(du != d[u]) continue;

        FORl(i, 0, siz(adj[u]))
        {
            v = adj[u][i].second;
            uv = adj[u][i].first;
            if(d[v] > du + uv)
            {
                trace[u] = v;
                d[v] = du + uv;
                pq.push(ii(d[v], v));
            }
        }
    }
}


//Output
void Output()
{
    FOR(i, 1, n)
    {
        printf("d(%d -> %d) = %d\n", st, i, d[i]);
    }
}


//Main Procedure
int main()
{
    Input();
    Dijkstra(st);
    Output();
    return 0;
}
