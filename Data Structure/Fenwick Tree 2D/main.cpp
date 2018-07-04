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
//Two-dimensional Fenwick Tree
struct FenwickTree2D
{
    typedef vector<int> vi;
    typedef vector<vi> vvi;

    vvi T;
    int n;

    void update(int x, int y, int val)
    {
        for(int i = x; i <= n; i += i & (-i))
        {
            for(int j = y; j <= n; j += j & (-j))
            {
                T[i][j] += val;
            }
        }
    }
    int query(int x, int y)
    {
        int ret = 0;
        for(int i = x; i > 0; i -= i & (-i))
        {
            for(int j = y; j > 0; j -= j & (-j))
            {
                ret += T[i][j];
            }
        }
        return ret;
    }

    ~FenwickTree2D() {}

    FenwickTree2D() {}
    FenwickTree2D(int __n)
    {
        n = __n;
        T = vvi(__n+1, vi(__n+1, 0));
    }
};

//=====================================
//Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vb> vvb;
typedef vector<vii> vvii;

//=====================================
//Functions and procedures
//Driver Program #1 (Tested, AC, SPOJ_NKMOBILE)
void NKMOBILE()
{
    int s, ctrl;
    scanf("%d%d", &s, &s);
    FenwickTree2D ft(s);

    while(scanf("%d", &ctrl) && ctrl != 3)
    {
        if(ctrl == 1)
        {
            int x, y, a;
            scanf("%d%d%d", &x, &y, &a);
            ft.update(++x, ++y, a);
        }
        else
        {
            int l, b, r, t, res;
            scanf("%d%d%d%d", &l, &b, &r, &t); ++l, ++b, ++r, ++t;
            res = ft.query(r, t) - ft.query(r, b-1) - ft.query(l-1, t) + ft.query(l-1, b-1);
            printf("%d\n", res);
        }
    }
}

//Driver Program #2 (Tested, AC, SPOJ_MATSUM)
void MATSUM()
{
    int x, y, u, v, res;
    char str[10];
    string cmd;
    int s, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &s);
        FenwickTree2D ft(s);

        while(scanf("%s", &str) == 1)
        {
            cmd = string(str);

            if(cmd == "END") break;
            if(cmd == "SET")
            {
                scanf("%d%d%d", &x, &y, &u);
                v = ft.query(x+1, y+1) - ft.query(x+1, y) - ft.query(x, y+1) + ft.query(x, y);
                ft.update(x+1, y+1, u - v);
            }
            else if(cmd == "SUM")
            {
                scanf("%d%d%d%d", &x, &y, &u, &v);
                res = ft.query(u+1, v+1) - ft.query(u+1, y) - ft.query(x, v+1) + ft.query(x, y);
                printf("%d\n", res);
            }
            puts("");

        }
    }

}

//Main Procedure
int main()
{
    MATSUM();
    return 0;
}


