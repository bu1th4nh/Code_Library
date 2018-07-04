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


//=====================================
//Typedef
//Segment Tree without Lazy Propagation, PU/RQ/Min-Max-Sum Query
struct SegmentTree
{
    #define lc id*2
    #define rc id*2+1
    typedef vector<int> vi;


    vi ST;
    int n;


    //Build
    void build(int id, int l, int r, const vi &a)
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
    void update(int id, int l, int r, int pos, int val)
    {
        if(pos < l || pos > r) return;

        ST[id] = max(ST[id], val);

        if(l == r) return;


        int mid = (l + r) / 2;

        update(lc, l    , mid, pos, val);
        update(rc, mid+1, r  , pos, val);
    }
    int query(int id, int l, int r, int ql, int qr)
    {
        if(ql > r || qr < l || l > r || ql > qr) return 0;  //or -INFINITY
        if(ql <= l && r <= qr) return ST[id];

        int mid = (l + r) / 2;

        return max(query(lc, l, mid, ql, qr), query(rc, mid+1, r, ql, qr));
    }


    //Constructors and destructor
    SegmentTree(int __n)
    {
        ST = vi (4 * __n + 8);
    }
    SegmentTree() {}
    ~SegmentTree() {}
};


//Segment Tree w/ Lazy Propagation, RU/RQ/Min-Max-Sum Query
struct SegmentTreeWithLP
{
    #define lc id*2
    #define rc id*2+1


    struct Node
    {
        int val, lazy;
        Node(): val(0), lazy(0) {}
        Node(int __v): val(__v), lazy(0) {}
        Node(int __v, int __l): val(__v), lazy(__l) {}
    };


    vector<Node> ST;

    //Lazy Propagation
    void push_down(int id)
    {
        int t = ST[id].lazy;

        ST[lc].lazy += t;
        ST[lc].val += t;

        ST[rc].lazy += t;
        ST[rc].val += t;

        ST[id].lazy = 0;
    }
    //Update and queries
    void update(int id, int l, int r, int up_l, int up_r, int v)
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
    int query(int id, int l, int r, int ql, int qr)
    {
        if(qr <  l || r <  ql) return -INFINITY;
        if(ql <= l && r <= qr) return ST[id].val;

        int mid = (l + r) / 2;
        push_down(id);

        return max( query(lc, l, mid, ql, qr)  ,  query(rc, mid+1, r, ql, qr) );
    }


    //Constructors and destructor
    SegmentTreeWithLP() {}
    SegmentTreeWithLP(int __n) {ST = vector<Node>(4*__n+16);}

    ~SegmentTreeWithLP() {ST.clear();}

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

    SegmentTree st(n+3);
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
    SegmentTree st(n+1);



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
    SegmentTreeWithLP st(n);

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
