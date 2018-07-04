//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
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
#define MODUL (int)(1e9+57)
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
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vb> vvb;
typedef vector<vii> vvii;
typedef long long ll;
int n, m, TCase;
vb avail;
vvi adj;
vi res;


//=====================================
//Functions and procedures
//Initialization and preparation
void FileInit()
{
    FILEOP()
}
void FileClose()
{
    fclose(stdin);
    fclose(stdout);
}
void IOSTROpt()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

//Enter
void Enter()
{
    int u, v;
    scanf("%d%d", &n, &m);

    TCase = 0;
    res = vi(n);
    avail = vb(n+1, true);
    adj = vvi(n+1, vi(n+1, 0));

    FOR(i, 1, m)
    {
        scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }
}

///Path Printing
void PrintPath()
{
    printf("Hamilton Cycle %d\: ", ++TCase);
    for(int i: res) printf("%d ", i);
    printf("1");
    puts("");
}


///Finding Hamiltonian Cycle
void Hamilton(int i)
{
    FOR(j, 1, n)
    {
        if(avail[j] && adj[res[i-1]][j])
        {
            res[i] = j;
            if(i < n-1)
            {
                avail[j] = false;
                Hamilton(i + 1);
                avail[j] = true;
            }
            else
            {
                if(adj[j][res[0]]) PrintPath();
            }
        }
    }
}

//Process
void Solve()
{
    avail[1] = false, res[0] = 1;
    Hamilton(1);
    if(TCase == 0) puts("There's no Hamilton Cycle :( ");
}

//Main Procedure
int main()
{
    Enter();
    Solve();
    return 0;
}
