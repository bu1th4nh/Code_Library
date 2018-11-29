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
    This is the implementation for finding Strongly Connected Component

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
class StrongConnectedComponent
{
private:
    typedef pair<int, int> ii;
    typedef vector<bool> vb;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<ii> vii;
    typedef stack<int> si;

    si st;
    vi num, low;
    vvi adj, SCC;
    int dfs_time, n;


    void dfs(int u)
    {
        /** \brief DFS though the graph to find SCCs
         *
         * \param
         * \param
         * \return
         *
         */


        int nChild = 0;

        st.push(u);

        low[u] = num[u] = ++dfs_time;
        for(int v: adj[u])
        {
            if(num[v] != 0) low[u] = min(low[u], num[v]);
            else
            {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
        }

        if(num[u] == low[u])
        {
            vi tmp;
            int v;
            do
            {
                v = st.top(); st.pop();
                num[u] = low[u] = 1234567890;
                tmp.push_back(v);
            }
            while(v != u);
            SCC.push_back(tmp);
        }
    }

public:
    void addEdge(int u, int v)
    {
        adj[u].pb(v);
    }
    void start()
    {
        FOR(i, 1, n) if(!num[i]) dfs(i);
    }
    int extract_scc_size()
    {
        return SCC.size();
    }
    vvi extract_scc()
    {
        return SCC;
    }


    StrongConnectedComponent(int __n)
    {
        n = __n;
        dfs_time = 0;
        num = vi(n+1, 0);
        low = vi(n+1, 0);
        adj = vvi(n+1);
    }
    StrongConnectedComponent() {}

    ~StrongConnectedComponent() {}

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
//Functions and procedures
//Driver Program #1: SPOJ - TJALG - Accepted
void TJALG()
{
    int n, m, u, v;
    cin >> n >> m;

    StrongConnectedComponent a(n);

    FOR(i, 1, m)
    {
        scanf("%d%d", &u, &v);
        a.addEdge(u, v);
    }

    a.start();

    cout << a.extract_scc_size();
}


//Main Procedure
int main()
{
    TJALG();
    return 0;
}
