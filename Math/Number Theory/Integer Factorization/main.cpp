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
    This is an implementation for integer factorization
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


//=====================================
//Typedefs
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;


//=====================================
//Overview - integer factorization implementation
/*  
    * Author : VNOI Wiki, modified by bu1th4nh.
    * Status : tested on many problems.
*/
//=====================================
//Naive Approach - O(sqrt(N)) per query
template<class T> map<T, int> NaiveFactorization(T n)
{
    map<T, int> mp;
    for(int i = 2; i * i <= n; ++i) while(n % i == 0)
    {
        ++mp[i];
        n /= i;
    }
    if(n != 1) mp[n] = 1;
    return mp;
}


//=====================================
//O(logN) Approach, needs pre-processing
const int MAX_N = 1e6;
vi minPrime;
void Preps()
{
    minPrime = vi(MAX_N+10, 0);
    for(int i = 2; i * i <= MAX_N; ++i) if(!minPrime[i])
    {
        for(int j = i * i; j <= MAX_N; j += i)
        {
            if(!minPrime[j]) minPrime[j] = i;
        }
    }
    for(int i = 2; i <= MAX_N; ++i) if(!minPrime[i]) minPrime[i] = i;
}
template<class T> map<T, int> LogNFactorization(T n)   //call Prep() first
{
    map<T, int> mp;
    while(n != 1)
    {
        ++mp[minPrime[n]];
        n /= minPrime[n];
    }
    return mp;
}

//=====================================
//Driver Program
int main()
{
    int x;
    cerr << "Please enter x = ";
    cin >> x;

    cerr << "Naive factorization of " << x << ": \n";
    map<int, int> a = NaiveFactorization(x);
    for(ii x: a) cout << x.fi << " ^ " << x.se << el;
    cerr << el;

    Preps();
    cerr << "LogN factorization of " << x << ": \n";
    a = LogNFactorization(x);
    for(ii x: a) cout << x.fi << " ^ " << x.se << el;
    cerr << el;
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
