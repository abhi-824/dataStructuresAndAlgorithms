#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int mxN = 200001;
int inf = 1e18;
class segTree
{
private:
    vector<int>tree;
    vector<int>a;
    void buildTree(int i, int st, int end, vector<int> &arr)
    {
        if(st == end)
        {
            tree[i] = arr[st];
            return;
        }

        int mid = st + (end - st) / 2;
        int lchild = 2 * i + 1;
        int rchild = 2 * i + 2;

        buildTree(lchild, st, mid, arr);

        buildTree(rchild, mid + 1, end, arr);

        tree[i] = tree[lchild] + tree[rchild];
    }
    int queryPrivate(int i, int segStart, int segEnd, int l, int r)
    {
        if(segEnd < l || segStart > r)return 0;

        if(segEnd <= r && segStart >= l)
            return tree[i];

        int lchild = 2 * i + 1;
        int rchild = 2 * i + 2;

        int mid = segStart + (segEnd - segStart) / 2;

        int resL = queryPrivate(lchild, segStart, mid, l, r);
        int resR = queryPrivate(rchild, mid + 1, segEnd, l, r);

        return resL + resR;
    }
    void upd(int i, int st, int end, int ind, int newVal)
    {
        if(st == end)
        {
            tree[i] = newVal;
            return;
        }

        int mid = st + (end - st) / 2;

        if(ind <= mid)
            upd(2 * i + 1, st, mid, ind, newVal);
        else
            upd(2 * i + 2, mid + 1, end, ind, newVal);

        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
public:
    segTree() {}
    segTree(vector<int> &arr)
    {
        int n = arr.size();
        tree.resize(4 * n + 1);
        for(int i = 0; i < 4 * n + 1; i++)tree[i] = inf;
        buildTree(0, 0, n - 1, arr);
        a = arr;
    }
    void build(vector<int> &arr)
    {
        int n = arr.size();
        tree.resize(4 * n + 1);
        for(int i = 0; i < 4 * n + 1; i++)tree[i] = inf;
        buildTree(0, 0, n - 1, arr);
        a = arr;
    }
    int query(int l, int r)
    {
        int n = a.size();
        return queryPrivate(0, 0, n - 1, l, r);
    }

    void update(int indToChange, int newVal)
    {
        int n = a.size();
        upd(0, 0, n - 1, indToChange, newVal);
    }
};
class Tree
{
    vector<int>adj[mxN];
    vector<int>val;
    vector<int>in;
    vector<int>out;
    vector<int>eTour;
    segTree s;
public:
    Tree(vector<int>arr)
    {
        int n = arr.size();
        val.resize(n);
        in.resize(n);
        out.resize(n);
        for(int i = 0; i < n; i++)in[i] = -1;
        for(int i = 0; i < n; i++)out[i] = -1;
        val = arr;
    }
    void dfs(int src, vector<bool> &vis)
    {
        vis[src] = 1;
        eTour.push_back(src);
        for(auto it : adj[src])
        {
            if(!vis[it])
                dfs(it, vis);
        }
        eTour.push_back(src);
    }
    void eulerTour()
    {
        vector<bool>vis(val.size());
        dfs(0, vis);
        for(int i = 0; i < eTour.size(); i++)
        {
            if(in[eTour[i]] == -1)
                in[eTour[i]] = i;
            else
                out[eTour[i]] = i;
        }
        for(int i = 0; i < eTour.size(); i++)
        {
            eTour[i] = val[eTour[i]];
        }
        s.build(eTour);
    }
    void addEdge(int x, int y)
    {
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int query(int node)
    {
        node--;
        return s.query(in[node], out[node]) / 2;
    }
    void update(int node, int x)
    {
        node--;
        s.update(in[node], x);
        s.update(out[node], x);
        val[node] = x;
    }
};
int32_t main()
{
    // This is the holy code of the demon AB-DUDE
    // This is the code of the question : https://cses.fi/problemset/task/1137/
    // We used Euler Tour and Segment Trees for this
    // Just do a Euler tour of type 2 on the tree and make a basic segment tree on the array
    // Now, we can just use in and out arrays for the positions of the nodes in the euler tour array
    
    int n, q;
    cin >> n >> q;
    vector<int>a(n);
    for(int i = 0; i < n; i++)cin >> a[i];
    Tree tr(a);
    for (int i = 0; i < n - 1; ++i)
    {
        int x, y;
        cin >> x >> y;
        tr.addEdge(x, y);
    }
    tr.eulerTour();
    for(int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int s, x;
            cin >> s >> x;
            tr.update(s, x);
        }
        else
        {
            int s;
            cin >> s;
            cout << tr.query(s) << "\n";
        }
    }

    return 0;
}
