#include<bits/stdc++.h>
using namespace std;
#define int long long int
class Graph
{
public:
	vector<int>adj[1000];
	void addEdge(int a,int b,bool dir=false)
	{
		adj[a].push_back(b);
		if(!dir)
			adj[b].push_back(a);
	}
	void BFS(int src,vector<bool>&vis)
	{
		//O(V+E)
		vis[src]=true;
		queue<int>q;
		q.push(src);
		while(!q.empty())
		{
			int cur=q.front();
			cout<<cur<<" ";
			q.pop();
			for(auto it:adj[cur])
			{
				if(!vis[it]){
					vis[it]=true;
					q.push(it);
				}
			}
		}
	}
	void printGraphUsingBFS(int n,int src=0)
	{
		//O(V+E)
		vector<bool> vis(n+1);
		for(int i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				BFS(i,vis);
			}
		}
		cout<<endl;
	}
	void DFS(int src,vector<bool>&vis,bool pr=1)
	{
		//O(V+E)
		vis[src]=true;
		if(pr)
			cout<<src<<" ";
		for(auto it:adj[src])
		{
			if(!vis[it]){
				DFS(it,vis,pr);
			}
		}
	}
	void printGraphUsingDFS(int n,int src=0)
	{
		//O(V+E)
		vector<bool>vis(n+1);
		for(int i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				DFS(i,vis);
			}
		}
		cout<<endl;
	}
	void printShortestPathToAllNodes(int n,int src=0)
	{
		//This method only applies to unweighted graph
		//Time Complexity: O(V+E)
		vector<int> dist(n+1);
		for(int i=0;i<n+1;i++)dist[i]=-1;
		vector<bool>vis(n+1);
		queue<int>q;
		q.push(src);
		vis[src]=1;
		dist[src]=0;
		while(!q.empty())
		{
			int cur=q.front();
			q.pop();
			for(auto it:adj[cur])
			{
				if(!vis[it])
				{
					vis[it]=1;
					q.push(it);
					dist[it]=dist[cur]+1;
				}
			}
		}
		for(int i=1;i<=n;i++)
			cout<<dist[i]<<" ";
		cout<<endl;
	}
	void findNumberOfConnectedComponents(int n)
	{
		//Same as DFS
		vector<bool>vis(n+1);
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				DFS(i,vis,0);
				cnt++;
			}
		}
		cout<<cnt;
		cout<<endl;
	}
	int countAllPossiblePaths(int src,int dest)
	{
		//Only Acyclic Graph
		int cnt=0;
		
		if(src==dest)return 1;
		
		for(auto it:adj[src])
		{
			cnt+=countAllPossiblePaths(it,dest);
		}
		return cnt;
	}
	void printAllPossiblePaths(int src,int dest,int n)
	{		
		vector<bool>vis(n);
		int path[n];
		int ind=0;
		printAllPathsUtil(src,dest,vis,path,ind);
		return;
	}
	void printAllPathsUtil(int s,int d,vector<bool>&vis,int path[],int &ind )
	{
		vis[s]=true;
		path[ind]=s;
		ind++;
		if(s==d)
		{
			cout<<"> ";
			for(int i=0;i<ind-1;i++)
				cout<<path[i]<<"->";
			cout<<path[ind-1];
			cout<<"\n";
		}
		else{
			for(auto it:adj[s])
			{
				if(!vis[it])
				{
					printAllPathsUtil(it,d,vis,path,ind);
				}
			}
		}
		ind--;
		vis[s]=false;
	}
	bool detectCycle(int src,int n)
	{
		vector<bool>vis(n);
		queue<int>q;
		q.push(src);
		vis[src]=1;
		int parent[n];
		parent[src]=-1;
		while(!q.empty())
		{
			int cur=q.front();
			q.pop();
			for(auto it:adj[cur])
			{
				if(!vis[it])
				{
					vis[it]=1;
					parent[it]=cur;
					q.push(it);
				}
				else if(it!=parent[cur])
				{
					return 1;
				}
			}
		}

		return 0;
	}

};
int32_t main()
{
	ios_base::sync_with_stdio(false);
		cin.tie(NULL); cout.tie(0);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
	int t;cin>>t;
	while(t--)
	{
		int n,m;cin>>n>>m;
		Graph gr;
		for(int i=0;i<m;i++)
		{
			int x,y;cin>>x>>y;
			gr.addEdge(x,y);
		}
		cout<<"BFS: ";gr.printGraphUsingBFS(n,1);
		cout<<"DFS: ";gr.printGraphUsingDFS(n,1);
		// for(int i=1;i<=n;i++)
		// {
		// 	cout<<"Shortest Path Array for node "<<i<<": ";
		// 	gr.printShortestPathToAllNodes(n,i);
		// }
		// cout<<"Number of Connected Componenets: ";
		// gr.findNumberOfConnectedComponents(n);
		// cout<<"# of paths from 1 to 5: ";
		// cout<<gr.countAllPossiblePaths(1,5)<<endl;

		// cout<<"paths from 1 to 5: \n";
		// gr.printAllPossiblePaths(1,5,n);

		cout<<"Cycle Detection in Undirected Graph: ";
		cout<<gr.detectCycle(1,n)<<endl;
		
	}
	
	return 0;
}