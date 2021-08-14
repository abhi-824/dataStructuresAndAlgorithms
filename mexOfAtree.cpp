
#include<bits/stdc++.h>
 
using namespace std;
#define int long long int
const int mxN=100001;
class Tree
{
    vector<int>adj[mxN];
    vector<int>val;
    map<int,int>valToInd;
    vector<int>in;
    vector<int>out;
    vector<int>eTour;
public:
    Tree(vector<int>arr)
    {
        int n = arr.size();
        val.resize(n);
        in.resize(n+1);
        out.resize(n+1);
        for(int i=0;i<n;i++)
        {
            valToInd[arr[i]]=i+1;
        }
        for(int i = 0; i <= n; i++)in[i] = -1;
        for(int i = 0; i <= n; i++)out[i] = -1;
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
        dfs(1, vis);
        for(int i = 0; i < eTour.size(); i++)
        {
            if(in[eTour[i]] == -1)
                in[eTour[i]] = i;
            else
                out[eTour[i]] = i;
            // cout<<eTour[i]<<" ";
        }
        // cout<<"\n";
        for(int i = 0; i < eTour.size(); i++)
        {
            eTour[i] = val[eTour[i]];
        }
    }

    vector<int> pathtozero()
    {
        int zerNode=valToInd[0];
        queue<int>q;
        q.push(1);
        vector<int>ans;
        vector<int>parent(valToInd.size()+1,-1);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            if(x==zerNode)
            {
                while(parent[x]!=-1)
                {
                    ans.push_back(x);
                    x=parent[x];
                }
                ans.push_back(1);
                reverse(ans.begin(),ans.end());
                return ans;
            }
            else{
                for(auto it:adj[x]){
                    parent[it]=x;
                    q.push(it);
                }
            }
        }
        return ans;
    }
    void addEdge(int x, int y)
    {
        adj[x].push_back(y);
        // adj[y].push_back(x);
    }
    bool query(int mex,int node)
    {
        if(mex>=val.size())return 1;
        int l1=in[node];
        int r1=out[node];
        int l2=in[valToInd[mex]];
        int r2=out[valToInd[mex]];
        return (l1>l2&&r1<r2);
    }
};
vector<int> solve(int n, vector<int>& val, vector<vector<int>> &c)
{
    Tree tr(val);

    for(int i=0;i<c.size();i++)tr.addEdge(c[i][0],c[i][1]);
    tr.eulerTour();
    vector<int>pathToZero=tr.pathtozero();
    
    int i=1;
    vector<int>mex(n,-1);
    for(int j=pathToZero.size()-1;j>=0;j--)
    {
        while(!tr.query(i,pathToZero[j]))
        {
            i++;
        }
        mex[pathToZero[j]-1]=i;
    }
    for(int i=0;i<mex.size();i++)mex[i]=max(mex[i],0);
    return mex;
}
int32_t main()
{
    int n;cin>>n;
    vector<int>b(n);
    for(int i=0;i<n;i++)
        cin>>b[i];
    vector<vector<int>> c;
    for(int i=0;i<n-1;i++)
    {
        int x,y;cin>>x>>y;
        vector<int>a;
        a.push_back(x);
        a.push_back(y);
        c.push_back(a);
    }
    vector<int>ans=solve(n,b,c);
    for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
}
