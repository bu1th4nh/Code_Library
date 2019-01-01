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
    This is an implementation for Segment Tree, or Interval Tree, both non-lazy and lazy version
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

//=====================================
//Overview - Non-lazy Segment Tree implementation
/*  
    * Author : bu1th4nh.
    * Status : tested on many problems.
*/
//=====================================
//Segment Tree without Lazy Propagation, PU/RQ/Min-Max-Sum Query
template<class T> struct SegmentTree
{
    #define lc id*2
    #define rc id*2+1
    typedef vector<T> vt;


    vt ST;
    int n;


    //Build
    void build(int id, int l, int r, const vt &a)
    {
        if(l > r) return;

        if(l == r) ST[id] = (a[l]);
        else
        {
            int mid = (l + r) / 2;
            build(lc, l, mid, a);
            build(lc + 1, mid+1, r, a);
            ST[id] = max(ST[lc], ST[rc]);
        }

    }
    //Update and queries
    void update(int id, int l, int r, int pos, T val)
    {
        if(pos < l || pos > r) return;
        if(l == r && l == pos)
        {
            ST[id] = val;
            return;
        }
        ST[id] = max(ST[id], val);

        int mid = (l + r) / 2;
        update(lc, l    , mid, pos, val);
        update(rc, mid+1, r  , pos, val);
        ST[id] = max(ST[lc], ST[rc]);
    }
    T query(int id, int l, int r, int ql, int qr)
    {
        if(ql > r || qr < l || l > r || ql > qr) return 0;  //or -INFINITY
        if(ql <= l && r <= qr) return ST[id];

        int mid = (l + r) / 2;

        return max(query(lc, l, mid, ql, qr), query(rc, mid+1, r, ql, qr));
    }


    //Constructors and destructor
    SegmentTree(int __n)
    {
        ST = vt(4*__n+8, T());
    }
    SegmentTree() {}
    ~SegmentTree() {}
};

//=====================================
//Overview - Lazy version of Segment Tree implementation
/*  
    * Author : bu1th4nh.
    * Status : tested on many problems.
*/
//=====================================
//Segment Tree w/ Lazy Propagation, RU/RQ/Min-Max Query
template<class T> struct LazySegmentTree
{
    #define lc id*2
    #define rc id*2+1


    struct Node
    {
        T val, lazy;
        Node(): val(T()), lazy(T()) {}
        Node(T __v): val(__v), lazy(0) {}
        Node(T __v, T __l): val(__v), lazy(__l) {}
    };


    vector<Node> ST;

    //Lazy Propagation
    void push_down(int id)
    {
        T t = ST[id].lazy;

        ST[lc].lazy += t;
        ST[lc].val += t;

        ST[rc].lazy += t;
        ST[rc].val += t;

        ST[id].lazy = 0;
    }
    //Update and queries
    void update(int id, int l, int r, int up_l, int up_r, T v)
    {
        if(up_r <  l || r <  up_l) return;
        if(up_l <= l && r <= up_r)
        {
            ST[id].val += v;
            ST[id].lazy += v;
            return;
        }

        int mid = (l + r) / 2;
        push_down(id);

        update(lc, l    , mid, up_l, up_r, v);
        update(rc, mid+1, r  , up_l, up_r, v);

        ST[id].val = max(ST[lc].val, ST[rc].val);
    }
    T query(int id, int l, int r, int ql, int qr)
    {
        if(qr <  l || r <  ql) return -INFINITY;
        if(ql <= l && r <= qr) return ST[id].val;

        int mid = (l + r) / 2;
        push_down(id);

        return max( query(lc, l, mid, ql, qr)  ,  query(rc, mid+1, r, ql, qr) );
    }


    //Constructors and destructor
    LazySegmentTree() {}
    LazySegmentTree(int __n) {ST = vector<Node>(4*__n+16);}

    ~LazySegmentTree() {ST.clear();}

};



//=====================================
//Overview - Lazy + Sum version of Segment Tree implementation
/*  
    * Author : bu1th4nh.
    * Status : tested on problem GRASSPLA on SPOJ.
*/
//=====================================
//Segment Tree w/ Lazy Propagation and Sum Query
template<class T> class LazySumSegmentTree
{
private:

    #define lc id*2
    #define rc id*2+1
    struct Node
    {
        T val, lazy;
        Node(): val(T()), lazy(T()) {}
        Node(T __v): val(__v), lazy(0) {}
        Node(T __v, T __l): val(__v), lazy(__l) {}
    };
    typedef vector<Node> vn;

    vn ST;
    void push_down(int id, T value)
    {
        ST[lc].lazy += value;
        ST[rc].lazy += value;
    }
    void increase(int id, int l, int r, T value)
    {
        ST[id].val += (r - l + 1) * value;
        if(l != r) push_down(id, value);
        ST[id].lazy = T();
    }


public:

    void update(int id, int l, int r, int ql, int qr, T value)
    {
        if(ST[id].lazy) increase(id, l, r, ST[id].lazy);
        if(r  <  l || qr < l || r < ql) return;
        if(ql <= l && r  <= qr)
        {
            increase(id, l, r, value);
            return;
        }

        int mid = (l + r) / 2;
        update(lc, l, mid, ql, qr, value);
        update(rc, mid+1, r, ql, qr, value);
        ST[id].val = ST[lc].val + ST[rc].val;
    }
    T query(int id, int l, int r, int ql, int qr)
    {
        if(r < l || qr < l || r < ql) return T();
        if(ST[id].lazy) increase(id, l, r, ST[id].lazy);
        if(ql <= l && r <= qr) return ST[id].val;

        int mid = (l + r) / 2;
        return query(lc, l, mid, ql, qr) + query(rc, mid+1, r, ql, qr);
    }


    LazySumSegmentTree() {}
    LazySumSegmentTree(int __n)
    {
        ST = vn(4*__n+100);
    }

};



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
//Driver Program #1 (Tested, AC, SPOJ_QMAX)
void QMAX()
{
    int nUpdate, nQuery, n;
    scanf("%d%d", &n, &nUpdate);

    SegmentTree<int> st(n+3);
    vi vect(n+3, 0);


	FOR(i, 1, nUpdate)
	{
	    int u, v, k;
	    scanf("%d%d%d", &u, &v, &k);
	    vect[u] += k;
	    vect[v+1] -= k;
	}
	scanf("%d", &nQuery);
	FOR(i, 1, n) vect[i] += vect[i-1];


    st.build(1, 1, n, vect);
    FOR(ifdgfhjh, 1, nQuery)
    {
        int u, v, res;
        scanf("%d%d", &u, &v);
        res = st.query(1, 1, n, u, v);
        printf("%d\n", res);
    }
}

//Driver Program #2 (Tested, AC, SPOJ_LIS)
void LIS()
{
    int a[30007], F[30007], b[30007], compressed[30007];
    int n, res;
    scanf("%d", &n);
    res = 0;


    FOR(i, 1, n)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    SegmentTree<int> st(n+1);



    sort(b+1, b+n+1);
    FOR(i, 1, n)
    {
        compressed[i] = lower_bound(b+1, b+n+1, a[i]) - b;
    }


    FOR(i, 1, n)
    {
        F[i] = st.query(1, 1, n, 1, compressed[i]-1) + 1;
        res = max(res, F[i]);
        st.update(1, 1, n, compressed[i], F[i]);
    }
    cout << res;
}

//Driver Program #2 (Tested, AC, SPOJ_QMAX2)
void QMAX2()
{
    int x, y, res, val, value, type;
    int n, m;


    scanf("%d%d", &n, &m);
    LazySegmentTree<int> st(n);

    while(m--)
    {
        scanf("%d", &type);
        if(type == 0)
        {
            scanf("%d%d%d", &x, &y, &val);
            st.update(1, 1, n, x, y, val);
        }
        else
        {
            scanf("%d%d", &x, &y);
            res = st.query(1, 1, n, x, y);
            printf("%d\n", res);
        }
    }

}


//Main Procedure
int main()
{
    QMAX2();
    return 0;
}
