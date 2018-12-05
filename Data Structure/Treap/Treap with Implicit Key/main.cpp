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
    This is an implementation for Treap with implicit key
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

// #define DEBUG
// #define OPTIONAL_FEATURE

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
//Overview - Treap with implicit key
/*
    * Author : - Noam, from CP Community - Original implementation.
               - bu1th4nh - Fork and implement
    * Status : Tested
*/
//=====================================
mt19937_64 PRNG(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> die(0, 100000007);
template<class T> class Treap
{
private:

    //Node implementation
    struct Node
    {
        Node *l, *r;
        T val, tagret;
        int sz, priority;

        Node(T __val = T())
        {
            sz = 1;
            l = r = 0;
            val = tagret = __val;
            priority = die(PRNG);
        }
        ~Node()
        {
            delete l;
            delete r;
        }

        void update()
        {
            sz = 1;
            tagret = val;
            if(l != NULL)
            {
                sz += l->sz;
                tagret = max(tagret, l->tagret);
            }
            if(r != NULL)
            {
                sz += r->sz;
                tagret = max(tagret, r->tagret);
            }
        }
    };
    typedef Node* pnode; pnode root; //Root initialization
    int get_sz(pnode t) {return t ? t->sz : 0;}

    //Split and merge
    void split(pnode t, pnode &l, pnode &r, int pos, int add = 0)
    {
        if(!t) return void(l = r = NULL);
        int cur_pos = add + get_sz(t->l);
        if(cur_pos <= pos)
        {
            split(t->r, t->r, r, pos, cur_pos+1),
            l = t;
        }
        else
        {
            split(t->l, l, t->l, pos, add),
            r = t;
        }
        t->update();
    }
    pnode merge(pnode l, pnode r)
    {
        if((!l) || (!r)) return l != NULL ? l : r;
        else if(l->priority > r->priority)
        {
            l->r = merge(l->r, r);
            l->update();
            return l;
        }
        else
        {
            r->l = merge(l, r->l);
            r->update();
            return r;
        }
    }
    void dfs(pnode n)
    {
        if(!n) return;
        if(n->l) dfs(n->l);
        cerr << n->val << sp << n->tagret << el;
        if(n->r) dfs(n->r);
    }

public:
    //Inorder traversal
    void show()
    {
        cerr << "-----------------\n";
        dfs(root);
        cerr << "-----------------\n";
    }

    //Insertion and deletion
    void insert(T x, int i)
    {
        pnode l, r;
        split(root, l, r, i-2);
        root = merge(merge(l, new Node(x)), r);
    }
    void erase(int pos)
    {
        pnode L1, R1, L2, R2;
        split(root, L1, R1, pos-2);
        split(R1, L2, R2, 0);
        root = merge(L1, R2);
    }
    T query(int ql, int qr)
    {
        if(ql > qr) return T();
        pnode L1, R1, L2, R2;
        split(root, L1, R1, ql - 2);
        split(R1, L2, R2, qr - ql);

        T ret = L2->tagret;
        root = merge(L1, merge(L2, R2));
        root->update();
        return ret;
    }

    //Constructor and destructor
    Treap()
    {
        root = 0;
    }
    ~Treap() {delete root;}

};


//=====================================
//Functions and procedures
//Driver Program
int main()
{
    char t;
    int nQuery, x, y;

    Treap<int> ict;

    FOR(i, 1, 100000) ict.insert(die(PRNG), 1);
    cerr << "Ok"; return 0;

    cin >> (nQuery);
    while(nQuery--)
    {
        scanf("\n%c", &t);
        if(t == 'I' || t == 'S' || t == 'Q')
        {
            cin >> (x);
            cin >> (y);
        }
        else if(t == 'D')
        {
            cin >> (x);
        }

        if(t == 'I') ict.insert(x, y);
        else if(t == 'Q') printf("%d\n", ict.query(x, y));
        else if(t == 'D') ict.erase(x);
        else if(t == 'X') ict.show();

    }
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
