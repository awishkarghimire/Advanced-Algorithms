#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>

using namespace std;

void displayGraph(vector<list<int>> graph, int capacity[][202], int n);
int breadthFirst(vector<list<int>> graph, int capacity[][202], int n);
int edmond_karp(vector<list<int>> graph, int capacity[][202], int n);

int
main(void)
{
	int n, m;
	cin >> n >> m;
	int vertexCount = n + m + 2;
	vector<list<int>> graph(vertexCount);
	int capacity[vertexCount][202];
	for(int i = 0; i < vertexCount; i++)
	{
		for(int j = 0; j < vertexCount; j++)
			capacity[i][j] = 0;
	}
	for(int i = 1; i <= n; i++)
	{
		capacity[0][i] = 1;
		graph[0].push_back(i);
		graph[i].push_back(0);
	}
	for(int i = n + 1; i <= n + m; i++)
	{
		capacity[i][vertexCount - 1] = 1;
		graph[i].push_back(vertexCount - 1);
		graph[vertexCount - 1].push_back(i);
	}
	int array[m];
	for(int j = 0; j < n; j++)
	{
		for(int i = 0; i < m; i++)
		{
			cin >> array[i];
		}
		for(int i = 0; i < m; i++)
		{
			if(array[i] == 1)
			{
				graph[j + 1].push_back((n + (i + 1)));
				graph[n + (i + 1)].push_back(j + 1);	
				capacity[j + 1][n + (i + 1)] = 1;
			}
		}
	}
	int flow = edmond_karp(graph, capacity, vertexCount);
	list<int>::iterator It;
	for(int i = 1; i <= n; i++)
	{
		bool breakVar = true;
		for(It = graph[i].begin(); It != graph[i].end(); It++)
		{
			if(capacity[i][*It] == 0 && *It != 0)
			{
				cout << *It - n << " ";
				breakVar = false;
				break;
			}
		}
		if(breakVar)
			cout << -1 << " ";
	}
}

void displayGraph(vector<list<int>> graph, int capacity[][202], int n)
{
	list<int>::iterator It;
	for(int i = 0; i < n; i++)
	{
		for(It = graph[i].begin(); It != graph[i].end(); It++)
			cout << i << " " << *It	<< " " << capacity[i][*It] << "\n";
	}
}

int breadthFirst(vector<list<int>> graph, int capacity[][202], int n)
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
				isVisited[*It] = true;
			}
		}	
		if(breakVar)
			break;
	}
	if(breakVar == false)
		return 0;
	vector<int> path;
	int j = n - 1;
	while(parent[j] != -1)
	{
		path.push_back(j);
		j = parent[j];
	}
	path.push_back(j);
	reverse(path.begin(), path.end());
	int min = 1000000;
	for(int i = 0; i < path.size() - 1; i++)
	{
		if(min > capacity[path[i]][path[i + 1]])
			min = capacity[path[i]][path[i + 1]];
	}
	for(int i = 0; i < path.size() - 1; i++)
	{
		capacity[path[i]][path[i + 1]] -= min;
		capacity[path[i + 1]][path[i]] += min;
	}
	return min;
}

int edmond_karp(vector<list<int>> graph, int capacity[][202], int n)
{
	int flow = 0;
	int min = 1;
	int i = 0;
	while(min != 0)
	{
		min = breadthFirst(graph, capacity, n);
		flow += min ;
	}
	return flow;
}
