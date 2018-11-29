/*==============================================================================================================*\
**                                  _           _ _   _     _  _         _                                      **
**                                 | |__  _   _/ | |_| |__ | || |  _ __ | |__                                   **
**                                 | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                                  **
**                                 | |_) | |_| | | |_| | | |__   _| | | | | | |                                 **
**                                 |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                                 **
\*==============================================================================================================*/
//=====================================
//Briefing
/*
    This is the implementation for finding Minimum Spanning Tree
    using Kruskal's Algorithm

    * Status: tested
    * Author: bu1th4nh
*/
//=====================================
//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
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
#define MODUL (int)(1e9+57)
#define siz(x) (int)(x.size())
#define len(x) (int)(x.length())
#define whole(x) x.begin(), x.end()
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP() {freopen(task".inp", "r", stdin); freopen(task".out", "w", stdout);}

//=====================================
//Typedef
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<iii> viii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;

int m, n, res;
vi label;
viii EList;


//=====================================
//Functions and procedures
///Disjoint Set Union Data Structure - Complexity O(m*alpha(n))
void MakeSet()
{
    label = vi(n+1, -1);
}
int FindSet(int u)                                                      ///Path Compression
{
    return (label[u] < 0) ? u : (label[u] = FindSet(label[u]));
}
void Union(int r, int s)                                              ///Union by Rank
{
    if(label[s] < label[r]) swap(r, s);
    label[r] += label[s];
    label[s] = r;
}

///Joseph Kruskal's Algorithm - Worst-Case Complexity O(m*log2(m))
void Kruskal()
{
    res = 0;
    MakeSet();
    sort(whole(EList));
    for(iii it : EList)
    {
        int u = FindSet(it.second.second);
        int v = FindSet(it.second.first);
        if(u != v)
        {
            Union(u, v);
            res += it.first;
        }
    }
    printf("%d", res);
}

///Driver program to test the algorithm
int main()
{
    int u, v, c;
    scanf("%d%d", &n, &m);
    FOR(i, 1, m)
    {
        scanf("%d%d%d", &u, &v, &c);
        EList.push_back(iii(c, ii(u, v)));
    }

    Kruskal();

    return 0;
}
