/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
/* Trie Tree implementation

        * Source: own work
        * Author: bu1th4nh
        * Status: Tested
        * Date: 2018/11/29
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
//Trie Tree
namespace Trie
{
    const int MAX_CHARACTER = 311;
    const int CHR_BEGIN     = 'A';
    const int CHR_END       = 'Z';

    struct Node
    {
        Node* parent;
        Node* child[MAX_CHARACTER];
        bool isLeaf;
    };
    Node* root;

    Node* newNode()
    {
        Node* ret = new Node;

        FORl(i, CHR_BEGIN, CHR_END) ret->child[i] = NULL;
        ret->parent = NULL;
        ret->isLeaf = 0;

        return ret;
    }
    Node* insert(string s)
    {
        Node* n = root;
        for(char c: s)
        {
            if(n->child[c] == NULL)
            {
                n->child[c] = newNode();
            }
            n = n->child[c];
        }
        n->isLeaf = 1;

        return n;
    }
    bool find(string t)
    {
        Node* n = root;
        for(char c: t)
        {
            if(n->child[c] == NULL) return 0;
            n = n->child[c];
        }
        return n->isLeaf;
    }
    void DFS(Node *p)
    {
        //
    }

    void initialize()
    {
        root = newNode();
    }
};
using namespace Trie;

//=====================================
//Driver Programs
void Driver()
{
    //Driver Problem: Given n word and m query. Each query: Find a word w.
    int n, m;
    string s;
    initialize();

    cin >> n >> m;
    FOR(i, 1, n)
    {
        cin >> s;
        insert(s);
    }
    FOR(i, 1, m)
    {
        cin >> s;
        puts(find(s) ? "true" : "false");
    }
}


//Main Procedure
int main()
{
    Driver();
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
