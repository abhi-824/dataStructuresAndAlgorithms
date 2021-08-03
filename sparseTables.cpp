#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int LOG = 17;
const int maxN = 100004;
class sparseTable
{
    int st[maxN][LOG];
public:
    // To build a sparse table, we use a 2d array with size n*lg(n)
    // st[i][j] stores the minimum in range i, i+(1<<j)
    // We first our 0th row with the values at the indices
    // From second row, where exponent is 1( which means we have to consider range of size 2 )
    // we follow this relation: m[i][j]=min(m[i][j-1],m[i-(1<<(j-1))][j-1]);
    // This is because
    // Minimum in the range i, i+(1<<j)
    // would be Minimum in range i,i+(1<<(j-1)) and i+(1<<(j-1)), i+2*(1<<(j-1))=i+(1<<j);
    sparseTable(vector<int> arr)
    {
        int n = arr.size();
        for(int i = 0; i < n; i++)st[i][0] = arr[i];
        for(int j = 1; j < LOG; j++)
        {
            for(int i = 0; i + (1 << j) - 1 < n; i++)
            {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    // To query on a sparse table, we query from l to the nearest number
    //  which is of form 2^k to r-l+1 and another query from r-the nearest number to r and find the minimum of these two
    int query(int l, int r)
    {
        int len = r - l + 1;
        int j = log2(len);
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }

};
int32_t main()
{
    // This question is created by the holy demon AbDUDE
    // on this problem: https://www.spoj.com/problems/RMQSQ/
    // We are going to use sparse tables for these.
    // Sparse tables enable constant time per query
    // and applicable on idempotent functions with processing fee of nlg(n)
    // Idempotent Functions: A*A=A(Like Max, Min, GCD, etc)
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0; i < n; i++)cin >> a[i];
    sparseTable st(a);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << "\n";
    }


    return 0;
}
