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
    This is an implementation for 2D Geometry Library
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
#define OPTIONAL_FEATURE

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
#define what_is(x) cerr << #x << " is " << x << endl;
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
//Overview - 2D Geometry Namespace
/*
    * Author : bu1th4nh.
    * Status : tested on problem MILITARY-SPOJ.
    * Source : Thầy Lê Minh Hoàng - (Convex Hull), GeeksForGeeks - (doIntersect) and more.
*/
//=====================================
//Main Namespace
namespace Geometry
{
    typedef long long ll;
    typedef complex<ll> pt;
    typedef vector<pt> vpt;

    #define x real()
    #define y imag()

//==========================================================//
/*                     Helper Functions                     */
//==========================================================//

    template<class T> bool inRange(T __L, T __R, T __X)
    {
        return __L <= __X && __X <= __R;
    }
    template<class T> T __abs(T __X)
    {
        return (__X < 0) ? -__X : __X;
    }
    template<class T> T __sqr(T __X)
    {
        return __X * __X;
    }

//==========================================================//
/*                 Operators and simple utils               */
//==========================================================//

    ll operator| (const pt &u, const pt &v)
    {
        /**< \brief Return dot product between vector u and vector v */
        return (conj(u)*v).x;
    }
    ll operator^ (const pt &u, const pt &v)
    {
        /**< \brief Return cross product between vector u and vector v */
        return (conj(u)*v).y;
    }
    ll sqr_len(const pt &u)
    {
        /**< \brief Return squared length of vector u */
        return __sqr(u.x) + __sqr(u.y);
    }
    ll absArea(const pt &A, const pt &B, const pt &C)
    {
        /**< \brief Return the doubled value of triangle forms with three points A, B and C */
        return  __abs((B - A) ^ (C - A));
    }
    int orient(const pt &A, const pt &B, const pt &C)
    {
        /**< \brief Return the orientation of three ordered points A, B and C */
        ll tmp = (B - A) ^ (C - B);
        return tmp ? tmp < 0 ? -1 : 1 : 0;
    }
    bool onSegment(const pt &A, const pt &B, const pt &M)
    {
        /**< \brief Check if point M lies on segment AB, with M arbitrary */
        return inRange(min(A.x, B.x), max(A.x, B.x), M.x) &&
               inRange(min(A.y, B.y), max(A.y, B.y), M.y) &&
               orient(A, B, M) == 0;
    }
    ll findDoubledArea(const vpt &polygon)
    {
        /**< \brief Return the area of ordered polygon, assumed polygon[0] == polygon.back() */

        ll ret = 0LL;
        int n = polygon.size()-1;
        FORl(i, 0, n) ret += polygon[i].x * polygon[i+1].y - polygon[i+1].x * polygon[i].y;
        return ret;
    }

//==========================================================//
/*                  More complex utilities                  */
//==========================================================//

    bool doIntersect(const pt &A, const pt &B, const pt &P, const pt &Q)
    {
        /**< \brief Check if two given segments AB and PQ are intersect */
        int o1 = orient(A, B, P);
        int o2 = orient(A, B, Q);
        int o3 = orient(P, Q, A);
        int o4 = orient(P, Q, B);

        if(o1 != o2 && o3 != o4) return 1;
        if(onSegment(A, B, P)) return 1;
        if(onSegment(A, B, Q)) return 1;
        if(onSegment(P, Q, A)) return 1;
        if(onSegment(P, Q, B)) return 1;

        return 0;
    }
    void findConvexHull(vpt &init_point, vpt &hull, vpt &remain)     //0-indexed
    {
        /** \brief Find the convex hull of the set of points
         *
         * \param init_point: Vector of initial points
         * \param hull: The convex hull container, counter-clockwise ordered
         * \param remain: The container of remain points after deleted (filtered)
                  all of the points which lies on the convex hull
         */


        int m = 0;
        int n = init_point.size();
        remain.clear();
        hull.resize(n);

        //Find root and Graham Scan
        pt root = *min_element(whole(init_point), [](const pt &B, const pt &C)
        {
                return make_pair(B.y, B.x) < make_pair(C.y, C.x);
        });
        sort(whole(init_point), [&root](const pt &B, const pt &C)  {
                pt u = B - root;
                pt v = C - root;
                ll tmp =  u ^ v;
                return tmp > 0 || (!tmp && sqr_len(u) < sqr_len(v));
        });


        //Find Convex Hull
        for(pt p: init_point)
        {
            while(m >= 2 && orient(hull[m-2], hull[m-1], p) <= 0) remain.push_back(hull[m-1]),  --m;
            hull[m++] = p;
        }
        while((int)hull.size() > m) hull.pop_back();
    }
}
using namespace Geometry;


//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
