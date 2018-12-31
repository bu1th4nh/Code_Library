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
    This is an implementation for Indian Multiplication Trick 
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
#include <chrono>
#endif // __cplusplus

using namespace std;

//#define DEBUG
//#define OPTIONAL_FEATURE

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
//Typedefs
typedef long long ll;


//=====================================
//Overview - Indian Multiplication Trick implementation - Calculate a + b / a * b
/*  
    * Author : bu1th4nh.
    * Status : tested on many problems.
*/
//=====================================
//Indian Multiplication Trick without modulo
template<class T, class R> T IndianPow(T a, R b)
{
    /** \brief Calculate a ^ b in O(logN) */

    T ret = T(1);
    FORl(i, 0, log2(b)+3)
    {
        if((b >> i) & 1) ret = ret * T(a);
        a = T(a) * T(a);
    }
    return ret;
}
template<class T, class R> T IndianMult(T a, R b)
{
    /** \brief Calculate a * b in O(logN) */

    T ret = T();
    FORl(i, 0, log2(b)+3)
    {
        if((b >> i) & 1) ret += a;
        a = a + a;
    }
    return ret;
}


//=====================================
//Indian Multiplication Trick with modulo
template<class T, class R> T IndianPow(T a, R b, T mod)
{
    /** \brief Calculate a ^ b in O(logN) */

    T ret = T(1);
    FORl(i, 0, log2(b)+3)
    {
        if((b >> i) & 1) ret = (ret * a) % mod;
        a = (a * a) % mod;
    }
    return ret % mod;
}
template<class T, class R> T IndianMult(T a, R b, T mod)
{
    /** \brief Calculate a * b in O(logN) */

    T ret = T();
    FORl(i, 0, log2(b)+3)
    {
        if((b >> i) & 1) ret = (ret + a) % mod;
        a = (a + a) % mod;
    }
    return ret % mod;
}

//=====================================
//Driver Program
int main()
{
    ll a, b, mod;
    cerr << "Please enter a, b = ";
    cin >> a >> b;

    fprintf(stdout, "%I64d * %I64d = %I64d\n", a, b, IndianMult(a, b));
    fprintf(stdout, "%I64d ^ %I64d = %I64d\n", a, b, IndianPow(a, b));

    cerr << el;
    cerr << "Please enter modulo = ";
    cin >> mod;

    fprintf(stdout, "(%I64d * %I64d) mod %I64d = %I64d\n", a, b, mod, IndianMult(a, b, mod));
    fprintf(stdout, "(%I64d ^ %I64d) mod %I64d = %I64d\n", a, b, mod, IndianPow(a, b, mod));

    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
