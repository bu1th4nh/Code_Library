/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
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
#include <tuple>
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
#define FILEOP_DEBUG() {freopen(task".inp", "r", stdin); freopen(task".out", "w", stdout); freopen(task".err", "w", stderr);}


//=====================================
//Typedef
class Polygon
{
private:
    //-----------------------------------------------------------------
    struct point
    {
        int x, y;
        bool operator < (const point &other) const
        {
            return (this->x < other.x || (this->x == other.x && this->y < other.y));
        }

        point(int __x, int __y): x(__x), y(__y) {}
        point() {}

        ~point() {}
    };
    //-----------------------------------------------------------------


    typedef long long ll;
    typedef set<point> sp;
    typedef vector<point> vp;

    sp ss;
    vp a;


    //-----------------------------------------------------------------
    bool IsCW(point a, point b, point c)
    {
        return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
    }
    bool IsCCW(point a, point b, point c)
    {
        return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0;
    }
    void remove_dup()
    {
        a = vp(whole(ss));
    }
    //-----------------------------------------------------------------



public:
    vp poly;

    //---------------------------------------------------------------------------------------------
    //Make convex hull
    void make_convex_hull()
    {
        remove_dup();
        if(a.size() == 1)
        {
            poly = a;
            return;
        }
        //---------------------------------------------
        point p1 = a[0], p2 = a.back();
        vp up(1, p1);
        vp dn(1, p1);
        //---------------------------------------------
        FORl(i, 1, a.size())
        {
            if(i == a.size()-1 || IsCW(p1, a[i], p2))
            {
                while(up.size() >= 2 && !IsCW(up[up.size() - 2], up[up.size() - 1], a[i]))
                {
                    up.pop_back();
                }
                up.push_back(a[i]);
            }
            //----------------------------------------
            if(i == a.size()-1 || IsCCW(p1, a[i], p2))
            {
                while(dn.size() >= 2 && !IsCCW(dn[dn.size() - 2], dn[dn.size() - 1], a[i]))
                {
                    dn.pop_back();
                }
                dn.push_back(a[i]);
            }
        }
        //---------------------------------------------
        poly.clear();
        for(auto i: up) poly.push_back(i);
        FORlb(i, dn.size()-2, 0) poly.push_back(dn[i]);
    }


    //Point adding, polygon and area (doubled, must divide by 2) extraction
    void add_point(int __x, int __y)
    {
        ss.insert(point(__x, __y));
    }
    vp extract(bool ccw = false)
    {
        vp ret = poly;
        if(ccw) reverse(whole(ret));
        return ret;
    }
    ll double_area()
    {
        ll ret = 0LL;
        vp com = poly;
        com.push_back(poly[0]);
        FORl(i, 1, com.size())
        {
            ret += 1LL * (com[i].x - com[i-1].x) * (com[i].y - com[i-1].y);
        }
        return (ret < 0) ? -ret : ret;
    }
    //---------------------------------------------------------------------------------------------

    point operator[] (int i) {return poly[i];}
    unsigned int size() {return poly.size();}

    ~Polygon() {}
    Polygon() {}

};



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
//Driver program #1: Kattis - Convex Hull - Accepted.
void KattisConvexHull()
{
    int n, u, v;
    while(scanf("%d", &n) == 1 && n)
    {
        Polygon ops;
        FOR(i, 1, n)
        {
            scanf("%d%d", &u, &v);
            ops.add_point(u, v);
        }
        ops.make_convex_hull();
        if(ops.size() == 1)
        {
            printf("1\n%d %d\n", ops[0].x, ops[0].y);
            continue;
        }
        printf("%d\n", ops.size());
        FORb(i, ops.size() - 1, 0)
        {
            printf("%d %d\n", ops[i].x, ops[i].y);
        }
    }
}

//Main Procedure
int main()
{
    KattisConvexHull();
    return 0;
}

