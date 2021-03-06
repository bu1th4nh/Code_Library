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
template<class T> class ConvexHullOpt
{
private:
    typedef long double ld;
    typedef deque<ld> dqld;
    typedef deque<T> dqt;

    dqt a, b;
    dqld x;

    void pop_front()
    {
        assert(!a.empty()); a.pop_front();
        assert(!b.empty()); b.pop_front();
        assert(!x.empty()); x.pop_front();
    }
    void pop_back()
    {
        assert(!a.empty()); a.pop_back();
        assert(!b.empty()); b.pop_back();
        assert(!x.empty()); x.pop_back();
    }

public:
    T query(T x_query)
    {
        if(x.empty()) return T();

        while(x.size() > 1 && x[1] <= x_query) pop_front();
        x[0] = x_query;

        return a.front() * x_query + b.front();
    }
    void update(T new_a, T new_b)
    {
        ld new_x = -1e18;
        while(!x.empty())
        {
            if(new_a == a.back()) return;

            new_x = 1.0 * (b.back() - new_b) / (new_a - a.back());
            if(x.size() == 1 || new_x >= x.back()) break;

            pop_back();
        }
        a.push_back(new_a);
        b.push_back(new_b);
        x.push_back(new_x);
    }

    ConvexHullOpt() {}
};



//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
