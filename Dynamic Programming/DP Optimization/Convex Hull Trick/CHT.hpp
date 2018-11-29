/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
/* Briefing - Convex Hull Optimization

        * Original Recurrence:
            dp[i] = min( dp[j] + b[j]*a[i] )  for j < i
        * Condition:
            b[j] >= b[j+1]
            a[i] <= a[i+1]
        * Usage:
            ConvexHullDS hull;
            FOR(i,1,n)
            {
                dp[i] = hull.get(a[i]);
                hull.add(b[i], dp[i]);
            }
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
/* Overview - Implementation for Convex Hull Trick

        *Source: https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/DP/convex_hull.h
        *Author: RR - Thanh Trung Nguyen - @ngthanhtrung23 (GitHub), forked by me
        *Status: tested on NKLEAVES and some Codeforces problem
        *Date: 2018/09/15
*/
//=====================================
//CHT Class
struct ConvexHullDS
{
    typedef double ld;
    typedef long long ll;
    typedef vector<int> vi;
    typedef vector<ld> vld;
    typedef vector<ll> vll;
    typedef vector<vld> vvld;
    typedef vector<vll> vvll;


    vi head, tail;
    vvll a, b;
    vvld x;


    ll query(int id, ll x_query)
    {
        int& he = head[id];
        int& ta = tail[id];

        if(he > ta) return 0LL;

        while(he < ta && x[id][he+1] <= x_query) he++;
        x[id][he] = x_query;


        //cerr << "Returned: " << 1LL * a[id][he] * x_query + b[id][he] << el;

        return 1LL * a[id][he] * x_query + b[id][he];
    }
    void update(int id, ll new_a, ll new_b)
    {
        int& he = head[id];
        int& ta = tail[id];


        ld new_x = -1e18;
        while(he <= ta)
        {
            if( new_a == a[id][ta] ) return;

            new_x = 1.0 * (b[id][ta] - new_b) / (new_a - a[id][ta]);
            if(he == ta || new_x >= x[id][ta]) break;

            ta--;
        }

        a[id][++ta] = new_a;
        b[id][ ta ] = new_b;
        x[id][ ta ] = new_x;

        //cerr << "Added: " << new_a << sp << new_b << sp << new_x << el;
    }


    ConvexHullDS()
    {
        head = vi(16, 1);
        tail = vi(16, 0);
        a = b = vvll(16, vll(131073, 0LL));
        x = vvld(16, vld(131073, 0.00000));
    }
};


//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
