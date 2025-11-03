#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> dist;
vector<vector<ll>> connections;
vector<bool> visited;
vector<ll> dp;

void bfs_dist(ll n) {
    visited.assign(n, false);

    queue<ll> q;
    visited[0] = true;
    q.push(0);
    dist[0] = 0;

    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (ll v : connections[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

ll dfs(ll u)
{
    if(dp[u] != -1) return dp[u];
    ll best = dist[u];

    for(ll v : connections[u])
    {
        if(dist[u] < dist[v])
            best = min(best, dfs(v));
        else
            best = min(best, dist[v]);
    }

    return dp[u] = best;
}


int main() {
    ll amountt, cities, roads;
    ll temp, temp2;
    scanf("%lld", &amountt);
    for(int test = 0; test < amountt; test++)
    {
        scanf("%lld %lld", &cities, &roads);
        connections.assign(cities, vector<ll>());
        dist.assign(cities, -1);
        for(int i = 0; i < roads; i++)
        {
            scanf("%lld %lld", &temp, &temp2);
            temp--;
            temp2--;
            connections[temp].push_back(temp2);
        }
        bfs_dist(cities);
        dp.assign(cities, -1);
        for(int i = 0; i < cities; i++)
        {
            printf("%lld ", dp[i] = min(dfs(i), dist[i]));
        }
        printf("\n");
    }
}