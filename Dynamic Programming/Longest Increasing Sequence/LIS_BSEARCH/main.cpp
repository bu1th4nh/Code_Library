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
    This is binary search method for finding LIS

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
#define maxinp (65536)
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
//Typedef
typedef vector<int> vi;
int F[maxinp];
int n, res;
vi seq;


//=====================================
//Functions and procedures
//Input
void Input()
{
    seq.push_back(0);
    scanf("%d", &n);
    FOR(i, 1, n)
    {
        int x;
        scanf("%d", &x);
        seq.push_back(x);
    }
}


//Check
int BinarySearch(int i, int j)
{
    int l = 1;
    int r = j;
    while(l<r)
    {
        int k = (l+r+1) / 2;
        if (seq[F[k]] < seq[i])
        {
            l = k;
        }
        else r = k - 1;
    }
    return l;
}



//Process
void Process()
{
    res = 1;
    F[1] = 1;
    FOR(i, 2, n)
    {
        if(seq[i]<seq[F[1]])
        {
            F[1] = i;
        }
        else if(seq[i] > seq[F[res]])
        {
            ++res;
            F[res] = i;
        }
        else
        {
            int mid = BinarySearch(i, res);
            if(seq[i] > seq[F[mid]] && seq[i]<seq[F[mid + 1]]) F[mid+1] = i;
        }
    }
    printf("%d", res);
}



//Main Procedure
int main()
{
    Input();
    Process();
    return 0;
}
