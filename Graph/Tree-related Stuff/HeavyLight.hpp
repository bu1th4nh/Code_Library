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
    Heavy-Light Decomposition - to flatten the tree into chains and optimize time complexity
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
#include <cassert>
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

#if __cplusplus >= 201103L
#include <unordered_map>
#include <unordered_set>
#include <random>
#endif // __cplusplus

using namespace std;

// #define DEBUG 

//=====================================
//Macroes
#define sp ' '
#define el '\n'
#define task ""
#define maxinp ()
#define fi first
#define se second
#define pb push_back
#define whole(x) x.begin(),x.end()
#define whole_1(x) x.begin()+1,x.end()
#define r_whole(x) x.rbegin(),x.rend()
#define FOR(i, x, y) for(auto i=x; i<=y; ++i)
#define FORl(i, x, y) for(auto i=x; i<y; ++i)
#define FORb(i, x, y) for(auto i=x; i>=y; --i)
#define FORlb(i, x, y) for(auto i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP()                        \
{                                       \
    freopen(task".inp", "r", stdin);    \
    freopen(task".out", "w", stdout);   \
}
#define FILEOP_DEBUG()                  \
{                                       \
    freopen(task".inp", "r", stdin);    \
    freopen(task".out", "w", stdout);   \
    freopen(task".err", "w", stderr);   \
}

//Macroes - Optional
#ifdef OPTIONAL_FEATURE
    #define pc(x) putchar(x)
    #define gc() getchar()
#endif


//=====================================
//Overview - Heavy-Light Decomposition
/*  
    * Author : Al.Cash, forked by me.
    * Status : tested on SPOJ_QTREE and SPOJ_QTREEX problem.
    * This implementation applied for rooted tree which has initial weight.
*/
//=====================================
//Main Class
class HeavyLightDecomp
{
    typedef pair<int, int> ii;
    typedef vector<int> vi;
    typedef vector<ii> vii;
    typedef vector<vii> vvii;

    int n;
    vvii tree;
    vi baseArray;
    vi path_root;
    vi parent;
    vi heavy;
    vi depth;
    vi pos;

    LazySegmentTree st;

    int dfs(int u)
    {
        int sz = 1;
        int maxSubtree = 0;

        for(auto x: tree[u]) if(x.se != parent[u])
        {
            int v = x.se;

            parent[v] = u;
            depth[v]  = depth[u] + 1;

            int subtree = dfs(v);
            if(maxSubtree < subtree)
            {
                maxSubtree = subtree;
                heavy[u] = v;
            }

            sz += subtree;
        }

        return sz;
    }
    template<class BinaryOperation> void processPath(int u, int v, BinaryOperation op)
    {
        for(; path_root[u] != path_root[v]; v = parent[path_root[v]])
        {
            if(depth[path_root[u]] > depth[path_root[v]]) swap(u, v);
            op(pos[path_root[v]], pos[v]);
        }

        if(u == v) return;
        if(depth[u] > depth[v]) swap(u, v);
        op(pos[u]+1, pos[v]);
    }

public:
    void initialize()
    {
        parent[1] = -1;
        depth[1] = 0;

        dfs(1);
        for(int i = 1, cur_pos = 1; i <= n; ++i)
        {
            if(parent[i] == -1 || heavy[parent[i]] != i)
            {
                for(int j = i; j != -1; j = heavy[j])
                {
                    path_root[j] = i;
                    pos[j] = cur_pos++;
                }
            }
        }
    }
    void initBaseArray()
    {
        FOR(i, 1, n) for(auto x: tree[i])
        {
            if(x.se != parent[i])
            {
                baseArray[pos[x.se]] = x.fi;
            }
        }
        st.build(1, 1, n, baseArray);
    }
    void addEdge(int u, int v, int c)
    {
        tree[u].pb(ii(c, v));
        tree[v].pb(ii(c, u));
    }
    void set(int u, int v, int value)
    {
        if(parent[v] == u) swap(u, v);
        st.update(1, 1, n, pos[u], value);
    }
    void update_path(int u, int v)
    {
        processPath(u, v, [this](int l, int r) {
            st.change(1, 1, n, l, r);
        });
    }
    int query_path(int u, int v)
    {
        int ret = -inf;   //Some critical value
        processPath(u, v, [this, &ret](int l, int r) {
            ret = max(ret, st.query(1, 1, n, l, r));
        });
        return ret;
    }

    void debugBaseArray()
    {
        cerr << "baseArray is:         "; FOR(i, 1, n) cerr << st.query(1, 1, n, pos[i], pos[i]) << sp; cerr << el;
    }
    void debug()
    {
        cerr << "id is:                "; FOR(i, 1, n) cerr << i << sp; cerr << el;
        cerr << "pos is:               "; FOR(i, 1, n) cerr << pos[i] << sp; cerr << el;
        cerr << "heavy is:             "; FOR(i, 1, n) cerr << heavy[i] << sp; cerr << el;
        cerr << "depth is:             "; FOR(i, 1, n) cerr << depth[i] << sp; cerr << el;
        cerr << "parent is:            "; FOR(i, 1, n) cerr << parent[i] << sp; cerr << el;
        cerr << "path_root is:          "; FOR(i, 1, n) cerr << path_root[i] << sp; cerr << el;
        cerr << "Initial baseArray is: "; FOR(i, 1, n) cerr << baseArray[i] << sp; cerr << el;
        cerr << "id is:                "; FOR(i, 1, n) cerr << i << sp; cerr << el;


        // FOR(i, 1, n)
        // {
        //     cerr << i << ": ";
        //     for(auto x: tree[i]) if(parent[i] != x.se) cerr << x.se << "-" << x.fi << sp;
        //     cerr << el;
        // }
    }


    ~HeavyLightDecomp() {}

    HeavyLightDecomp() {}
    HeavyLightDecomp(int __n)
    {
        n = __n;
        tree = vvii(n+1);
        baseArray = vi(n+1, 0);

        pos = vi(n+1, 0);
        depth = vi(n+1, 0);
        parent = vi(n+1, 0);
        path_root = vi(n+1, 0);
        heavy = vi(n+1, -1);

        st = LazySegmentTree(n);
    }
};


//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
