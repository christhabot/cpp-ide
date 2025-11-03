#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<pair<ll, ll>>> connections;
// node, distance
priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
// distance, node
vector<ll> stuff;
// distance
vector<ll> path;

int main() {
    ll nodes, edges;
    ll temp1, temp2, temp3;
    bool done = false;
    pair<ll,ll> t;
    scanf("%lld %lld", &nodes, &edges);
    connections.assign(nodes, vector<pair<ll,ll>>());
    stuff.assign(nodes, LLONG_MAX);
    for(ll i = 0; i < edges; i++)
    {
        scanf("%lld %lld %lld", &temp1, &temp2, &temp3);
        temp1--;
        temp2--;
        connections[temp1].push_back({temp2, temp3});
    }
    pq.push({0, 0});
    while(!pq.empty())
    {
        t = pq.top();
        pq.pop();

        if (t.first > stuff[t.second]) continue;

        for(ll i = 0; i < connections[t.second].size(); i++)
        {
            if(stuff[connections[t.second][i].first] > t.first + connections[t.second][i].second)
            {
                pq.push({t.first + connections[t.second][i].second, connections[t.second][i].first});
                stuff[connections[t.second][i].first] = t.first + connections[t.second][i].second;
            }
        }
    }
    printf("0 ");
    for(ll i = 1; i < nodes; i++)
    {
        printf("%lld ", stuff[i]);
    }
}