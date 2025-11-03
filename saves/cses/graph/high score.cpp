#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> connections;
vector<pair<int, pair<int,int>>> vec;
vector<ll> dist;

vector<int> q;
// node, source
vector<bool> explored;

ll nodes;

bool dfs(int i)
{
    explored[i] = true;
    if(i == nodes-1)
        return true;
    for(int j = 0; j < connections[i].size(); j++)
    {
        if(!explored[connections[i][j]] && dfs(connections[i][j]))
        {
            return true;
        }
    }
    return false;
}

int main() {
    ll edges;
    int temp1, temp2, temp3;
    int n1, n2, w;
    int t;
    scanf("%lld %lld", &nodes, &edges);
    dist.assign(nodes, LLONG_MIN);
    explored.assign(nodes, false);
    connections.assign(nodes, vector<int>());
    for(ll i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &temp1, &temp2, &temp3);
        temp1--;
        temp2--;
        vec.push_back({temp3,{temp1, temp2}});
        connections[temp1].push_back(temp2);
    }
    dist[0] = 0;
    for(int rel = 0; rel < nodes; rel++)
    {
        for(int i = 0; i < vec.size(); i++)
        {
            n1 = vec[i].second.first;
            n2 = vec[i].second.second;
            w = vec[i].first;
            if(dist[n1] != LLONG_MIN && dist[n2] < dist[n1] + w)
            {
                if(rel == nodes-1)
                {
                    q.push_back(n1);
                }
                dist[n2] = dist[n1] + w;
            }
        }
    }
    for(int i = 0; i < q.size(); i++)
    {
        t = q[i];
        if(dfs(t))
        {
            printf("-1");
            return 0;
        }
    }
    printf("%lld", dist[nodes-1]);
}