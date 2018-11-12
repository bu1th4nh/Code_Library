/*==============================================================================================================*\
**                                  _           _ _   _     _  _         _                                      **
**                                 | |__  _   _/ | |_| |__ | || |  _ __ | |__                                   **
**                                 | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                                  **
**                                 | |_) | |_| | | |_| | | |__   _| | | | | | |                                 **
**                                 |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                                 **
\*==============================================================================================================*/
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
//Initialization and preparation
void FileInit()
{
    FILEOP()
}
void FileClose()
{
    fclose(stdin);
    fclose(stdout);
}

//Fenwick Tree - Point Update/Point Query/Summation Query
template<class T> struct SumFenwickTree
{
    typedef vector<T> vt;

    int n;
    vt Tree;


    void update(int pos, T value)
    {
        while(pos <= n)
        {
            Tree[pos] += value;
            pos += pos & (-pos);
        }
    }
    T query(int pos)
    {
        T ret = T();
        while(pos > 0)
        {
            ret += Tree[pos];
            pos -= pos & (-pos);
        }
        return ret;
    }

    ~SumFenwickTree() {Tree.clear();}

    SumFenwickTree() {}
    SumFenwickTree(int __n) {n = __n; Tree = vt(__n+4, T());}
    SumFenwickTree(int __n, T DefaultValue) {n = __n; Tree = vt(__n+4, DefaultValue);}
};

//Main Procedure
int main()
{
    int a[65536];
    int n, res = 0;

    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d", &a[i]);

    SumFenwickTree<int> ft(65536, 0);
    FORb(i, n, 1)
    {
        res += ft.query(a[i] - 1);
        ft.update(a[i], 1);
    }
    printf("%d\n", res);
    return 0;
}
