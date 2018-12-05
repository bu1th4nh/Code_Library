/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
//Solution Briefing - Foreword
/*
    This is an implementation for Treap with explicit key
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
//Overview - Treap with explicit key
/*
    * Author : - Noam, from CP Community - Original implementation.
               - bu1th4nh - Fork and implement
    * Status : Test Pending
*/
//=====================================
uniform_int_distribution<> die(0, 100000007);
mt19937_64 PRNG(chrono::steady_clock::now().time_since_epoch().count());
template<class T, class R = size_t> class Treap
{
    /*
        T: Class/Type for key/value
        R: Class/Type for size, priority
    */

private:
    struct Node
    {
        R sz, priority;
        Node *l, *r;
        T val;


        Node(T __val = T())
        {
            sz = 1;
            l = r = 0;
            val = __val;
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
            if(l) sz += l->sz;
            if(r) sz += r->sz;
        }
    };
    typedef Node* pnode; pnode root;

    //Core function: Split and merge
    void split(pnode t, pnode &l, pnode &r, T key)
    {
        if(!t) return void(l = r = 0);
        else if(key < t->val)
        {
            split(t->l, l, t->l, key);
            r = t;
        }
        else
        {
            split(t->r, t->r, r, key);
            l = t;
        }
        t->update();
    }
    pnode merge(pnode l, pnode r)
    {
        if(!l || !r) return l ? l : r;
        if(l->priority > r->priority)
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

    //DFS, Inorder traversal
    void dfs(pnode n)
    {
        if(!n) return;
        if(n->l) dfs(n->l);
        cerr << n->val << el;
        if(n->r) dfs(n->r);
    }


public:

    //Inorder traversal
    void show()
    {
        cerr << "======================\n";
        dfs(root);
        cerr << "======================\n";
    }

    //Find, insert and delete
    bool find(pnode t, T val)
    {
        if(!t) return 0;
        if(t->val == val) return 1;
        return (t->val < val) ? find(t->r, val) : find(t->l, val);
    }
    void insert(T x)
    {
        if(find(root, x)) return;
        pnode l, r;
        split(root, l, r, x);
        root = merge(merge(l, new Node(x)), r);
    }
    void erase(T x)
    {
        if(!find(root, x)) return;
        pnode l, r, t;

        split(root, l, t, x);
        split(t, t, r, x+1);

        delete t;
        root = merge(l, r);
    }

    //Size and indexing utilities
    R size()
    {
        return root ? root->sz : 0;
    }
    T index(pnode t, R i)
    {
        R lsz = t->l ? t->l->sz : 0;
        if(i == lsz) return t->val;

        return (i < lsz) ? index(t->l, i) : index(t->r, i - lsz - 1);
    }
    R indexOf(pnode t, T x)
    {
        R lsz = t->l ? t->l->sz : 0;
        if(t->val == x) return lsz;

        return (t->val < x) ? lsz + 1 + indexOf(t->r, x) : indexOf(t->l, x);
    }

    //Constructor and destructor
    Treap()
    {
        root = 0;
//        PRNG = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
//        die = uniform_int_distribution<R> (1000000007, 0);
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


//    FOR(i, 1, 100000) ict.insert(die(PRNG));
//    cerr << "Ok"; return 0;

    cin >> (nQuery);
    while(nQuery--)
    {
        scanf("\n%c", &t);
        if(t == 'I' || t == 'D' || t == 'Q')
        {
            cin >> (x);
        }

        if(t == 'I') ict.insert(x);
        else if(t == 'D') ict.erase(x);
        else if(t == 'X') ict.show();

    }

    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
