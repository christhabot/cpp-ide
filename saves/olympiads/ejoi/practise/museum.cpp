#include "museum.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

std::vector <int> find_tours (int N, int M, int K, std::vector <std::pair <int, int>> e, std::vector <int> t)
{
    vector<vector<pair<int,int>>> connections;
    // node, distance
    connections.assign(M+1, vector<pair<int,int>>());
    for(int i = 0; i < e.size(); i++)
    {
        connections[e[i].first].push_back({e[i].second, t[i]});
        connections[e[i].second].push_back({e[i].first, t[i]});
    }
    int found=0;
    pair<int,int> idx;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> distances;
    // distance, node
    pq.push({0,0});
    while(!pq.empty() && found < K)
    {
        idx = pq.top();
        pq.pop();
        if(idx.second == N)
        {
            distances.push_back(idx.first);
            found++;
        }
        for(int i = 0; i < connections[idx.second].size(); i++)
        {
            pq.push({connections[idx.second][i].first, idx.first + connections[idx.second][i].second});
        }
    }
    return distances;
}
