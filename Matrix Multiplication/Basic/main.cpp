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
#define FILEOP(x) freopen(x".inp", "r", stdin); freopen(x".out", "w", stdout);

//=====================================
//Typedef
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;

//=====================================
//Matrix Class
#define SIZE 10

template <class _T> class Matrix
{
public:

    _T a[SIZE][SIZE];
    int m, n;

    _T* operator[] (int i)
    {
        return a[i];
    }
    const _T*operator[] (int i) const
    {
        return a[i];
    }

    void clear(int M, int N){ m=M,n=N; int i, j; for (i=1; i<=m; i++) for (j=1; j<=n; j++) a[i][j]=0; }

    void operator = (const Matrix &A);

    Matrix(int M, int N)
    {
        clear(M, N);
    }

};

template <class _T> Matrix<_T>
basedMatrix(int n)
{
    Matrix<_T> R(n, n);
    FOR(i, 1, n) R[i][i] = 1;
    return R;
}

template <class _T> Matrix<_T>
operator * (const Matrix<_T> &A, const Matrix<_T> &B)
{
    Matrix<_T> C(A.m, B.n);
    FOR(i, 1, A.m)
    {
        FOR(j, 1, B.n)
        {
            FOR(k, 1, A.n)
            {
                C[i][j] +=  A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

template <class _T> Matrix<_T>
operator ^ (const Matrix<_T> &A, ll k)
{
    if(k==0) return basedMatrix<_T> (A.n);
    if(k==1) return A;
    Matrix<_T> p = A^(k/2);
    p = p*p;
    if(k&1) return p*A;
    else return p;
}

template <class _T> void Matrix<_T> ::
operator = (const Matrix<_T> &A)
{
    FOR(i, 1, A.m)
    {
        FOR(j, 1, A.n)
        {
            a[i][j] = A[i][j];
        }
    }
    m = A.m, n = A.n;
}




//=====================================
//Functions and procedures
//Main Procedure
int main()
{
    ll n;

    cin >> n;
    FOR(i, 1, n)
    {
        ll kk = i - 1;
        Matrix<ll> A(2, 2);
        A[1][1] = 1;
        A[1][2] = 1;
        A[2][1] = 1;
        A[2][2] = 0;
        A = A^kk;
        cout << (A[1][1])*1LL << endl;
    }

    return 0;
}
