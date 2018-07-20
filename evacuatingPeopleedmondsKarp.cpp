//uses aproox 10 megabytes of memory
//works fo rmaximum of 100 nodes and 10000 edges
//input first line n, m : no of vertices, no of edges
//m lines stating to, from, edge capacity

#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<algorithm>

using namespace std;

void displayGraph(vector<list<int>> graph, int capacity[][100], int n);
int breadthFirst(vector<list<int>> graph, int capacity[][100], int n);
int edmond_karp(vector<list<int>> graph, int capacity[][100], int n);

int 
main(void)
{
	int n, m;
	cin >> n >> m;
	vector<list<int>> graph(n);
	vector<list<int>> residualGraph(n);
	int graphCapacity[n][100];
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			graphCapacity[i][j] = 0;
		}
	}
	int u, v, c;
	for(int i = 0; i < m; i++) //input loop
	{
		cin >> u >> v >> c;
		if(graphCapacity[u - 1][v - 1] == 0 && u - 1 != v - 1) //handles multiple edges and ignores self loops
		{
			graph[u - 1].push_back(v - 1);
			graph[v - 1].push_back(u - 1);
			graphCapacity[u - 1][v - 1] = c;
		}
		else if(u - 1 != v - 1) 
		{
			graphCapacity[u - 1][v - 1] += c;
		}
	}
	cout << edmond_karp(graph, graphCapacity, n);
}

void displayGraph(vector<list<int>> graph, int capacity[][100], int n)
{
	list<int>::iterator It;
	for(int i = 0; i < n; i++)
	{
		for(It = graph[i].begin(); It != graph[i].end(); It++)
			cout << i + 1 << " " << *It + 1	<< " " << capacity[i][*It] << "\n";
	}
}

int breadthFirst(vector<list<int>> graph, int capacity[][100], int n)
{
	queue<int> q1;
	int vertex;
	list<int>::iterator It;
	int* parent = new int[n];
	bool isVisited[n];
	for(int i = 0; i < n; i++)
	{
		parent[i] = -1;
		isVisited[i] = false;
	}
	q1.push(0);
	bool breakVar = false;
	isVisited[0] = true;
	while(!q1.empty())
	{
		vertex = q1.front(); 
		q1.pop();
		if(vertex == n - 1)
		{
			breakVar = true;
			break;
		}
		for(It = graph[vertex].begin(); It != graph[vertex].end(); It++)
		{
			if(isVisited[*It] == false && capacity[vertex][*It] != 0)
			{
				q1.push(*It);
				parent[*It] = vertex;
				//cout << *It + 1 << ":" << vertex + 1 << "\n";
				isVisited[*It] = true;
			}
		}	
		//cout << 1 << ":" << parent[0] << "\n";
		if(breakVar)
			break;
	}
	if(breakVar == false)
		return 0;
	//cout << "lol";
	vector<int> path;
	int j = n - 1;
	while(parent[j] != -1)
	{
		//cout << j << " ";
		path.push_back(j);
		j = parent[j];
	}
	path.push_back(j);
	reverse(path.begin(), path.end());
	/*cout << "path: ";
	for(int i = 0; i < path.size(); i++)
		cout << path[i] + 1 << " ";
	cout << endl;*/
	int min = 1000000;
	for(int i = 0; i < path.size() - 1; i++)
	{
		if(min > capacity[path[i]][path[i + 1]])
			min = capacity[path[i]][path[i + 1]];
	}
	//cout << "min: " << min << "\n";
	for(int i = 0; i < path.size() - 1; i++)
	{
		capacity[path[i]][path[i + 1]] -= min;
		capacity[path[i + 1]][path[i]] += min;
	}
	return min;
}

int edmond_karp(vector<list<int>> graph, int capacity[][100], int n)
{
	int flow = 0;
	int min = 1;
	int i = 0;
	while(min != 0)
	{
		//displayGraph(graph, capacity , n);
		min = breadthFirst(graph, capacity, n);
		flow += min ;
		//cout << "\n\n";
		//i++;
		//if( i == 3)
		//	break;
		//cout << "lol";
	}
	return flow;
}
