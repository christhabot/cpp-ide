#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> connections;
vector<bool> explored;
vector<bool> colors;
ll amountc;

void dfs(ll i, bool colored)
{
    explored[i] = true;
    if(colored)
    {
        colors[i] = true;
        amountc++;
    }
    for(int j = 0; j < connections[i].size(); j++)
    {
        if(!explored[connections[i][j]])
            dfs(connections[i][j], !colored);
    }
}

void bfs(ll i, bool colored)
{
    pair<int,int> idx;
    queue<pair<int,int>> pq;
    pq.push({i,-1});
    while(!pq.empty())
    {
        idx = pq.front();
        pq.pop();
        if(explored[idx.first]) continue;
        explored[idx.first] = true;
        if(idx.second == -1) {
            colors[idx.first] = colored;
        } else {
            colors[idx.first] = !colors[idx.second];
        }
        if(colors[idx.first])
            amountc++;
        for(int j = 0; j < connections[idx.first].size(); j++)
        {
            if(!explored[connections[idx.first][j]])
            {
                explored[connections[idx.first][j]] = true;
                pq.push({connections[idx.first][j], idx.first});
            }
        }
    }
}

int main()
{
    ll numbert;
    ll nodes, edges;
    ll temp, temp2;
    scanf("%lld", &numbert);
    for(ll test = 0; test < numbert; test++)
    {
        scanf("%lld %lld", &nodes, &edges);
        connections.assign(nodes,vector<ll>());
        for(int i = 0; i < edges; i++)
        {
            scanf("%lld %lld", &temp, &temp2);
            temp--;
            temp2--;
            connections[temp].push_back(temp2);
            connections[temp2].push_back(temp);
        }
        explored.assign(nodes, false);
        colors.assign(nodes, false);
        amountc = 0;
        for (int i = 0; i < nodes; i++) {
            if (!explored[i]) {
                bfs(i, true);
            }
        }
        if(amountc <= nodes/2)
        {
            printf("%lld\n", amountc);
            for(int i = 0; i < nodes; i++)
            {
                if(colors[i])
                    printf("%d ", i+1);
            }
        }
        else
        {
            printf("%lld\n", nodes-amountc);
            for(int i = 0; i < nodes; i++)
            {
                if(!colors[i])
                    printf("%d ", i+1);
            }
        }
        printf("\n");
    }
}