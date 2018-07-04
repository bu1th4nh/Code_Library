// Copyright (C) 2001-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */
#include <bits/stdc++.h>
using namespace std;


#pragma message("Code by bu1th4nh")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")

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
class CutVertexAndBridge
{
private:
    typedef pair<int, int> ii;
    typedef vector<bool> vb;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<ii> vii;

    vvi adj;
    vb isCut;
    vii bridge;
    vi num, low, cut_vtx;

    int dfs_time, n;

    void dfs(int u, int p)
    {
        int nChild = 0;
        low[u] = num[u] = ++dfs_time;
        for(int v: adj[u])
        {
            if(v != p)
            {
                if(num[v] != 0) low[u] = min(low[u], num[v]);
                else
                {
                    dfs(v, u);
                    ++nChild;

                    low[u] = min(low[u], low[v]);
                    if(low[v] >= num[v]) bridge.push_back(ii(u, v));

                    if(u == p)
                    {
                        if(nChild >= 2) isCut[u] = true;
                    }
                    else
                    {
                        if(low[v] >= num[u]) isCut[u] = true;
                    }
                }
            }
        }
    }


public:
    void addEdge(int u, int v)
    {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi extract_cut_vertices()
    {
        return cut_vtx;
    }
    vii extract_bridges()
    {
        return bridge;
    }
    int extract_cut_vertices_size()
    {
        return cut_vtx.size();
    }
    int extract_bridges_size()
    {
        return bridge.size();
    }
    void start()
    {
        FOR(i, 1, n) if(!num[i]) dfs(i, i);
        FOR(i, 1, n) if(isCut[i]) cut_vtx.push_back(i);
    }



    CutVertexAndBridge(int __n)
    {
        n = __n;
        dfs_time = 0;
        isCut = vb(n+1, false);
        num = vi(n+1, 0);
        low = vi(n+1, 0);
        adj = vvi(n+1);
    }
    CutVertexAndBridge() {}

    ~CutVertexAndBridge() {}

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
//Driver Program #1: SPOJ_GRAPH_ - Accepted
void GRAPH_()
{
    int m, n, u, v;
    cin >> n >> m;
    CutVertexAndBridge a(n);

    FOR(i, 1, m)
    {
        cin >> u >> v;
        a.addEdge(u, v);
    }

    a.start();
    cout << a.extract_cut_vertices_size() << " " << a.extract_bridges_size();
}

//Main Procedure
int main()
{
    GRAPH_();
    return 0;
}
