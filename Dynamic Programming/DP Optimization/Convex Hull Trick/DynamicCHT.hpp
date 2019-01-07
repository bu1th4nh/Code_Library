/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
/* Briefing - Convex Hull Optimization

        * Original Recurrence: Find max y = a * x + b.
        * Usage:
            using namespace __dp__line_container;

            LineContainer lcon;
            FOR(i,1,n)
            {
                hull.add(a[i-1], b[i-1]);
                dp[i] = lcon.query(x[i]);
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
/* Overview - Implementation for Dynamic Line Container (or Dynamic CHT/CHO)

        *Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
        *Author: Simon Lindholm @ KTH-CP, KTH ACM Contest Library, forked by me
        *Status: tested on Codeforces problem 660F
        *Date: 2019/01/05
*/
//=====================================
//Dynamic CHT Namespace
namespace __dp__line_container
{
    typedef long long ll;

    const ll inf = 100000000000000000LL;
    bool isQuery = 0;

    struct Line
    {
        mutable ll a, b, p;

        bool operator< (const Line &other) const
        {
            return isQuery ? (this->p < other.p) : (this->a < other.a);
        }

        Line(ll a, ll b, ll p): a(a), b(b), p(p) {}
        Line() {}
    };
    struct LineContainer : multiset<Line, less<Line>>
    {
        ll div(ll a, ll b)
        {
            return a / b - ((a ^ b) < 0 && a % b);
        }
        bool isect(iterator x, iterator y)
        {
            if(y == end()) {
                x->p = inf;
                return 0;
            }

            x->p =  (x->a == y->a) ? ((x->b > y->b) ?  inf : -inf)
                                   : div(y->b - x->b, x->a - y->a);
            return x->p >= y->p;
        }
        void add(ll a, ll b)
        {
            auto z = emplace(a, b, 0), y = z++, x = y;

            while(isect(y, z)) z = erase(z);
            if(x != begin() && isect(--x, y)) isect(x, y = erase(y));

            while((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
        }
        ll query(ll x)
        {
            assert(!empty());

            isQuery = 1;
            auto l = *lower_bound(Line(0, 0, x));
            isQuery = 0;

            return l.a * x + l.b;
        }
    };
}
using namespace __dp__line_container;


//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//