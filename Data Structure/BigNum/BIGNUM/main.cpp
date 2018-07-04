/***********************************************************************************/
/**                                                                               **/
/**                     BIG INTEGER CLASS v1.1.10423                              **/
/**             Copyright(c) 2017 by bu1th4nh - I.T 16-19 CTB                     **/
/**                                                                               **/
/**                    E-mail: bu1th4nh.127@gmail.com                             **/
/**                                                                               **/
/**       This program is free software; you can redistribute it and/or           **/
/**        modify it under the terms of the GNU General Public License            **/
/**      as published by the Free Software Foundation; either version 2           **/
/**        of the License, or (at your option) any later version.                 **/
/**                                                                               **/
/**       This program is distributed in the hope that it will be useful,         **/
/**        but WITHOUT ANY WARRANTY; without even the implied warranty of         **/
/**         MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **/
/**                GNU General Public License for more details.                   **/
/**                                                                               **/
/**    You should have received a copy of the GNU General Public License          **/
/**      along with this program; if not, write to the Free Software              **/
/**   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. **/
/**                                                                               **/
/***********************************************************************************/

//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;


//=====================================
//Macros
#define task ""
#define maxvalueinp (int)()
#define MODUL (int)(1e9+57)
#define len(x) (int)(x.length())
#define siz(x) (int)(x.size())
#define whole(x) x.begin(), x.end()
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP(x) freopen(x".inp", "r", stdin); freopen(x".out", "w", stdout);

//=====================================
//Typedef

class BigInt
{

public:

    string val;
    bool IsNegative = false;

    BigInt(string t, bool Normalize = true)
    {

        val = t;
        if(val[0] == '-') IsNegative = true;
        if(Normalize)
        {
            if(val[0] == '-')
            {
                val.erase(0, 1);
            }
        }
    }
    BigInt(unsigned long long n)
    {
        if(n < 0)
        {
            IsNegative = true;
        }
        while(n > 0)
        {
            int t = n % 10;
            val = (char)(t + '0') + val;
            n /= 10;
        }
    }
    BigInt()
    {
        val = "";
        IsNegative = false;
    }


protected:

    BigInt Add(BigInt A, BigInt B)
    {
        string a = A.val;
        string b = B.val;
        int carry = 0;
        BigInt res;

        while(len(a)<len(b)) a = '0' + a;
        while(len(a)>len(b)) b = '0' + b;

        FORb(i, len(a)-1, 0)
        {
            int tmp = a[i] + b[i] - 96 + carry;
            carry = tmp/10;
            tmp = tmp%10;
            res.val = (char)(tmp + 48) + res.val;
        }

        if (carry > 0) res.val = '1' + res.val;
        return res;
    }

    BigInt Subtract(BigInt A, BigInt B)
    {
        string a = A.val;
        string b = B.val;

        while(len(a)<len(b)) a = '0' + a;
        while(len(a)>len(b)) b = '0' + b;

        bool neg = (a < b);
        int borrow = 0;
        BigInt res;

        if(neg) swap(a, b);

        FORb(i, len(a)-1, 0)
        {
            int tmp = a[i] - b[i] - borrow;
            if(tmp<0)
            {
                tmp+=10;
                borrow = 1;
            }
            else borrow = 0;
            res.val = (char)(tmp + 48) + res.val;
        }

        while(len(res.val)>1 && res.val[0] == '0') res.val.erase(0, 1);

        if(neg) res.val = '-' + res.val;

        res.IsNegative = neg;

        return res;
    }

    BigInt Multi(BigInt A, BigInt B)
    {
        BigInt res;
        int n = len(A.val), m = len(B.val);
        int len1 = n+m-1;
        int carry = 0;
        FORb(i, len1, 0)
        {
            int tmp = 0;
            FORb(j, n-1, 0)
            {
                if(i-j<=m && i-j>=1)
                {
                    tmp += (A.val[j]-48) * (B.val[i-j-1]-48);
                }
            }
            tmp += carry;
            carry = tmp/10;
            res.val = (char)(tmp%10 + 48) + res.val;
        }
        while(len(res.val)>1 && res.val[0] == '0') res.val.erase(0, 1);
        return res;
    }

    BigInt Divide(BigInt A, BigInt B)
    {
        BigInt a = A;
        BigInt b = B;
        BigInt res, tmp;
        BigInt kb[11];

        kb[0].val = "0";
        FOR(i, 1, 10)
        {
            kb[i] = Add(b, kb[i-1]);
        }
        FORl(i, 0, len(a.val))
        {
            int k = 1;
            tmp.val = tmp.val + a.val[i];
            while(BigInt::compare(tmp, kb[k]) != -1) ++k;
            res.val = res.val + (char)(k-1+48);
            tmp = Subtract(tmp, kb[k-1]);
        }
        while (len(res.val) > 1 && res.val[0] == '0') res.val.erase(0, 1);
        return res;
    }

    BigInt Mod(BigInt A, BigInt B)
    {
        BigInt a = A;
        BigInt b = B;
        BigInt tmp;
        BigInt kb[11];

        kb[0].val = "0";
        FOR(i, 1, 10)
        {
            kb[i] = Add(b, kb[i-1]);
        }
        FORl(i, 0, len(a.val))
        {
            int k = 1;
            tmp.val = tmp.val + a.val[i];
            while(BigInt::compare(tmp, kb[k]) != -1) ++k;
            tmp = Subtract(tmp, kb[k-1]);
        }
        return tmp;
    }


public:

    int compare(BigInt a, BigInt b)
    {
        while(len(a.val)<len(b.val)) a.val = '0' + a.val;
        while(len(a.val)>len(b.val)) b.val = '0' + b.val;
        if(a.val == b.val) return 0;
        if(a.val > b.val) return 1;
        return -1;
    }

    void Normalize(BigInt &A)
    {
        if(A.val[0] == '-')
        {
            A.IsNegative = true;
            A.val.erase(0, 1);
        }
    }

    BigInt operator+(const BigInt &other)
    {
        BigInt A = *this;
        BigInt B = other;
        BigInt res;
        Normalize(A);
        Normalize(B);
        if(A.IsNegative && B.IsNegative)
        {
            res = Add(A, B);
            res.IsNegative = true;
            res.val = '-' + res.val;
        }
        else if(A.IsNegative && !B.IsNegative)
        {
            res = Subtract(B, A);
        }
        else if(!A.IsNegative && B.IsNegative)
        {
            res = Subtract(A, B);
        }
        else
        {
            res = Add(A, B);
        }
        return res;
    }

    BigInt operator-(const BigInt &other)
    {
        BigInt A = *this;
        BigInt B = other;
        BigInt res;
        Normalize(A);
        Normalize(B);
        if(A.IsNegative && !B.IsNegative)
        {
            res = Add(A, B);
            res.IsNegative = true;
            res.val = '-' + res.val;
        }
        else if(A.IsNegative && B.IsNegative)
        {
            res = Subtract(B, A);
        }
        else if(!A.IsNegative && B.IsNegative)
        {
            res = Add(A, B);
        }
        else
        {
            res = Subtract(A, B);
        }
        return res;
    }

    BigInt operator*(const BigInt &other)
    {
        BigInt A = *this;
        BigInt B = other;
        BigInt res;
        Normalize(A);
        Normalize(B);
        if(compare(A, BigInt("0")) == 0 || compare(B, BigInt("0")) == 0) return BigInt("0");
        if(A.IsNegative != B.IsNegative)
        {
            res = Multi(A, B);
            res.val = '-' + res.val;
            res.IsNegative = true;
        }
        else
        {
            res = Multi(A, B);
        }
        return res;
    }

    BigInt operator/(const BigInt &other)
    {
        BigInt A = *this;
        BigInt B = other;
        BigInt res;
        if(compare(A, BigInt("0")) == 0 || compare(B, BigInt("0")) == 0) return BigInt("0");
        Normalize(A);
        Normalize(B);
        if(A.IsNegative != B.IsNegative)
        {
            res = Divide(A, B);
            res.val = '-' + res.val;
            res.IsNegative = true;
        }
        else
        {
            res = Divide(A, B);
        }
        return res;
    }

    BigInt operator%(const BigInt &other)
    {
        BigInt A = *this;
        BigInt B = other;
        BigInt res;
        if(compare(A, BigInt("0")) == 0 || compare(B, BigInt("0")) == 0) return BigInt("0");
        Normalize(A);
        Normalize(B);
        if(A.IsNegative != B.IsNegative)
        {
            res = Mod(A, B);
            res.val = '-' + res.val;
            res.IsNegative = true;
        }
        else
        {
            res = Mod(A, B);
        }
        return res;
    }

    BigInt& operator+= (const BigInt& B)
    {
        *this = *this + B;
        return *this;
    }

    BigInt& operator-= (const BigInt& B)
    {
        *this = *this - B;
        return *this;
    }

    BigInt& operator*= (const BigInt& B)
    {
        *this = *this * B;
        return *this;
    }

    BigInt& operator/= (const BigInt& B)
    {
        *this = *this / B;
        return *this;
    }

    BigInt& operator%= (const BigInt& B)
    {
        *this = *this % B;
        return *this;
    }

    BigInt& operator++()
    {
        BigInt res = *this;
        res = res + BigInt("1");
        *this = res;
        return *this;
    }

    BigInt& operator++(int t)
    {
        BigInt res = *this + BigInt("1");
        return res;
    }

    BigInt& operator--()
    {
        BigInt res = *this;
        res = res - BigInt("1");
        *this = res;
        return *this;
    }

    BigInt& operator--(int t)
    {
        BigInt res = *this - BigInt("1");
        return res;
    }


};



int main()
{
    BigInt A, B, C, D, E, F, G, M, N, P, Q, R, S, T;
    unsigned long long n;
    cin >> n;
    T = BigInt(n);
    cin >> A.val;
    cin >> B.val;
    cout << C.compare(A, B) << endl;
    C = A + B;
    D = A - B;
    E = A * B;
    F = A / B;
    G = A % B;
    M = A;
    N = A;
    P = A;
    Q = A;
    R = A;
    S = A;
    A += B;
    M -= B;
    N *= B;
    P /= B;
    Q %= B;
    ++R;
    --S;
    cout << C.val << endl;
    cout << D.val << endl;
    cout << E.val << endl;
    cout << F.val << endl;
    cout << G.val << endl;
    cout << A.val << endl;
    cout << M.val << endl;
    cout << N.val << endl;
    cout << P.val << endl;
    cout << Q.val << endl;
    cout << R.val << endl;
    cout << S.val << endl;
    cout << T.val << endl;
    return 0;
}
