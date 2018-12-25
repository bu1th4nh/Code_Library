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
template<class T> inline void scan(T &ret)
{
    ret = T();
    char c = 0;
    bool neg = 0;

    while(isdigit(c) == 0 && c != '-') c = getchar();
    if(c == '-')
    {
        neg = 1;
        c = getchar();
    }

    for(; isdigit(c) != 0; c = getchar()) ret = ret * 10 + c - '0';
    ret = (neg) ? -ret : ret;

    #ifdef DEBUG
        cerr << "FastScan Diagnostic: " << ret << el;
    #endif
}
template<class T> void print(T x)
{
    if(x < 0)
    {
        putchar('-');
        x *= -1;
    }

    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
//=====================================
//Overview - Treap with implicit key
/*
    * Author : - Noam, from CP Community - Original implementation.
               - bu1th4nh - Fork and implement
    * Status : Test Pending
*/
//=====================================
mt19937_64 PRNG(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> die(0, 100000007);
template<class T, int INDEX_FROM = 0> class Treap
{
private:

    //Node implementation
    struct Node
    {
        T val;
        bool rev;
        Node *l, *r;
        int sz, priority;

        T min_value;
        T max_value;
        T gcd_value;
        T sum_value;
        T increment;

        Node(T __val = T())
        {
            sz = 1;
            rev = 0;
            l = r = 0;
            val = __val;
            min_value = __val;
            max_value = __val;
            gcd_value = __val;
            sum_value = __val;
            increment = T();
            priority = die(PRNG);
        }
        ~Node()
        {
            delete l;
            delete r;
        } 

        void push_down()
        {
            //Lazy Propagation Processing
            if(increment)
            {
                val += increment;
                sum_value += increment * sz;
                if(l) l->increment += increment;
                if(r) r->increment += increment;
                increment = T();
            }

            //Reverse Effect Processing
            if(rev)
            {
                if(l) l->rev ^= 1;
                if(r) r->rev ^= 1;
                swap(l, r);
                rev = 0;
            }
        }
        void update()
        {
            sz = 1;
            // push_down();
            min_value = max_value = gcd_value = sum_value = val;
            if(l)
            {
                // l->push_down();
                sz += l->sz;
                min_value = min(min_value, l->min_value);
                max_value = max(max_value, l->max_value);
                gcd_value = __gcd(gcd_value, l->gcd_value);
                sum_value += l->sum_value;
            }
            if(r)
            {
                // r->push_down();
                sz += r->sz;
                min_value = min(min_value, r->min_value);
                max_value = max(max_value, r->max_value);
                gcd_value = __gcd(gcd_value, r->gcd_value);
                sum_value += r->sum_value;
            }
        }
    };
    typedef Node* pnode; pnode root; //Root initialization
    int get_sz(pnode t) {return t ? t->sz : 0;}

    //Split and merge
    void split(pnode t, pnode &l, pnode &r, int pos)
    {
        if(!t) return void(l = r = NULL);
        t->push_down();
        if(get_sz(t->l) < pos)
        {
            split(t->r, t->r, r, pos - get_sz(t->l) - 1),
            l = t;
        }
        else
        {
            split(t->l, l, t->l, pos),
            r = t;
        }
        t->update();
    }
    pnode merge(pnode l, pnode r)
    {
        if((!l) || (!r)) return l ? l : r;

        l->push_down();
        r->push_down();
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
    void dfs(pnode n)
    {
        if(!n) return;
        n->push_down(); 
        if(n->l) dfs(n->l);
        cout << n->val << sp;
        if(n->r) dfs(n->r);
    }


    //Helper Function
    T get_value(pnode t, int pos)
    {
        t->push_down();
        int lsz = get_sz(t->l);
        if(pos == lsz) return t->val;
        else return (pos < lsz) ? get_value(t->l, pos) : get_value(t->r, pos - lsz - 1);
    }
    

public:
    //Inorder traversal
    void show()
    {
        //cerr << "\n-----------------\n";
        dfs(root);
        //cerr << "\n-----------------\n";
    }
    //Insert a value to treap
    void insert(T x, int pos)
    {
        pnode l, r;
        split(root, l, r, pos);
        root = merge(merge(l, new Node(x)), r);
    }

    //Delete ``num`` element(s) from treap from position pos
    void erase(int pos, int num)
    {
        pnode L1, R1, L2, R2;
        split(root, L1, R1, pos);
        split(R1, L2, R2, num);
        root = merge(L1, R2);
        delete L2;
    }

    //get the i-th value of the array
    T operator[] (int id)
    {
        return get_value(root, id);
    }

    //Bring segment from l to r to front of the array
    void to_front(int l, int r)
    {
        pnode L1, R1, L2, R2;
        split(root, L1, R1, r+1);
        split(L1, L2, R2, l);
        root = merge(merge(R2, L2), R1);
    }
    void teleport(int old_pos, int sz, int new_pos) //root = [L1, R1[L2, R2]]
    {
        pnode L1, R1, L2, R2, L3, R3;
        split(root, L1, R1, old_pos);
        split(R1, L2, R2, sz);

        L1 = merge(L1, R2);
        split(L1, L3, R3, new_pos);
        root = merge(merge(L3, L2), R3);
    }
    
    //Cyclic shift
    void cyclic_shift(int l, int r, int k)
    {
        cerr << "CShift from " << l << " to " << r << " by " << k << el;

        int len = r - l;
        pnode T1, T2, T3, T4;
        if(k < 0) k = (len + k % len) % len;
        if(k > 0)
        {
            k %= len;
            split(root, T1, T2, l);
            split(T2, T2, T3, len - k);
            split(T3, T3, T4, k);

            cerr << "Debug: \n T1: ";
            dfs(T1);
            cerr << "\n-----\n T2: ";
            dfs(T2);
            cerr << "\n-----\n T3: ";
            dfs(T3);
            cerr << "\n-----\n T4: ";
            dfs(T4);
            cerr << "\n-----\n\n";

            root = merge(merge(merge(T1, T3), T2), T4);
        }
    }

    //Range Update/Query
    void increase(int l, int r, T val)
    {
        if(l > r) return;
        pnode L1, R1, L2, R2;
        split(root, L2, R2, r+1);
        split(L2, L1, R1, l);
        R1->increment = val;
        root = merge(merge(L1, R1), R2);
        root->update();
    }
    void extract_param(int l, int r, T &max_val, T &min_val, T &sum_val, T &gcd_val)
    {
        if(l > r) return;
        pnode L1, R1, L2, R2;
        split(root, L2, R2, r+1);
        split(L2, L1, R1, l);
        
        max_val = R1->max_value;
        min_val = R1->min_value;
        sum_val = R1->sum_value;
        gcd_val = R1->gcd_value;

        root = merge(merge(L1, R1), R2);
    }
    


    //Constructor and destructor
    Treap(const vector<T> &vect)
    {
        root = 0;
        for(T x: vect) root = merge(root, new Node(x));
    }
    Treap()
    {
        root = 0;
    }
    ~Treap() {delete root;}

};


//=====================================
//Functions and procedures
//Driver Program
void SPOJ_CARDS()
{
    int n, x;
    scan(n);
    scan(x);
    vector<int> a(n, 0);

    iota(whole(a), 1);
    Treap<int> trp(a);

    int i, m, j;
    FOR(ipx, 1, x)
    {
        scan(i);
        scan(m);
        scan(j);

        trp.teleport(i-1, m, j-1);
    }

    trp.show();
}
void SPOJ_QMAX3VN()
{
    char t;
    int n, x, y, p, d;
    Treap<int> trp;

    scan(n);
    while(n)
    {
        t = 0;
        while(t != 'A' && t != 'Q') t = getchar();
        scan(x); scan(y);

        if(t == 'A') trp.insert(x, y-1);
        else 
        {
            trp.extract_param(x, y, p, d, d, d);
            print(p);
            putchar(el);
        }
        --n;
    }

}
void SPOJ_QMAX2()
{
    long long n, c, t, x, y, z, p, d;
    scan(n);
    scan(c);
    Treap<long long> trp(vector<long long> (n+1, 0));

    while(c--)
    {
        scan(t);
        if(t == 0)
        {
            scan(x);
            scan(y);
            scan(z);

            trp.increase(x, y, z);
        }
        else
        {
            scan(x);
            scan(y);
            trp.extract_param(x, y, p, d, d, d);
            print(p);
            putchar(el);
        }
    }
}
void SPOJ_HORRIBLE()
{
    long long n, c, t, x, y, z, p, d;
    scan(t);
    while(t--)
    {
        scan(n);
        scan(c);
        Treap<long long> trp(vector<long long> (n+1, 0));

        while(c--)
        {
            scan(x);
            if(x == 0)
            {
                scan(x);
                scan(y);
                scan(z);

                trp.increase(x, y, z);
            }
            else
            {
                scan(x);
                scan(y);
                trp.extract_param(x, y, d, d, p, d);
                print(p);
                putchar(el);
            }
        }
    }
}
void GenericTester()
{
    char t;
    int nQuery, x, y, n, z;


    cout << "Enter n = ";
    cin >> n;
    cerr << "Enter a = ";


    vector<int> initial_element(n);
    for(int &x: initial_element) cin >> x;
    Treap<int> ict(initial_element);
    cout << el;
    for(int &x: initial_element) cout << x << sp;
    cout << el;


    cout << "Numbers stored in tree: " << el;
    FORl(i, 0, n) cout << ict[i] << sp; cout << el;
    cout << "Enter number of queries: ";
    cin >> nQuery;

    while(nQuery--)
    {
        string t;
        cin >> t;

        if(t == "INSERT")
        {
            cin >> x >> y;
            ict.insert(x, y);
        }
        if(t == "ERASE_1")
        {
            cin >> x;
            ict.erase(x, 1);
        }
        if(t == "ERASE_n")
        {
            cin >> x >> y;
            ict.erase(x, y);
        }
        if(t == "ITH")
        {
            cin >> x;
            printf("At pos %d: %d", x, ict[x]);
        }
        if(t == "CSHIFT")
        {
            cin >> x >> y >> z;
            ict.cyclic_shift(x, y, z);
        }
        if(t == "BTFRONT")
        {
            cin >> x >> y;
            ict.to_front(x, y);
        }
        if(t == "SHOW")
        {
            ict.show();
        }
        if(t == "INC")
        {
            cin >> x >> y >> z;
            ict.increase(x, y, z);
        }
        if(t == "PARAM")
        {
            int m, mm, s, gccd;
            cin >> x >> y;
            ict.extract_param(x, y, mm, m, s, gccd);
            printf("From %d to %d: max = %d, min = %d, sum = %d, gcd = %d\n", x, y, mm, m, s, gccd);
        }
    }

}

//Mains
int main()
{
    SPOJ_CARDS();
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
