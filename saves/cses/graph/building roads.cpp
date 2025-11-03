#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> connections;
vector<bool> explored;
vector<pair<int,int>> results;

void dfs(int i)
{
    explored[i] = true;
    for(int j = 0; j < connections[i].size(); j++)
    {
        if(!explored[connections[i][j]])
        {
            dfs(connections[i][j]);
        }
    }
    return;
}

int main() {
    int nodes, edges, temp1, temp2;
    int total = 0;
    scanf("%d %d", &nodes, &edges);
    connections.assign(nodes, vector<int>());
    explored.assign(nodes, false);
    for(int i = 0; i < edges; i++)
    {
        scanf("%d %d", &temp1, &temp2);
        temp1--;
        temp2--;
        connections[temp1].push_back(temp2);
        connections[temp2].push_back(temp1);
    }
    dfs(0);
    for(int i = 0; i < nodes; i++)
    {
        if(!explored[i])
        {
            total++;
            results.push_back({0, i});
            dfs(i);
        }
    }
    printf("%d\n", total);
    for(int i = 0; i < total; i++)
    {
        printf("%d %d\n", results[i].first+1, results[i].second+1);
    }
}