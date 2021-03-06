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
    * Centroid Tree Decomposition - to construct the centroid tree and optimize time complexity
    * Centroid: It's a special vertex, when we remove it, we will get a forest of subtrees whose
    subtree size is at most N/2
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
// #define OPTIONAL_FEATURE

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
//Auxilary Functions and Fast I/O
#ifdef OPTIONAL_FEATURE
    template<class T, class R> T max(T &x, R &y)
    {
        return x > y ? x : y;
    }
    template<class T, class R> T min(T &x, R &y)
    {
        return x < y ? x : y;
    }
    template<class T, class R> void maximize(T &x, R y)
    {
        x = x > y ? x : y;
    }
    template<class T, class R> void minimize(T &x, R y)
    {
        x = x < y ? x : y;
    }
    template<class T> int getBit(T &x, int i)
    {
        return ((x >> i) & 1) == 1;
    }
    template<class T> T __abs(T &x)
    {
        return (x = (x < 0) ? -x : x);
    }
#endif
//Fast I/O
template<class T> inline void read(T &ret)
{
    ret = T();
    char c = 0;
    bool neg = 0;

    while(isdigit(c) == 0 && c != '-') c = getchar();
    if(c == '-')
    {
        neg = 1;
        c = getchar();
    }

    for(; isdigit(c) != 0; c = getchar()) ret = ret * 10 + c - '0';
    ret = (neg) ? -ret : ret;

    #ifdef DEBUG
        cerr << "FastScan Diagnostic: " << ret << el;
    #endif
}
template<class T> void print(T x)
{
    if(x < 0)
    {
        putchar('-');
        x *= -1;
    }

    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}


//=====================================
//Overview - Centroid Tree Decomposition
/*  
    * Author : Tanuj Khattar, forked by bu1th4nh.
    * Status : tested on SPOJ_QTREE5 and Codeforces - 3442E problem.
*/
//=====================================
//Main Class/Struct
struct CentroidTreeDecomp
{
    typedef set<int> si;
    typedef vector<si> vsi;
    typedef vector<int> vi;
    typedef vector<vi> vvi;

    vsi adj;
    int nn, n;
    vi par, subtree;

    void findSubtree(int u, int p)
    {
        ++nn;
        subtree[u] = 1;

        for(int v: adj[u]) if(v != p)
        {
            findSubtree(v, u);
            subtree[u] += subtree[v];
        }
    }
    int findCentroid(int u, int p)
    {
        for(int v: adj[u]) if(v != p && subtree[v] * 2 > nn)
        {
            return findCentroid(v, u);
        }
        return u;
    }
    void decomp(int root, int p)
    {
        nn = 0;
        findSubtree(root, root);
        int centroid = findCentroid(root, root);

        if(p == -1) p = centroid;
        par[centroid] = p;

        for(int v: adj[centroid])
        {
            adj[v].erase(centroid);
            decomp(v, centroid);
        }
        adj[centroid].clear();
    }
    void initialize()
    {
        decomp(1, -1);
    }
    vi extract_tree()
    {
        return par;
    }




    ~CentroidTreeDecomp() {}

    CentroidTreeDecomp() {}
    CentroidTreeDecomp(int __n, const vsi &G)
    {
        n = __n;
        adj = G;
        par = subtree = vi(n+1, 0);
    }


    void operator= (const CentroidTreeDecomp &x)
    {
        n = x.n;
        adj = x.adj;
        par = x.par;
        subtree = x.subtree;
    }
};


//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
